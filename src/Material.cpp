#include "Material.h"

using namespace RTC;

Material::Material() : color(Color(1, 1, 1)), ambient(0.1), diffuse(0.9), specular(0.9), shininess(200) {}

bool
Material::operator==(const Material &other) const {
  return color == other.color && ambient == other.ambient && diffuse == other.diffuse && specular == other.specular && shininess == other.shininess;
}
