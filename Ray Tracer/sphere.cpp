#include "sphere.h"
#include <iostream>
Sphere::Sphere(const Point& center, float radius, const Color& color, const Material& material){
	this->center = center;
	this->radius = radius;
	this->color = color;
	this->material = material;
}

Sphere::~Sphere(){
}

//deslocar o centro da esfera pra origem dos eixos pra facilitar as contas
bool Sphere::intersect(Intersection& intersection){
	Ray transformedRay = intersection.ray;
	transformedRay.origin -= center;

	float a = transformedRay.direction.lengthSquared();
	float b = 2 * dot(transformedRay.direction, transformedRay.origin);
	float c = transformedRay.origin.lengthSquared() - (radius * radius);
	float delta = b * b - 4 * a * c;

	if (delta < 0.0f){
		return false;
	}
	
	float t1 = (-b - std::sqrt(delta)) / (2 * a);
	float t2 = (-b + std::sqrt(delta)) / (2 * a);
	
	if (t1 > T_MIN && t1 < intersection.t){
		intersection.t = t1;
	}
	else if (t2 > T_MIN && t2 < intersection.t){
		intersection.t = t2;
	}
	else{
		return false;
	}
	
	intersection.pShape = this;
	
	return true;
}

// I = ka * Ia + kd * Id + ks * Is
Color Sphere::getFinalColor(const Point& contactPoint, const Point& observerPoint, const Light& light){
	Vector3 n = (contactPoint - this->center).normalized();
	Vector3 l = (light.position - contactPoint).normalized();
	Vector3 v = (observerPoint - contactPoint).normalized();
	
	Color ambient = this->color * this->material.kAmbient;
	Color diffuse = light.color * this->material.kAmbient * (dot(n, l));
	
	float specCalc = std::pow(2 * dot(n, l) * dot (n, v) - dot(v, l), this->material.shininess);
	Color specular = light.color * this->material.kAmbient * specCalc;
	
	Color finalColor = ambient + diffuse + specular;
	finalColor.clamp();
	
	return finalColor;
}

