#include <vector>
#include "model.h"
#include "camera.h"
#include "light.h"
#include "hit.h"
#include "options.h"
#pragma once

class Scene {
	std::vector<Model*> models;
	Camera* camera;

public:
	// Variables
	glm::vec3 bgColor;
	Light* light;
	Options options;

	// Model functions
	void AddModel();
	void AddModel(Model* _model);
	void RemoveModel(size_t index);
	Model* Get(size_t index);
	size_t Size();

	// Camera functions
	void ToggleOrth();
	void MoveCamera(glm::vec3 disp);
	void RotateCamera(glm::vec3 disp);
	bool IsOrth();
	Hit Intersect(Ray ray, float start, float end);
	Ray GetRay(int x, int y, int width, int height);

	// Default functions
	Model*& operator[](size_t index);
	Scene();
	Scene(Camera* _camera);
	Scene(Camera* _camera, Light* _light, glm::vec3 _bgColor, Options _options);
	Scene(std::vector<Model*>& _models);
	~Scene();
};
