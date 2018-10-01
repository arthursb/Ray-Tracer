#include "ray.h"

Ray::Ray(){
	this->origin = Vector3(0.0f, 0.0f, 0.0f);
	this->direction = Vector3(0.0f, 0.0f, 1.0f); //forward
	this->tMax = T_MAX;
}

Ray::Ray(const Ray& r){
	this->origin = r.origin;
	this->direction = r.direction;
	this->tMax = r.tMax;
}

Ray::Ray(const Point& origin, const Vector3& direction, float tMax){
	this->origin = origin;
	this->direction = direction;
	this->tMax = tMax;
}

Ray::~Ray(){
}

Ray& Ray::operator =(const Ray& r){
	this->origin = r.origin;
	this->direction = r.direction;
	this->tMax = r.tMax;
	
	return *this;
}

Point Ray::calculate(float t) const{
	return origin + direction * t;
}
