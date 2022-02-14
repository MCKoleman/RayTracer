#include <glm/vec3.hpp>
#pragma once

struct Ray {
	glm::vec3 pos; //p
	glm::vec3 dir; //d

	// Returns the position of t along the ray R(t) = p + td
	glm::vec3 GetPos(float t) { return pos + t * dir; }
	Ray(glm::vec3 _pos, glm::vec3 _dir) : pos(_pos), dir(_dir) {}
};