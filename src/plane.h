#include "model.h"
#pragma once

const int PLANE_VERTS = 4;

class Plane : public Model {
	glm::vec3 vertices[PLANE_VERTS];
	glm::vec3 normal;
	glm::vec3 center;

public:
	void CalcNormal();
	Hit Intersect(Ray ray, float start, float end);

	Plane();
	Plane(glm::vec3 _center, float _width, float _length, Material _mat);
	Plane(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, Material _mat);
	Plane(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, MatType _matT, glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka);
	~Plane();
};