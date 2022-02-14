#include "material.h"

Material::Material() : matType(MatType::Lambert), kd(glm::vec3()), ks(glm::vec3()), ka(glm::vec3()) {}

Material::Material(MatType _matType) : matType(_matType), kd(glm::vec3()), ks(glm::vec3()), ka(glm::vec3()) {}

Material::Material(MatType _matType, glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka)
	: matType(_matType), kd(_kd), ks(_ks), ka(_ka) {}

Lambert::Lambert(glm::vec3 _kd, glm::vec3 _ka)
{
	matType = MatType::Lambert;
	kd = _kd;
	ka = _ka;
	ks = glm::vec3(0, 0, 0);
	p = 1;
	maxR = 0;
}

Blinn::Blinn(glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka, unsigned int _p)
{
	matType = MatType::Blinn;
	kd = _kd;
	ka = _ka;
	ks = _ks;
	p = _p;
	maxR = 0;
}

Mirror::Mirror(glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka, unsigned int _p, unsigned int _maxR)
{
	matType = MatType::Mirror;
	kd = _kd;
	ka = _ka;
	ks = _ks;
	p = _p;
	maxR = _maxR;
}