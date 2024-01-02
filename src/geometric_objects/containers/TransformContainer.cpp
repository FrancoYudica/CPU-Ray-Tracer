#include "TransformContainer.hpp"

RT::GeometricObjects::TransformContainer::TransformContainer()
    : Container(GeometricObjectType::TransformContainer)
{
    enable_bounding_box();

    _container = std::make_shared<Container>();
    _instance = std::make_shared<Instance>(_container);
}

void RT::GeometricObjects::TransformContainer::add(const GeometricObjectPtr& object)
{
    _container->add(object);
}

bool RT::GeometricObjects::TransformContainer::remove(const GeometricObjectPtr& object)
{
    return _container->remove(object);
}

void RT::GeometricObjects::TransformContainer::clear()
{
    _container->clear();
}

// Wrapper methods over RT::Instance
bool RT::GeometricObjects::TransformContainer::hit(const Ray& ray, double& tmin, ShadeRec& record) const
{
    return _instance->hit(ray, tmin, record);
}

bool RT::GeometricObjects::TransformContainer::shadow_hit(const Ray& ray, double& tmin) const
{
    return _instance->shadow_hit(ray, tmin);
}

void RT::GeometricObjects::TransformContainer::recalculate_bounding_box()
{
    _instance->recalculate_bounding_box();
    set_bounding_box(_instance->get_bounding_box());
}

void RT::GeometricObjects::TransformContainer::set_translation(const Vec3& translation)
{
    _instance->set_translation(translation);
}

void RT::GeometricObjects::TransformContainer::set_scale(const Vec3& scale)
{
    _instance->set_scale(scale);
}

void RT::GeometricObjects::TransformContainer::set_rotation_x(const double& rotation)
{
    _instance->set_rotation_x(rotation);
}

void RT::GeometricObjects::TransformContainer::set_rotation_y(const double& rotation)
{
    _instance->set_rotation_y(rotation);
}

void RT::GeometricObjects::TransformContainer::set_rotation_z(const double& rotation)
{
    _instance->set_rotation_z(rotation);
}

void RT::GeometricObjects::TransformContainer::set_transform_the_texture(bool transform)
{
    _instance->set_transform_the_texture(transform);
}

RT::Vec3 RT::GeometricObjects::TransformContainer::get_translation() const
{
    return _instance->get_translation();
}

RT::Vec3 RT::GeometricObjects::TransformContainer::get_scale() const
{
    return _instance->get_scale();
}

RT::Vec3 RT::GeometricObjects::TransformContainer::get_rotation() const
{
    return _instance->get_rotation();
}

bool RT::GeometricObjects::TransformContainer::get_transform_the_texture() const
{
    return _instance->get_transform_the_texture();
}
