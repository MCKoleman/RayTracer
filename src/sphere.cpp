/* Formula for ray-sphere intersection when the sphere is not positioned at the origin
 * was derived using help from:
 * https://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/
 * The formula (A+tB-c).(A+tB-c)=r^2 was taken from the guide
 */

#include "sphere.h"

// Checks whether the ray intersects with the sphere, returning the t value of where it intersects
Hit Sphere::Intersect(Ray ray, float start, float end)
{
	/* t ^ 2 d.d + 2t d.(p - c) + (p - c).(p - c) - r ^ 2 = 0
	 * a*t^2 + b*t + c
	 * a = d.d
	 * b = 2 d.(p-c)
	 * c = (p-c).(p-c) - r^2
	 * t = (-b +- sqrt(b^2 -4ac))/2a
	 */
	glm::vec3 dist = ray.pos - position;
	float a = glm::dot(ray.dir, ray.dir);
	float b = 2 * dot(ray.dir, dist);
	float c = dot(dist, dist) - radius * radius;
	float disc = b * b - 4 * a * c;

	// The ray must miss if the discriminant is less than zero
	if (disc < 0) {
		return Hit();
	}
	// If the ray doesn't miss, return the best intersection position
	else {
		// Return t as long as it is within the bounds given
		float t = (-b - sqrt(disc)) / (2 * a);
		if (t > start && t < end) {
			// return the normal vector of the intersection N(P - C)
			return Hit(this, ray.GetPos(t), glm::normalize(ray.GetPos(t) - position), t);
		}
		// If t is out of bounds, return default hit (-1)
		else {
			return Hit();
		}
	}
}

Sphere::Sphere()
{
	position = glm::vec3(0,0,0);
	radius = 1.0f;
}

Sphere::Sphere(glm::vec3 _pos, float _rad) : position(_pos), radius(_rad) {}

Sphere::Sphere(glm::vec3 _pos, float _rad, Material _mat) : position(_pos), radius(_rad)
{
	mat = _mat;
}

Sphere::Sphere(glm::vec3 _pos, float _rad, MatType _matT, glm::vec3 _kd, glm::vec3 _ks, glm::vec3 _ka) : Sphere(_pos, _rad)
{
	mat = Material(_matT, _kd, _ks, _ka);
}

Sphere::~Sphere() {}