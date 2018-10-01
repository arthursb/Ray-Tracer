#include "intersection.h"

Intersection::Intersection(){
	this->ray = ray;
	this->t = T_MAX;
	this->pShape = nullptr;
}

Intersection::Intersection(const Intersection& i){
	this->ray = i.ray;
	this->t = i.t;
	this->pShape = i.pShape;
}

Intersection::Intersection(const Ray& ray){
	this->ray = ray;
	this->t = ray.tMax;
	this->pShape = nullptr;
}

Intersection::~Intersection(){
}

Intersection& Intersection::operator =(const Intersection& i){
	this->ray = i.ray;
	this->t = i.t;
	this->pShape = i.pShape;
	
	return *this;
}

bool Intersection::intersected() const{
	return (pShape != nullptr);
}

Point Intersection::position() const{
	return ray.calculate(t);
}
