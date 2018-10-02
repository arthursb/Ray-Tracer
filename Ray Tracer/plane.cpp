#include "plane.h"

Plane::Plane(const Point& position, const Vector3& normal, const Color& color, const Material& material){
	this->position = position;
	this->normal = normal;
	this->color = color;
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
Color Plane::getFinalColor(const Point& contactPoint, const Point& observerPoint, const Light& light){
	Vector3 n = this->normal;
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

Vector3 Plane::getNormal(const Point& contactPoint){
	return normal;
}
