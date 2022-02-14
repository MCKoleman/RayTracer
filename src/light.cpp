#include "light.h"

Light::Light() : pos(glm::vec3()), dir(glm::vec3()), intensity(1.0f), ia(glm::vec3(1,1,1)) {}
Light::Light(glm::vec3 _pos, glm::vec3 _dir) : pos(_pos), dir(_dir), intensity(1.0f), ia(glm::vec3(1,1,1)) {}
Light::Light(glm::vec3 _pos, glm::vec3 _dir, glm::vec3 _ia, float _intensity) : pos(_pos), dir(_dir), ia(_ia), intensity(_intensity) {}