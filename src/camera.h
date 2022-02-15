#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vector_relational.hpp>
#include "ray.h"
#pragma once

const float NEAR_CLIP_DIST = 0.01f;
const float FAR_CLIP_DIST = 10000.0f;

class Camera {
	// Basis variables
	glm::vec3 basisU;
	glm::vec3 basisV;
	glm::vec3 basisW;
	glm::vec3 basisE;
	float aspectRatio;
	glm::mat4x4 projMat;

public:
	// Variables
	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 up;
	float fov = 90.0f;
	float near = 0.1f;
	float far = 100.0f;
	glm::vec2 aspect = glm::vec2(1,1);
	bool isOrthographic;

	// Functions
	Ray GetRay(int xi, int yi, int width, int height);
	void Move(glm::vec3 displacement);
	void Rotate(glm::vec3 displacement);
	void SetPos(glm::vec3 _newPos);
	void SetLookAt(glm::vec3 _lookAt);
	void SetUpVec(glm::vec3 _up);
	void SetIsOrth(bool _isOrth);
	void CalcBasis();

	// Constructors
	Camera();
	Camera(glm::vec3 _pos, glm::vec3 _lookAt, glm::vec3 _up);
	Camera(glm::vec3 _pos, glm::vec3 _lookAt, glm::vec3 _up, bool _isOrth);
	Camera(glm::vec3 _pos, glm::vec3 _lookAt, glm::vec3 _up, bool _isOrth, float _fov, glm::vec2 _aspect);
	Camera(glm::vec3 _pos, glm::vec3 _lookAt, glm::vec3 _up, bool _isOrth, float _fov, glm::vec2 _aspect, float _near, float _far);
};