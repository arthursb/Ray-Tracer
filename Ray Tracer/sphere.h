#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "shape.h"
#include "material.h"

// ||ponto - centro|| = raio para que um ponto esteja na esfera
// ponto = origem + direção * t para que o ponto esteja no raio
// um ponto p pertencente ao raio e a esfera
// (origem + direção * t) dot (origem + direção * t) = r * r

// equação quadrática em t
// a = ||direção|| * ||direção||
// b = 2 * (ponto dot direção)
// c = ||ponto|| ||ponto|| - raio * raio
class Sphere : public Shape{
public:
	Point center;
	float radius;
	Color color;
	Material material;
	
	Sphere(const Point& center, float radius, const Color& color, const Material& material);
	
	virtual ~Sphere();
	
	virtual bool intersect(Intersection& intersection);
	virtual Color getFinalColor(const Point& contactPoint, const Point& observerPoint, const Light& light);
	virtual Vector3 getNormal(const Point& contactPoint);
};

#endif // SPHERE_H
