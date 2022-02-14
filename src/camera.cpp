#include "camera.h"
#include <iostream>

// Returns the ray at the given relative pixel positions
Ray Camera::GetRay(int xi, int yi, int width, int height)
{
	using namespace glm;
	vec3 rectCenter = basisE - basisW;
	vec3 basisUW = (float)width * basisU;
	vec3 basisVH = (float)height * basisV;
	float u = (xi + 0.5f) / width;
	float v = (yi + 0.5f) / height;

	//vec3 bl = rectCenter - 0.5f * basisUW - 0.5f * basisVH;
	//vec3 tr = rectCenter + 0.5f * basisUW + 0.5f * basisVH;
	//vec3 pos = rectCenter + (xi - 0.5f) * basisUW + (yi - 0.5f) * basisVH;
	
	// Orthographic projection
	if (isOrthographic) {
		//std::cout << "Ray uv:" << pos.x << ", " << pos.y << ", " << pos.z << std::endl;

		// Origin: e + (u)*u + (v)*v
		vec3 origin = basisE + u * basisU + v * basisV;
		return Ray(origin, normalize(-basisW));
	}
	// Perspective projection
	else {
		// dir = -d*w + (u)*u + (v)*v
		vec3 dir = -distance(basisE, rectCenter) * basisW + u * basisU + v * basisV;
		return Ray(basisE, normalize(dir));
	}
}

// Recalulcates the basis of the camera (used for rendering)
void Camera::CalcBasis()
{
	basisW = glm::normalize(- lookAt);
	basisU = glm::normalize(glm::cross(up, basisW));
	basisV = glm::normalize(glm::cross(basisW, basisU));
	basisE = position;

	std::cout << "Camera basis: u[" << basisU.x << ", " << basisU.y << ", " << basisU.z << "]; ";
	std::cout << "v[" << basisV.x << ", " << basisV.y << ", " << basisV.z << "]; ";
	std::cout << "w[" << basisW.x << ", " << basisW.y << ", " << basisW.z << "]; ";
	std::cout << "e[" << basisE.x << ", " << basisE.y << ", " << basisE.z << "]" << std::endl;
}

// Moves the camera by the given displacement vector
void Camera::Move(glm::vec3 displacement)
{
	position = position + displacement;
	CalcBasis();
}

// Sets the camera position to the given position
void Camera::SetPos(glm::vec3 _newPos)
{
	position = _newPos;
	CalcBasis();
}

// Sets the camera's lookAt vector to the given vector
void Camera::SetLookAt(glm::vec3 _lookAt)
{
	lookAt = _lookAt;
	CalcBasis();
}

// Sets the camera's up vecetor the given vector
void Camera::SetUpVec(glm::vec3 _up)
{
	up = _up;
	CalcBasis();
}

// Sets the camera's orthographic status
void Camera::SetIsOrth(bool _isOrth)
{
	isOrthographic = _isOrth;
}

Camera::Camera() : 
	position(glm::vec3(0, 0, 0)), lookAt(glm::vec3(1, 0, 0)), up(glm::vec3(0, 0, 1)), isOrthographic(true) 
{ CalcBasis(); }

Camera::Camera(glm::vec3 _pos, glm::vec3 _lookAt, glm::vec3 _up) : 
	position(_pos), lookAt(_lookAt), up(_up), isOrthographic(true)
{ CalcBasis(); }

Camera::Camera(glm::vec3 _pos, glm::vec3 _lookAt, glm::vec3 _up, bool _isOrth) : 
	position(_pos), lookAt(_lookAt), up(_up), isOrthographic(_isOrth)
{ CalcBasis(); }

Camera::Camera(glm::vec3 _pos, glm::vec3 _lookAt, glm::vec3 _up, bool _isOrth, float _fov, glm::vec2 _aspect)
	: position(_pos), lookAt(_lookAt), up(_up), isOrthographic(_isOrth), fov(_fov), aspect(_aspect)
{
	aspectRatio = _aspect.x / _aspect.y;
	CalcBasis();
}