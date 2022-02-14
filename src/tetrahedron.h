/* Formula for calculating surface normals for triangles was taken from
 * https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal
 */

#include "model.h"
#include "tri.h"
#pragma once

const int TETRA_TRIS = 4;

class Tetrahedron : public Model {
	Tri tris[TETRA_TRIS];
public:
	Hit Intersect(Ray ray, float start, float end);

	Tetrahedron();
	Tetrahedron(glm::vec3 center, float size);
	Tetrahedron(glm::vec3 center, float size, Material _mat);
	Tetrahedron(glm::vec3 center, float size, MatType _matT, glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka);
	Tetrahedron(Tri*& _tris);
	Tetrahedron(Tri& tri1, Tri& tri2, Tri& tri3, Tri& tri4);
	~Tetrahedron();
};