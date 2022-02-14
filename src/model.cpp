#include "model.h"

Hit Model::Intersect(Ray ray, float start, float end)
{
	return Hit();
}

Model::Model() : mat(Material()) {}
Model::Model(Material _mat) : mat(_mat) {}

Model::Model(MatType _matT, glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka)
{
	mat = Material(_matT, _kd, _ks, _ka);
}

Model::~Model() {}