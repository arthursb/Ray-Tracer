#include <vector>

#include "plane.h"

Plane::Plane(const Point& position, const Vector3& normal, const Material& material){
	this->position = position;
	this->normal = normal;
	this->material = material;
}

Plane::~Plane(){
}

bool Plane::intersect(Intersection& intersection){
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
	
	intersection.t = t;
	intersection.pShape = this;
	
	return true;
}

// I = ka * Ia + kd * Id + ks * Is
Color Plane::getColor(const Point& contactPoint, const Point& observerPoint, Light& light){
	Color ambient = getAmbientColor();
	Color diffuse = getDiffuseColor(contactPoint, observerPoint, light);
	Color specular = getSpecularColor(contactPoint, observerPoint, light);
	
	Color finalColor = ambient + diffuse + specular;
	finalColor.clamp();
	
	return finalColor;
}

Color Plane::getAmbientColor(){
	Color ambient = this->material.kAmbient * this->material.color;
	ambient.clamp();
	
	return ambient;
}

Color Plane::getDiffuseColor(const Point& contactPoint, const Point& observerPoint, Light& light){
	Vector3 n = this->normal;
	Vector3 l = (light.position - contactPoint).normalized();
	Vector3 v = (observerPoint - contactPoint).normalized();
	
	Color diffuse = this->material.kDiffuse * this->material.color * light.color * (dot(n, l));
	
	return diffuse;
}

Color Plane::getSpecularColor(const Point& contactPoint, const Point& observerPoint, Light& light){
	Vector3 n = this->normal;
	Vector3 l = (light.position - contactPoint).normalized();
	Vector3 v = (observerPoint - contactPoint).normalized();
	
	float specCalc = std::pow(2 * dot(n, l) * dot (n, v) - dot(v, l), this->material.shininess);
	Color specular = this->material.kSpecular * light.color * specCalc;
	
	return specular;
}

Vector3 Plane::getNormal(const Point& contactPoint){
	return normal;
}
