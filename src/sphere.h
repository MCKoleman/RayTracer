#include "model.h"
#pragma once

class Sphere : public Model {

public:
	glm::vec3 position;
	float radius;

	Hit Intersect(Ray ray, float start, float end);

	Sphere();
	Sphere(glm::vec3 _pos, float _rad);
	Sphere(glm::vec3 _pos, float _rad, Material _mat);
	Sphere(glm::vec3 _pos, float _rad, MatType _matT, glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka);
	~Sphere();
};