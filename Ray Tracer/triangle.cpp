#include <iostream>
#include "triangle.h"

Triangle::Triangle(const Point& point1, const Point& point2, const Point& point3, const Color& color, const Material& material){
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;
	
	this->position = (point1 + point2 + point3) / 3;
	
	Vector3 P2P1 = point2 - point1;
	Vector3 P3P1 = point3 - point1;
	Vector3 crossProduct = cross(P3P1, P2P1);
	this->normal = crossProduct.normalized();
	
	this->color = color;
	this->material = material;
}

Triangle::~Triangle(){
}

bool Triangle::intersect(Intersection& intersection){
	float dDotN = dot(intersection.ray.direction, normal);
	
	//paralelo ao plano = infinitas interseções
	if (dDotN == 0.0f){
		return false;
	}
	
	float t = dot(position - intersection.ray.origin, normal) / dDotN;
	
	//perto demais
	if (t <= T_MIN) {
		return false;
	}
	
	//já achei alguém mais próximo
	if (t >= intersection.t){
		return false;
	}
	
	float previousT = intersection.t;
	intersection.t = t;
	
	Point intersectionPoint = intersection.position();
	
	if(!isPointInTriangle(intersectionPoint)){
		intersection.t = previousT;
		return false;
	}
	
	intersection.t = t;
	intersection.pShape = this;
	
	return true;
}

Color Triangle::getColor(const Point& contactPoint, const Point& observerPoint, Light& light){
	Color ambient = getAmbientColor();
	Color diffuse = getDiffuseColor(contactPoint, observerPoint, light);
	Color specular = getSpecularColor(contactPoint, observerPoint, light);
	
	Color finalColor = ambient + diffuse + specular;
	finalColor.clamp();
	
	return finalColor;
}

Color Triangle::getAmbientColor(){
	Color ambient = this->material.kAmbient * this->material.color;
	ambient.clamp();
	
	return ambient;
}

Color Triangle::getDiffuseColor(const Point& contactPoint, const Point& observerPoint, Light& light){
	Vector3 n = this->normal;
	Vector3 l = (light.position - contactPoint).normalized();
	Vector3 v = (observerPoint - contactPoint).normalized();
	
	Color diffuse = this->material.kDiffuse * this->material.color * light.color * (dot(n, l));
	
	return diffuse;
}

Color Triangle::getSpecularColor(const Point& contactPoint, const Point& observerPoint, Light& light){
	Vector3 n = this->normal;
	Vector3 l = (light.position - contactPoint).normalized();
	Vector3 v = (observerPoint - contactPoint).normalized();
	
	float specCalc = std::pow(2 * dot(n, l) * dot (n, v) - dot(v, l), this->material.shininess);
	Color specular = this->material.kSpecular * light.color * specCalc;
	
	return specular;
}

Vector3 Triangle::getNormal(const Point& contactPoint){
	return normal;
}

//fonte: http://blackpawn.com/texts/pointinpoly/
bool Triangle::isPointInTriangle(Point& p){
	// Compute vectors
	Vector3 v1 = point3 - point1;
	Vector3 v2 = point2 - point1;
	Vector3 v3 = p - point1;
	
	// Compute dot products
	float dot11 = dot(v1, v1);
	float dot12 = dot(v1, v2);
	float dot13 = dot(v1, v3);
	float dot22 = dot(v2, v2);
	float dot23 = dot(v2, v3);
	
	// Compute barycentric coordinates
	float invDenom = 1 / (dot11 * dot22 - dot12 * dot12);
	float u = (dot22 * dot13 - dot12 * dot23) * invDenom;
	float v = (dot11 * dot23 - dot12 * dot13) * invDenom;
	
	// Check if point is in triangle
	return (u >= 0) && (v >= 0) && (u + v < 1);
}


