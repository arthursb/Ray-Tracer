#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"
#include "material.h"

class Triangle : public Shape{
public:
	Point point1;
	Point point2;
	Point point3;
	
	Point position;
	
	Vector3 normal;
	Color color;
	Material material;
	
	Triangle(const Point& point1, const Point& point2, const Point& point3, const Color& color, const Material& material);
	
	virtual ~Triangle();
	
	virtual bool intersect(Intersection& intersection);
	virtual Color getFinalColor(const Point& contactPoint, const Point& observerPoint, const Light& light);
	virtual Color getShadowColor();
	virtual Vector3 getNormal(const Point& contactPoint);
	
private:
	bool isPointInTriangle(Point& p);
};

#endif //TRIANGLE_H
