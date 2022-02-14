/* Logic for plane ray intersection was taken from
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
 */

#include "plane.h"
#include <iostream>

// Returns the intersection between the given ray and this plane
Hit Plane::Intersect(Ray ray, float start, float end)
{
	float denom = glm::dot(normal, ray.dir);

	// If denominator l.n is close to zero, the ray misses
	if (denom > 0.00001f) {
		float t = glm::dot(center - ray.pos, normal) / denom;

		// If t is valid and in range, it hits
		if (t > start && t < end) {
			return Hit(this, ray.GetPos(t), normal, t);
		}
	}

	return Hit();
}

// Calculates the normal for this plane
void Plane::CalcNormal()
{
	normal = glm::normalize(glm::cross(vertices[1] - vertices[0], vertices[2] - vertices[0]));
}

// Creates a default unit plane centered at the origin
Plane::Plane()
{
	vertices[0] = glm::vec3(-0.5f, -0.5f, 0);
	vertices[1] = glm::vec3(0.5f, -0.5f, 0);
	vertices[2] = glm::vec3(0.5f, 0.5f, 0);
	vertices[3] = glm::vec3(-0.5f, 0.5f, 0);
	center = glm::vec3(0, 0, 0);
	CalcNormal();
}

// Creates a plane centered at the given position, with width x, length y, and flat on the z axis
Plane::Plane(glm::vec3 _center, float _width, float _length, Material _mat)
{
	vertices[0] = _center + glm::vec3(-_width/2, -_length/2, 0);
	vertices[1] = _center + glm::vec3(_width/2, -_length/2, 0);
	vertices[2] = _center + glm::vec3(_width/2, _length/2, 0);
	vertices[3] = _center + glm::vec3(-_width/2, _length/2, 0);
	mat = _mat;
	center = _center;
	CalcNormal();
}

// Creates a plane with the given vertices and material
Plane::Plane(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, Material _mat)
{
	vertices[0] = v0;
	vertices[1] = v1;
	vertices[2] = v2;
	vertices[3] = v3;
	center = (v0 + v1 + v2 + v3) / 4.0f;
	mat = _mat;
	CalcNormal();
}

// Creates a plane with the given vertices and material components
Plane::Plane(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, MatType _matT, glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka)
{
	vertices[0] = v0;
	vertices[1] = v1;
	vertices[2] = v2;
	vertices[3] = v3;
	center = (v0 + v1 + v2 + v3) / 4.0f;
	mat = Material(_matT, _kd, _ks, _ka);
	CalcNormal();
}

// Destructor
Plane::~Plane() {}