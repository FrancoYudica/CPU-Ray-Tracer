#include "PhongMaterial.hpp"
#include "../Ray.hpp"
#include "../ShadeRec.hpp"
#include "../World.hpp"
#include "../math_RT.hpp"

using namespace RT;
using namespace RT::Materials;

RGBColor Phong::shade(const ShadeRec& sr)
{
    // Incoming direction
    Vec3 wo = -sr.ray.direction;

    RGBColor L = ambient_brdf->rho(sr, sr.ray.direction) * sr.world->ambient_light->L(sr);

    for (const std::shared_ptr<Light>& light : sr.world->lights) {
        // To light direction
        Vec3 wi = light->get_direction(sr);
        Vec3 normal = sr.get_normal();

        float n_dot_wi = Math::dot(normal, wi);

        if (n_dot_wi > 0.0f) {
            bool in_shadow = false;
            if (light->casts_shadows()) {
                Ray shadow_ray = { sr.hit_point + normal * Constants::k_epsilon, wi };
                in_shadow = light->in_shadow(shadow_ray, sr);
            }

            if (!in_shadow) {

                L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi)) * light->L(sr) * n_dot_wi;
            }
        }
    }

    return L;
}

// The only difference with Phong::shade is that we are using the
// area form of the rendering equation, where geometrical term (G)
// and surface area (pdf) are added
RGBColor Phong::area_light_shade(const ShadeRec& sr)
{
    // Incoming direction
    Vec3 wo = -sr.ray.direction;

    RGBColor L = ambient_brdf->rho(sr, sr.ray.direction) * sr.world->ambient_light->L(sr);

    for (const std::shared_ptr<Light>& light : sr.world->lights) {
        // To light direction
        Vec3 wi = light->get_direction(sr);
        Vec3 normal = sr.get_normal();
        float n_dot_wi = Math::dot(normal, wi);

        if (n_dot_wi > 0.0f) {

            bool in_shadow = false;
            if (light->casts_shadows()) {
                Ray shadow_ray = { sr.hit_point + normal * Constants::k_epsilon, wi };
                in_shadow = light->in_shadow(shadow_ray, sr);
            }

            if (!in_shadow) {

                L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi)) * light->L(sr) * n_dot_wi * light->G(sr) / light->pdf(sr);
            }
        }
    }

    return L;
}