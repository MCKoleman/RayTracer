#include <glm/vec3.hpp>
#include "camera.h"
#include "material.h"
#include "hit.h"
#pragma once

class Model {
public:
	Material mat;

	virtual Hit Intersect(Ray ray, float start, float end);

	// Default
	Model();
	Model(Material _mat);
	Model(MatType _matT, glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka);
	~Model();
};