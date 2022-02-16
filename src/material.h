#include <glm/vec3.hpp>
#pragma once

enum class MatType { Lambert, Blinn, Mirror };

struct Material {
	MatType matType;
	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 ka;
	glm::vec3 km;
	unsigned int p = 1;
	unsigned int maxR = 0;

	Material();
	Material(MatType _matType);
	Material(MatType _matType, glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka);
};

struct Lambert : public Material {
	Lambert(glm::vec3 _kd, glm::vec3 _ka);
};

struct Blinn : public Material {
	Blinn(glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka, unsigned int _p);
};

struct Mirror : public Material {
	Mirror(glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka, glm::vec3 _km, unsigned int _p, unsigned int _maxR);
};