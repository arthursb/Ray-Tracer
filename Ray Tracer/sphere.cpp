#include "sphere.h"

Sphere::Sphere(const Point& center, float radius, const Material& material){
	this->center = center;
	this->radius = radius;
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
Color Sphere::getColor(const Point& contactPoint, const Point& observerPoint, Light& light){
	Color ambient = getAmbientColor();
	Color diffuse = getDiffuseColor(contactPoint, observerPoint, light);
	Color specular = getSpecularColor(contactPoint, observerPoint, light);
	
	Color finalColor = ambient + diffuse + specular;
	finalColor.clamp();
	
	return finalColor;
}

Color Sphere::getAmbientColor(){
	Color ambient = this->material.kAmbient * this->material.color;
	ambient.clamp();
	
	return ambient;
}

Color Sphere::getDiffuseColor(const Point& contactPoint, const Point& observerPoint, Light& light){
	Vector3 n = (contactPoint - this->center).normalized();
	Vector3 l = (light.position - contactPoint).normalized();
	Vector3 v = (observerPoint - contactPoint).normalized();
	
	Color diffuse = this->material.kDiffuse * this->material.color * light.color * (dot(n, l));
	
	return diffuse;
}

Color Sphere::getSpecularColor(const Point& contactPoint, const Point& observerPoint, Light& light){
	Vector3 n = (contactPoint - this->center).normalized();
	Vector3 l = (light.position - contactPoint).normalized();
	Vector3 v = (observerPoint - contactPoint).normalized();
	
	float specCalc = std::pow(2 * dot(n, l) * dot (n, v) - dot(v, l), this->material.shininess);
	Color specular = this->material.kSpecular * light.color * specCalc;
	
	return specular;
}

bool Sphere::isMirror(){
	return this->material.isMirror;
}

bool Sphere::isTransparent(){
	return this->material.isTransparent;
}

Vector3 Sphere::getNormal(const Point& contactPoint){
	return (contactPoint - this->center).normalized();
}

