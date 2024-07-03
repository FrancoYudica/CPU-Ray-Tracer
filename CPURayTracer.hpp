#ifndef __RT_CPU_RAY_TRACER__
#define __RT_CPU_RAY_TRACER__

// Main files
#include "src/AABBox.hpp"
#include "src/BRDF.hpp"
#include "src/BuildFunctions.hpp"
#include "src/Camera.hpp"
#include "src/Constants.hpp"
#include "src/GeometricObject.hpp"
#include "src/Instance.hpp"
#include "src/Light.hpp"
#include "src/Material.hpp"
#include "src/math_RT.hpp"
#include "src/Random.hpp"
#include "src/Ray.hpp"
#include "src/RenderBuffer.hpp"
#include "src/Sampler.hpp"
#include "src/ShadeRec.hpp"
#include "src/Tracer.hpp"
#include "src/Types_rt.hpp"
#include "src/ViewPlane.hpp"
#include "src/World.hpp"

// BRDF
#include "src/brdf/GlossySpecular.hpp"
#include "src/brdf/Lambertian.hpp"

// Cameras
#include "src/cameras/AnaglyphCamera.hpp"
#include "src/cameras/FishEyeCamera.hpp"
#include "src/cameras/OrthographicCamera.hpp"
#include "src/cameras/PinholeCamera.hpp"
#include "src/cameras/SphericalPanoramicCamera.hpp"
#include "src/cameras/StereoCamera.hpp"
#include "src/cameras/StereoDualCamera.hpp"
#include "src/cameras/ThinLensCamera.hpp"

// Geometric objects
#include "src/geometric_objects/GeometricObjects.hpp"

// Lights
#include "src/lights/Lights.hpp"

// Materials
#include "src/materials/EmissiveMaterial.hpp"
#include "src/materials/MatteMaterial.hpp"
#include "src/materials/PhongMaterial.hpp"
#include "src/materials/PlasticMaterial.hpp"

// Samplers
#include "src/samplers/JitteredSampler.hpp"
#include "src/samplers/MultiJitteredSampler.hpp"
#include "src/samplers/NRooksSampler.hpp"
#include "src/samplers/RegularSampler.hpp"

// Tracers
#include "src/tracers/AreaLighting.hpp"
#include "src/tracers/DepthTracer.hpp"
#include "src/tracers/NormalTracer.hpp"
#include "src/tracers/RayCastTracer.hpp"


#endif