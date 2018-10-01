#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <cmath>

#include "vector3.h"
#include "ray.h"
#include "light.h"
#include "color.h"
#include "intersection.h"

class Intersection;

class Shape{
public:
	virtual ~Shape() { }

	virtual bool intersect(Intersection& intersection) = 0;
	virtual Color getFinalColor(const Point& contactPoint, const Point& observerPoint, const Light& light) = 0;
};

class ShapeSet{
protected:
	std::vector<Shape*> shapes;
	
public:
	ShapeSet();
	
	virtual ~ShapeSet();
	
	void addShape(Shape* shape);
	
	virtual bool intersect(Intersection& intersection);
};

#endif // SHAPE_H
