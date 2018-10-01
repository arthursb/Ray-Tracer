#ifndef RAY_H
#define RAY_H

#include "vector3.h"
#include "color.h"

#define T_MIN 0.0001f
#define T_MAX 1.0e30f

struct Ray{
	Point origin;
	Vector3 direction;
	float tMax;

	Ray();
	Ray(const Ray& r);
	Ray(const Point& origin, const Vector3& direction, float tMax);

	virtual ~Ray();

	Ray& operator =(const Ray& r);

	Point calculate(float t) const;
};

#endif // RAY_H
