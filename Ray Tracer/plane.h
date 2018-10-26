#ifndef PLANE_H
#define PLANE_H

#include "shape.h"
#include "material.h"

//(ˆr - p) dot n = 0 para que ˆr pertença ao plano
// ^r é um ponto
// p é um ponto pertencente ao plano
// n é a normal do plano

// um ponto de interseção pertence ao raio e ao plano, então:
// ponto = origem + direção * t
// (ponto plano - ponto) dot normal = 0
// t * (direção dot n) = (ponto plano dot n - origem dot n)
// t = (ponto plano dot n - origem dot n) / (direção dot n)
class Plane : public Shape{
public:
	Point position;
	Vector3 normal;
	
	Plane(const Point& position, const Vector3& normal, const Material& material);
	
	virtual ~Plane();
	
	virtual bool intersect(Intersection& intersection);
	
	virtual Color getColor(const Point& contactPoint, const Point& observerPoint, Light& light);
	virtual Color getAmbientColor();
	virtual Color getSpecularColor(const Point& contactPoint, const Point& observerPoint, Light& light);
	virtual Color getDiffuseColor(const Point& contactPoint, const Point& observerPoint, Light& light);
	
	virtual bool isMirror();
	virtual bool isTransparent();
	
	virtual Vector3 getNormal(const Point& contactPoint);

};

#endif //PLANE_H
