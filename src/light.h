#include <glm/vec3.hpp>
#pragma once

class Light {
public:
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 ia;
	float intensity;

	Light();
	Light(glm::vec3 _pos, glm::vec3 _dir);
	Light(glm::vec3 _pos, glm::vec3 _dir, glm::vec3 _ia, float _intensity);
};