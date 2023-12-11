#include "PlasticMaterial.hpp"
#include "../Ray.hpp"
#include "../ShadeRec.hpp"
#include "../World.hpp"

using namespace RT;
using namespace Materials;

RGBColor Plastic::shade(const ShadeRec& sr)
{

    Vec3 wo = -sr.ray.direction;
    RGBColor L = ambient_brdf->rho(sr, wo) * sr.world->ambient_light->L(sr);

    for (const std::shared_ptr<Light>& light : sr.world->lights) {
        // To light direction
        Vec3 wi = light->get_direction(sr);

        bool in_shadow = false;
        Vec3 normal = sr.get_normal();

        if (light->casts_shadows()) {
            Ray shadow_ray = { sr.hit_point + normal * Constants::k_epsilon, wi };
            in_shadow = light->in_shadow(shadow_ray, sr);
        }

        if (!in_shadow) {
            float n_dot_wi = Math::dot(normal, wi);

            if (n_dot_wi > 0.0f) {
                L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi)) * light->L(sr) * n_dot_wi;
            }
        }
    }

    return L;
}

// The only difference with Plastic::shade is that we are using the
// area form of the rendering equation, where geometrical term (G)
// and surface area (pdf) are added
RGBColor Plastic::area_light_shade(const ShadeRec& sr)
{
    Vec3 wo = -sr.ray.direction;
    RGBColor L = ambient_brdf->rho(sr, sr.ray.direction) * sr.world->ambient_light->L(sr);

    for (const std::shared_ptr<Light>& light : sr.world->lights) {
        // To light direction
        Vec3 wi = light->get_direction(sr);

        bool in_shadow = false;
        Vec3 normal = sr.get_normal();
        if (light->casts_shadows()) {
            Ray shadow_ray = { sr.hit_point + normal * Constants::k_epsilon, wi };
            in_shadow = light->in_shadow(shadow_ray, sr);
        }

        if (!in_shadow) {
            float n_dot_wi = Math::dot(normal, wi);

            if (n_dot_wi > 0.0f) {
                L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi)) * light->L(sr) * n_dot_wi * light->G(sr) / light->pdf(sr);
            }
        }
    }

    return L;
}