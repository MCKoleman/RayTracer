/* Logic for plane ray intersection was taken from
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
 */

#include "plane.h"
#include <iostream>

// Returns the intersection between the given ray and this plane
Hit Plane::Intersect(int index, Ray ray, float start, float end)
{
	return tris[index].Intersect(this, ray, start, end);
}

// Creates a default unit plane centered at the origin
Plane::Plane()
{
	glm::vec3 v0 = glm::vec3(-0.5f, 0, -0.5f);
	glm::vec3 v1 = glm::vec3(0.5f, 0, -0.5f);
	glm::vec3 v2 = glm::vec3(0.5f, 0, 0.5f);
	glm::vec3 v3 = glm::vec3(-0.5f, 0, 0.5f);
	tris[0] = Tri(v0, v1, v3);
	tris[1] = Tri(v1, v2, v3);
	center = glm::vec3(0, 0, 0);
	numTris = PLANE_TRIS;
}

// Creates a plane centered at the given position, with width x, length y, and flat on the z axis
Plane::Plane(glm::vec3 _center, float _width, float _length, Material _mat)
{
	glm::vec3 v0 = _center + glm::vec3(-_width/2, 0, -_length/2);
	glm::vec3 v1 = _center + glm::vec3(_width/2, 0, -_length/2);
	glm::vec3 v2 = _center + glm::vec3(_width/2, 0, _length/2);
	glm::vec3 v3 = _center + glm::vec3(-_width/2, 0, _length/2);
	tris[0] = Tri(v0, v1, v3);
	tris[1] = Tri(v1, v2, v3);
	mat = _mat;
	center = _center;
	numTris = PLANE_TRIS;
}

// Creates a plane with the given tris
Plane::Plane(Tri t0, Tri t1, Material _mat)
{
	tris[0] = t0;
	tris[1] = t1;
	mat = _mat;
	center = (t0.vertices[0] + t0.vertices[1] + t0.vertices[2] + t1.vertices[0] + t1.vertices[1] + t1.vertices[2]) / 6.0f;
	numTris = PLANE_TRIS;
}

// Plane constructor
Plane::Plane(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
	tris[0] = Tri(v0, v1, v3);
	tris[1] = Tri(v1, v2, v3);
	center = (v0 + v1 + v2 + v3) / 4.0f;
	numTris = PLANE_TRIS;
}

// Creates a plane with the given vertices and material
Plane::Plane(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, Material _mat)
	: Plane(v0, v1, v2, v3)
{
	mat = _mat;
}

// Creates a plane with the given vertices and material components
Plane::Plane(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, MatType _matT, glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka)
	: Plane(v0, v1, v2, v3)
{
	mat = Material(_matT, _kd, _ks, _ka);
}

// Destructor
Plane::~Plane() {}