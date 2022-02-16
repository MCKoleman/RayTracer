#include "camera.h"
#include <iostream>

// Returns the ray at the given relative pixel positions
Ray Camera::GetRay(int xi, int yi, int width, int height)
{
	using namespace glm;
	vec3 rectCenter = basisE - basisW;
	float canvasSize = tan(radians(fov * 0.5f));
	float u = canvasSize * (2 * (xi + 0.5f) / width - 1);// -(float)width / 2.0f;
	float v = canvasSize * (1 - 2 * (yi + 0.5f) / height ) / aspectRatio;// -(float)height / 2.0f;

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
		vec3 dir = -(far - near) * basisW + u * basisU + v * basisV;
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

	// Calculate camera to world projection matrix
	/**
	float fn = far + near;
	float f_n = far - near;
	float t = 1.0f / tan(fov / 2.0f);
	projMat = glm::mat4x4(
		glm::vec4(t / aspectRatio, 0.0f, 0.0f, 0.0f), 
		glm::vec4(0.0f, t, 0.0f, 0.0f), 
		glm::vec4(0.0f, 0.0f, -fn / f_n, -1.0f), 
		glm::vec4(0.0f, 0.0f, -2.0f * far * near / f_n, 0.0f));
	
	basisE = projMat * position.;
	/**/
}

// Moves the camera by the given displacement vector
void Camera::Move(glm::vec3 displacement)
{
	position = position + displacement;
	CalcBasis();
}

// Rotates the camera by the given displacement vector
void Camera::Rotate(glm::vec3 displacement)
{
	// Find current angles
	float tempX = atan(lookAt.x);
	float tempY = atan(lookAt.y);
	float tempZ = atan(lookAt.z);

	// Calculate new angles
	float newX = tan(glm::clamp(tempX + displacement.x, -85.0f, 85.0f));
	float newY = tan(glm::clamp(tempY + displacement.y, -85.0f, 85.0f));
	float newZ = tan(glm::clamp(tempZ + displacement.z, -85.0f, 85.0f));

	// Set new lookAt vector
	lookAt = glm::vec3(newX, newY, newZ);

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

Camera::Camera(glm::vec3 _pos, glm::vec3 _lookAt, glm::vec3 _up, bool _isOrth, float _fov, glm::vec2 _aspect, float _near, float _far)
	: Camera(_pos, _lookAt, _up, _isOrth, _fov, _aspect)
{
	near = _near;
	far = _far;
}