#include "camera.h"

#include <cmath>

Camera::Camera(Point origin, Vector3 target, Vector3 upguide, float fieldOfView, float aspectRatio){
	this->origin = origin;
	this->forward = (target - origin).normalized();
	this->right = cross(forward, upguide).normalized();
	this->up = cross(right, forward);

	h = tan(fieldOfView);
	w = h * aspectRatio;
}

Ray Camera::makeRay(float x, float y){
	Vector3 direction = forward + x * w * right + y * h * up;

	return Ray(origin, direction.normalized(), T_MAX);
}
