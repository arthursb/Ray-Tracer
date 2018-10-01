#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"
#include "ray.h"

class Camera{
public:
	Point origin;
	Vector3 forward;
	Vector3 up;
	Vector3 right;
	
	float h;
	float w;
	
	Camera(Point origin, Vector3 target, Vector3 upguide, float fieldOfView, float aspectRatio);
	virtual ~Camera() { }

	virtual Ray makeRay(float x, float y);
};

#endif // CAMERA_H
