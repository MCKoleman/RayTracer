/* Formula for triangle-ray intersection taken from
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
 */

#include <iostream>
#include "tetrahedron.h"
using namespace glm;

// Checks for intersections between the ray and the tetrahedron
Hit Tetrahedron::Intersect(Ray ray, float start, float end)
{
	// (p + td - a).n = 0
	// t = (a - p).n/(d.n)
	float t = -1.0f;
	vec3 bestNormal;

	// Check intersections in every vertice of every tri in the tetrahedron
	for (size_t i = 0; i < TETRA_TRIS; i++) {
		// t = (v0 - p).n/d.n
		// Calculate n.d
		float denom = dot(tris[i].normal, ray.dir);

		// If the denominator of the potential t is 0 the ray is parallel to the plane and misses
		//std::cout << "Denominator of intersection: " << denom << std::endl;
		if (denom < 0.00001f && denom > -0.00001f) {
			continue;
		}

		// Find the time of intersection along the ray
		float tempT = (dot(tris[i].normal, tris[i].vertices[0] - ray.pos)) / denom;

		// Find the point of intersection
		vec3 p = ray.GetPos(tempT);
		//float tempT = dot(tris[i].vertices[j] - ray.pos, tris[i].normal)/dot(ray.dir, tris[i].normal);

		// Conditions for the point of intersection being inside the triangle
		// ((b-a)x(p-a)).n > 0
		// ((c-b)x(p-b)).n > 0
		// ((a-c)x(p-c)).n > 0

		// Check if the intersection is inside the triangle or not
		// -------------------------------------------------------
		if (dot(cross(tris[i].vertices[1] - tris[i].vertices[0], p - tris[i].vertices[0]), tris[i].normal) <= 0) {
			continue;
		}
		else if (dot(cross(tris[i].vertices[2] - tris[i].vertices[1], p - tris[i].vertices[1]), tris[i].normal) <= 0) {
			continue;
		}
		else if (dot(cross(tris[i].vertices[0] - tris[i].vertices[2], p - tris[i].vertices[2]), tris[i].normal) <= 0) {
			continue;
		}

		//std::cout << "Comparing t values: temp[" << tempT << "], best [" << t << "]" << std::endl;
		// If the new t is valid, check if it is the best solution
		if (tempT > start && tempT < end) {
			// If there is no previous solution, use the new t, otherwise pick the better solution
			if (tempT < t || t < 0) {
				t = tempT;
				bestNormal = tris[i].normal;
			}
		}
	}

	// Return a miss if t is not valid
	if (t < 0) {
		return Hit();
	}
	// Otherwise return full hit result
	else {
		return Hit(this, ray.GetPos(t), bestNormal, t);
	}
}

// Creates a regular tetrhedron centered at the origin with edge length 1
Tetrahedron::Tetrahedron()
{
	tris[0] = Tri(vec3(sqrt(8/9), 0, -1/3), vec3(-sqrt(2/9), sqrt(2/3), -1/3), vec3(0, 0, 1));
	tris[1] = Tri(vec3(sqrt(8/9), 0, -1/3), vec3(-sqrt(2/9), -sqrt(2/3), -1/3), vec3(0, 0, 1));
	tris[2] = Tri(vec3(-sqrt(2/9), sqrt(2/3), -1/3), vec3(-sqrt(2/9), -sqrt(2/3), -1/3), vec3(0, 0, 1));
	tris[3] = Tri(vec3(sqrt(8/9), 0, -1/3), vec3(-sqrt(2/9), sqrt(2/3), -1/3), vec3(-sqrt(2/9), -sqrt(2/3), -1/3));
}

// Creates a regular tetrahedron centered at the given position with the given size
Tetrahedron::Tetrahedron(vec3 center, float size)
{
	vec3 v0 = vec3(center.x, center.y, center.z + size);
	vec3 v1 = vec3(0.9428f * size + center.x, center.y, center.z - size / 3);
	vec3 v2 = vec3(-0.4714f * size + center.x, center.y + 0.8165f * size, center.z - size / 3);
	vec3 v3 = vec3(-0.4714f * size + center.x, center.y - 0.8165f * size, center.z - size / 3);

	tris[0] = Tri(v0, v1, v2);
	tris[1] = Tri(v0, v1, v3);
	tris[2] = Tri(v0, v2, v3);
	tris[3] = Tri(v1, v2, v3);

	std::cout << "Tetrahedron: [N{" << tris[0].normal.x << ", " << tris[0].normal.y << ", " << tris[0].normal.z << "}; ";
	std::cout << "x{" << tris[0].vertices[0].x << ", " << tris[0].vertices[0].y << ", " << tris[0].vertices[0].z << "}; ";
	std::cout << "y{" << tris[0].vertices[1].x << ", " << tris[0].vertices[1].y << ", " << tris[0].vertices[1].z << "}; ";
	std::cout << "z{" << tris[0].vertices[2].x << ", " << tris[0].vertices[2].y << ", " << tris[0].vertices[2].z << "}; " << std::endl;

	std::cout << "N{" << tris[1].normal.x << ", " << tris[1].normal.y << ", " << tris[1].normal.z << "}; ";
	std::cout << "x{" << tris[1].vertices[0].x << ", " << tris[1].vertices[0].y << ", " << tris[1].vertices[0].z << "}; ";
	std::cout << "y{" << tris[1].vertices[1].x << ", " << tris[1].vertices[1].y << ", " << tris[1].vertices[1].z << "}; ";
	std::cout << "z{" << tris[1].vertices[2].x << ", " << tris[1].vertices[2].y << ", " << tris[1].vertices[2].z << "}; " << std::endl;

	std::cout << "N{" << tris[2].normal.x << ", " << tris[2].normal.y << ", " << tris[2].normal.z << "}; ";
	std::cout << "x{" << tris[2].vertices[0].x << ", " << tris[2].vertices[0].y << ", " << tris[2].vertices[0].z << "}; ";
	std::cout << "y{" << tris[2].vertices[1].x << ", " << tris[2].vertices[1].y << ", " << tris[2].vertices[1].z << "}; ";
	std::cout << "z{" << tris[2].vertices[2].x << ", " << tris[2].vertices[2].y << ", " << tris[2].vertices[2].z << "}; " << std::endl;

	std::cout << "N{" << tris[3].normal.x << ", " << tris[3].normal.y << ", " << tris[3].normal.z << "}; ";
	std::cout << "x{" << tris[3].vertices[0].x << ", " << tris[3].vertices[0].y << ", " << tris[3].vertices[0].z << "}; ";
	std::cout << "y{" << tris[3].vertices[1].x << ", " << tris[3].vertices[1].y << ", " << tris[3].vertices[1].z << "}; ";
	std::cout << "z{" << tris[3].vertices[2].x << ", " << tris[3].vertices[2].y << ", " << tris[3].vertices[2].z << "}; " << std::endl;
}

Tetrahedron::Tetrahedron(vec3 center, float size, Material _mat) : Tetrahedron(center, size)
{
	mat = _mat;
}

Tetrahedron::Tetrahedron(glm::vec3 center, float size, MatType _matT, glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka)
{
	mat = Material(_matT, _kd, _ks, _ka);
}

// Creates a tetrahedron with the first 4 of the given tris
Tetrahedron::Tetrahedron(Tri*& _tris)
{
	tris[0] = _tris[0];
	tris[1] = _tris[1];
	tris[2] = _tris[2];
	tris[3] = _tris[3];
}

// Creates a tetrahedron out of the 4 given tris
Tetrahedron::Tetrahedron(Tri& tri1, Tri& tri2, Tri& tri3, Tri& tri4)
{
	tris[0] = tri1;
	tris[1] = tri2;
	tris[2] = tri3;
	tris[3] = tri4;
}

// Destructor
Tetrahedron::~Tetrahedron() {}