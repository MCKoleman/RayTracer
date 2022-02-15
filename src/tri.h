#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "hit.h"
#pragma once

const int TRI_VERTS = 3;

struct Tri {
	glm::vec3 vertices[TRI_VERTS];
	glm::vec3 normal;

	// Checks for intersections between the ray and the tetrahedron
	Hit Intersect(Model* model, Ray ray, float start, float end)
	{
		using namespace glm;

		// (p + td - a).n = 0
		// t = (a - p).n/(d.n)
		// t = (v0 - p).n/d.n
		// Calculate n.d
		float denom = dot(normal, ray.dir);

		// If the denominator of the potential t is 0 the ray is parallel to the plane and misses
		if (denom < 0.00001f && denom > -0.00001f) {
			return Hit();
		}

		// Find the time of intersection along the ray
		float tempT = (dot(normal, vertices[0] - ray.pos)) / denom;

		// Find the point of intersection
		vec3 p = ray.GetPos(tempT);

		// Conditions for the point of intersection being inside the triangle
		// ((b-a)x(p-a)).n > 0
		// ((c-b)x(p-b)).n > 0
		// ((a-c)x(p-c)).n > 0

		// Check if the intersection is inside the triangle or not
		// -------------------------------------------------------
		if (dot(cross(vertices[1] - vertices[0], p - vertices[0]), normal) <= 0) {
			return Hit();
		}
		else if (dot(cross(vertices[2] - vertices[1], p - vertices[1]), normal) <= 0) {
			return Hit();
		}
		else if (dot(cross(vertices[0] - vertices[2], p - vertices[2]), normal) <= 0) {
			return Hit();
		}

		// If the new t is valid, check if it is the best solution
		if (tempT > start && tempT < end) {
			return Hit(model, ray.GetPos(tempT), normal, tempT);
		}
		// Return a miss if t is not valid
		else {
			return Hit();
		}
	}

	void CalcNormal()
	{
		// N = U x V = (p3 - p1) x (p2 - p1)
		//glm::vec3 u = vertices[2] - vertices[0];
		//glm::vec3 v = vertices[1] - vertices[0];
		//normal = glm::normalize(glm::vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x));
		normal = glm::normalize(glm::cross(vertices[1] - vertices[0], vertices[2] - vertices[0]));
	}

	Tri()
	{
		vertices[0] = glm::vec3(-0.5f, 0.5f, 0);
		vertices[1] = glm::vec3(0.5f, 0.5f, 0);
		vertices[2] = glm::vec3(0, -0.707f, 0);
		CalcNormal();
	}

	Tri(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
	{
		vertices[0] = v1;
		vertices[1] = v2;
		vertices[2] = v3;
		CalcNormal();
	}
};