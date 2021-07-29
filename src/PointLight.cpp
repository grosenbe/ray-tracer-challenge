#include "PointLight.h"

#include <cmath>
#include <stdexcept>

#include "Color.h"
#include "Tuple.h"

using namespace RTC;

PointLight::PointLight() : position(Tuple::MakePoint(0, 0, 0)), intensity(Color(0, 0, 0)) {}

PointLight::PointLight(const Tuple &aPosition, const Color &anIntensity) : position(aPosition), intensity(anIntensity) {
}

bool
PointLight::operator==(const PointLight &other) const {
  return position == other.position && intensity == other.intensity;
}

Color
RTC::Lighting(const Material &material, const PointLight &light, const Tuple &point, const Tuple &eyev, const Tuple &normalv) {
  if (!point.IsPoint())
    throw std::runtime_error("Should have passed a point to Lighting.");
  if (!eyev.IsVector() || !normalv.IsVector())
    throw std::runtime_error("Must pass vectors for the eye and normal vector parameters");

  // combine the material color with the light's surface and intensity
  Color effective_color = material.color * light.GetIntensity();

  // direction to the light source
  auto lightv = (light.GetPosition() - point).Normalize();

  // ambient contribution
  Color ambient = effective_color * material.ambient;

  // represents cosine of the angle between the light and normal vectors.
  auto light_dot_normal = Dot(lightv, normalv);

  Color diffuse(0, 0, 0), specular(0, 0, 0);
  if (light_dot_normal >= 0) {
    //A negative number would mean the light is on the other side of the surface.
    diffuse = effective_color * material.diffuse * light_dot_normal;
    auto reflectv = Reflect(Tuple::MakeVector(0, 0, 0) - lightv, normalv);
    auto reflect_dot_eye = Dot(reflectv, eyev);

    if (reflect_dot_eye <= 0) {
      specular = Color(0, 0, 0);
    } else {
      auto factor = std::pow(reflect_dot_eye, material.shininess);
      specular = light.GetIntensity() * material.specular * factor;
    }
  }
  return ambient + diffuse + specular;
}
