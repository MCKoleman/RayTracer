#pragma once

class Model;

struct Hit {
	Model* model;
	glm::vec3 pos;
	glm::vec3 normal;
	float dist;

	Hit() : model(nullptr), pos(glm::vec3(0, 0, 0)), normal(glm::vec3(0, 0, 0)), dist(-1.0f) {}
	Hit(Model* _model, glm::vec3 _pos, glm::vec3 _normal, float _dist) : model(_model), pos(_pos), normal(_normal), dist(_dist) {}
};