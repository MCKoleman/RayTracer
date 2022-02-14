#include <glm/vec3.hpp>
#pragma once

const int TRI_VERTS = 3;

struct Tri {
	glm::vec3 vertices[TRI_VERTS];
	glm::vec3 normal;

	void CalcNormal()
	{
		// N = U x V = (p3 - p1) x (p2 - p1)
		glm::vec3 u = vertices[2] - vertices[0];
		glm::vec3 v = vertices[1] - vertices[0];
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