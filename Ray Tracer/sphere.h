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
	Material material;
	
	Sphere(const Point& center, float radius, const Material& material);
	
	virtual ~Sphere();
	
	virtual bool intersect(Intersection& intersection);
	
	virtual Color getColor(const Point& contactPoint, const Point& observerPoint, Light& light);
	virtual Color getAmbientColor();
	virtual Color getSpecularColor(const Point& contactPoint, const Point& observerPoint, Light& light);
	virtual Color getDiffuseColor(const Point& contactPoint, const Point& observerPoint, Light& light);
	
	virtual Vector3 getNormal(const Point& contactPoint);
};

#endif // SPHERE_H
