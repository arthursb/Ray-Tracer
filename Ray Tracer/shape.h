#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <cmath>

#include "vector3.h"
#include "ray.h"
#include "light.h"
#include "color.h"
#include "material.h"
#include "intersection.h"

class Intersection;

class Shape{
public:
	Material material;
	
	virtual ~Shape() { }

	virtual bool intersect(Intersection& intersection) = 0;
	
	virtual Color getColor(const Point& contactPoint, const Point& observerPoint, Light& light) = 0;
	virtual Color getAmbientColor() = 0;
	virtual Color getSpecularColor(const Point& contactPoint, const Point& observerPoint, Light& light) = 0;
	virtual Color getDiffuseColor(const Point& contactPoint, const Point& observerPoint, Light& light) = 0;
	
	virtual Vector3 getNormal(const Point& contactPoint) = 0;
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
