/* Formula for triangle-ray intersection taken from
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
 */

#include <iostream>
#include "tetrahedron.h"
using namespace glm;

Hit Tetrahedron::Intersect(int index, Ray ray, float start, float end)
{
	return tris[index].Intersect(this, ray, start, end);
}

// Creates a regular tetrhedron centered at the origin with edge length 1
Tetrahedron::Tetrahedron()
{
	tris[0] = Tri(vec3(sqrt(8/9), 0, -1/3), vec3(-sqrt(2/9), sqrt(2/3), -1/3), vec3(0, 0, 1));
	tris[1] = Tri(vec3(sqrt(8/9), 0, -1/3), vec3(-sqrt(2/9), -sqrt(2/3), -1/3), vec3(0, 0, 1));
	tris[2] = Tri(vec3(-sqrt(2/9), sqrt(2/3), -1/3), vec3(-sqrt(2/9), -sqrt(2/3), -1/3), vec3(0, 0, 1));
	tris[3] = Tri(vec3(sqrt(8/9), 0, -1/3), vec3(-sqrt(2/9), sqrt(2/3), -1/3), vec3(-sqrt(2/9), -sqrt(2/3), -1/3));
	numTris = TETRA_TRIS;
}

// Creates a tetrahedron with 
Tetrahedron::Tetrahedron(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, Material _mat)
{
	mat = _mat;
	tris[0] = Tri(v0, v1, v2);
	tris[1] = Tri(v0, v1, v3);
	tris[2] = Tri(v0, v2, v3);
	tris[3] = Tri(v1, v2, v3);
	numTris = TETRA_TRIS;

	/*
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
	*/
}

// Creates a regular tetrahedron centered at the given position with the given size
Tetrahedron::Tetrahedron(vec3 center, float size)
{
	// y as top
	vec3 v0 = vec3(0.9428f * size + center.x, center.y - size / 3, center.z);
	vec3 v1 = vec3(-0.4714f * size + center.x, center.y + size / 3, center.z - 0.8165f * size);
	vec3 v2 = vec3(-0.4714f * size + center.x, center.y - size / 3, center.z - 0.8165f * size);
	vec3 v3 = vec3(center.x, center.y + size, center.z);

	// z as top
	//vec3 v0 = vec3(center.x, center.y, center.z + size);
	//vec3 v1 = vec3(0.9428f * size + center.x, center.y, center.z - size / 3);
	//vec3 v2 = vec3(-0.4714f * size + center.x, center.y + 0.8165f * size, center.z - size / 3);
	//vec3 v3 = vec3(-0.4714f * size + center.x, center.y - 0.8165f * size, center.z - size / 3);

	tris[0] = Tri(v0, v1, v2);
	tris[1] = Tri(v0, v1, v3);
	tris[2] = Tri(v0, v2, v3);
	tris[3] = Tri(v1, v2, v3);
	numTris = TETRA_TRIS;

	/*
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
	*/
}

Tetrahedron::Tetrahedron(vec3 center, float size, Material _mat) : Tetrahedron(center, size)
{
	mat = _mat;
}

Tetrahedron::Tetrahedron(glm::vec3 center, float size, MatType _matT, glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka)
	: Tetrahedron(center, size)
{
	mat = Material(_matT, _kd, _ks, _ka);
}

// Creates a tetrahedron with the first 4 of the given tris
Tetrahedron::Tetrahedron(Tri* _tris)
{
	tris[0] = _tris[0];
	tris[1] = _tris[1];
	tris[2] = _tris[2];
	tris[3] = _tris[3];
	numTris = TETRA_TRIS;
}

// Creates a tetrahedron out of the 4 given tris
Tetrahedron::Tetrahedron(Tri tri1, Tri tri2, Tri tri3, Tri tri4, Material _mat)
{
	tris[0] = tri1;
	tris[1] = tri2;
	tris[2] = tri3;
	tris[3] = tri4;
	numTris = TETRA_TRIS;
	mat = _mat;
}

// Destructor
Tetrahedron::~Tetrahedron() {}