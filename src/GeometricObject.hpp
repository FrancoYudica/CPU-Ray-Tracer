#ifndef __RT_GEOMETRIC_OBJECT__
#define __RT_GEOMETRIC_OBJECT__

#include "AABBox.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Sampler.hpp"
#include "ShadeRec.hpp"

namespace RT {

enum class GeometricObjectType : uint8_t {
    Sphere = 0,
    Plane = 1,
    Box = 2,
    Disk = 3,
    Rect = 4,
    Triangle = 5,
    GenericCylinder = 6,
    Torus = 7,
    PartCylinder = 8,
    PartSphere = 9,
    SolidCylinder = 10,
    Capsule = 11,
    PartTorus = 12,
    CompoundBox = 13,
    Annulus = 14,
    Cone = 15,
    SolidCone = 16,
    ThickAnnulus = 17,
    Bowl = 18,
    Instance = 19,
    BoundingVolumeHierarchy = 20,
    Container = 21,
    TransformContainer = 22,
    SmoothTriangle = 23,
    FlatMeshTriangle = 24,
    SmoothMeshTriangle = 25
};

static bool is_container_type(GeometricObjectType type)
{
    return type == GeometricObjectType::Container
        || type == GeometricObjectType::BoundingVolumeHierarchy
        || type == GeometricObjectType::TransformContainer;
}
class GeometricObject;

typedef std::shared_ptr<GeometricObject> GeometricObjectPtr;

class GeometricObject {

public:
    GeometricObject(GeometricObjectType type)
        : _type(type)
        , _shadows(true)
        , _visible(true)
        , _inv_surface_area(1.0f)
        , _surface_sampler(nullptr)
        , _bounding_box(Vec3(0.0), Vec3(0.0))
        , _has_bounding_box(false)
        , _bounding_box_enabled(false)
        , _normal_type(NormalType::Outwards)
    {
    }

    inline bool is_visible() const { return _visible; }
    void set_visibility(bool visible) { _visible = visible; }

    virtual void set_material(const std::shared_ptr<Material>& mtl) { material = mtl; }

    inline std::shared_ptr<Material> get_material() const { return material; }

    inline bool has_material() const { return material != nullptr; }

    inline GeometricObjectType get_type() { return _type; }

    inline void set_normal_flip() { _normal_type = NormalType::Flip; }

    inline void set_normal_outwards() { _normal_type = NormalType::Outwards; }

    inline void set_normal_inwards() { _normal_type = NormalType::Inwards; }

    inline NormalType get_normal_type() const { return _normal_type; }

    inline bool casts_shadows() const { return _shadows; }

    inline void enable_shadows() { _shadows = true; }

    inline void disable_shadows() { _shadows = false; }

    inline bool has_bounding_box() const { return _has_bounding_box; }

    inline void set_bounding_box(const Vec3& min, const Vec3& max)
    {
        _bounding_box = AABBox(min, max);
        _has_bounding_box = true;
    }

    inline void set_bounding_box(const AABBox& bbox)
    {
        set_bounding_box(bbox.get_min(), bbox.get_max());
    }

    /// @brief Disables bounding box
    inline void disable_bounding_box() { _bounding_box_enabled = false; }

    /// @brief Enables bounding box, in case that it has a bounding box set
    inline void enable_bounding_box() { _bounding_box_enabled = _has_bounding_box; }

    /// @brief True if the bounding box is enabled
    inline bool bounding_box_enabled() const { return _bounding_box_enabled; }

    /// @brief Returns AABBox used for testing intersections
    virtual const AABBox& get_bounding_box() const { return _bounding_box; }

    /// @brief Recalculates bounding box if possible
    virtual void recalculate_bounding_box() { }

    /// @return inverse surface area
    virtual float pdf(const ShadeRec& sr) const { return _inv_surface_area; }

    virtual bool hit(const Ray& ray, double& tmin, ShadeRec& record) const = 0;

    /// @brief Hit called when trying to cast shadows. Same as hit, but
    /// optimized for shadows, since there is no need to store ShadeRec
    /// @param ray Origin in intersection and direction to light
    /// @param tmin Minimum accepted distance t from origin along ray direction
    /// @returns True or false if the ray intersects the object.
    virtual bool shadow_hit(const Ray& ray, double& tmin) const = 0;

    /// @return Normal at surface point p. Used for area lights
    virtual Vec3 get_normal(const Vec3& p) const { return Vec3(); };

    /// @brief Samples point from surface. Used for area lights
    virtual Vec3 sample_surface() const { return Vec3(); };

    /// @brief Sets surface sampler. Used for area lights
    virtual void set_surface_sampler(std::shared_ptr<Sampler> sampler) {};

public:
    mutable std::shared_ptr<Material> material;

private:
    GeometricObjectType _type;
    bool _has_bounding_box;
    bool _bounding_box_enabled;
    bool _visible;
    bool _shadows;
    AABBox _bounding_box;
    NormalType _normal_type;

protected:
    // Both _inv_surface_area and _surface_sampler
    // are only used for area lighting.
    float _inv_surface_area;
    mutable std::shared_ptr<Sampler> _surface_sampler;
};
}

#endif