#include "model.h"
#include <iostream>

// Intersects the index-th tri on this model
Hit Model::Intersect(int index, Ray ray, float start, float end)
{
	return Hit();
}

// Intersects the given ray with the model and returns the closest hit, if any
Hit Model::Intersect(Ray ray, float start, float end)
{
	// Store the best hit
	Hit bestHit = Hit();

	// Check intersections in every vertice of every tri in the tetrahedron
	for (int i = 0; i < numTris; i++) {
		Hit tempHit = Intersect(i, ray, start, end);

		//std::cout << "Checking for best hit. Current hit data: BestHit: [" << bestHit.dist << "], TempHit: [" << tempHit.dist << "]" << std::endl;
		// If the new hit is valid, check if it is the best solution
		if ((tempHit.dist < bestHit.dist || bestHit.dist < 0) && tempHit.dist > start && tempHit.dist < end) {
			//std::cout << "Found new best, before: BestHit: [" << bestHit.dist << "], TempHit: [" << tempHit.dist << "];    ";
			bestHit = tempHit;
			//std::cout << "After: BestHit: [" << bestHit.dist << "], TempHit: [" << tempHit.dist << "]" << std::endl;
		}
		//std::cout << "After comparing: BestHit: [" << bestHit.dist << "], TempHit: [" << tempHit.dist << "]" << std::endl;
	}

	return bestHit;
}

Model::Model() : mat(Material()) {}
Model::Model(Material _mat) : mat(_mat) {}

Model::Model(MatType _matT, glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka)
{
	mat = Material(_matT, _kd, _ks, _ka);
}

Model::~Model() {}