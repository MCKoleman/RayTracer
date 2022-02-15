#include "scene.h"

// Adds an empty model to the scene
void Scene::AddModel()
{
	Model* tempModel = new Model();
	models.push_back(tempModel);
}

// Adds the given model to the scene
void Scene::AddModel(Model* _model)
{
	models.push_back(_model);
}

// Removes the model at the given index from the scene, deleting it
void Scene::RemoveModel(size_t index)
{
	Model* tempModel = models[index];
	models.erase(models.begin()+index);
	delete tempModel;
}

// Returns the model at the given index
Model* Scene::Get(size_t index)
{
	return models[index];
}

// Returns the number of models in the scene
size_t Scene::Size()
{
	return models.size();
}

// Toggles the orthographic status of the camera
void Scene::ToggleOrth()
{
	camera->SetIsOrth(!camera->isOrthographic);
}

// Moves the camera by the given displacement
void Scene::MoveCamera(glm::vec3 disp)
{
	camera->Move(disp);
}

// Rotates the camera by the given displacement
void Scene::RotateCamera(glm::vec3 disp)
{
	camera->Rotate(disp);
}

// Returns the ray of the given pixel based on the current camera viewpoint
Ray Scene::GetRay(int x, int y, int width, int height)
{
	return camera->GetRay(x, y, width, height);
}

// Returns the Hit struct of the first object hit by the given ray
Hit Scene::Intersect(Ray ray, float start, float end)
{
	// Creates a default hit struct, aka a miss
	Hit hit = Hit();

	// Check each model in the scene for a hit
	for (int i = 0; i < models.size(); i++) {
		Hit tempHit = models[i]->Intersect(ray, start, end);

		// If a model was hit closer than the previous closest hit, store that instead
		if ((tempHit.dist < hit.dist || hit.dist < 0) && tempHit.dist > 0) {
			hit = tempHit;
		}
	}
	return hit;
}

// Overload for getting the model at the given index
Model*& Scene::operator[](size_t index)
{
	return models[index];
}

// Default constructor
Scene::Scene() : bgColor(glm::vec3(0,0,0))
{
	camera = new Camera();
	light = new Light();
}

Scene::Scene(Camera* _camera) : camera(_camera), bgColor(glm::vec3(0, 0, 0))
{
	light = new Light();
}

Scene::Scene(Camera* _camera, Light* _light, glm::vec3 _bgColor) : camera(_camera), light(_light), bgColor(_bgColor) {}

// Initializes the scene with the given models
Scene::Scene(std::vector<Model*>& _models) : models(_models), bgColor(glm::vec3(0, 0, 0))
{
	camera = new Camera();
	light = new Light();
}

// Destructor
Scene::~Scene() 
{
	// Clear all models
	for(size_t i = models.size(); i --> 0;)
	{
		RemoveModel(i);
	}
	models.clear();

	delete camera;
	delete light;
}