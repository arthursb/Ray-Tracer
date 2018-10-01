#ifndef INTERSECT_H
#define INTERSECT_H

#include "shape.h"
#include "material.h"
#include "ray.h"

class Shape;
class Material;

struct Intersection{
	Ray ray;
	float t;
	Shape *pShape;

	Intersection();
	Intersection(const Intersection& i);
	Intersection(const Ray& ray);
	
	virtual ~Intersection();
	
	Intersection& operator =(const Intersection& i);
	
	bool intersected() const;
	Point position() const;
};

#endif
