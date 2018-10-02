#include <cmath>

#include "vector3.h"

Vector3::Vector3(){
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3::Vector3(const Vector3& v){
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Vector3::Vector3(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(float f){
	this->x = f;
	this->y = f;
	this->z = f;
}

Vector3::~Vector3(){
}

inline float Vector3::lengthSquared(){
	return  x * x + y * y + z * z;
}

inline float Vector3::length(){
	return std::sqrt(lengthSquared());
}

Vector3 Vector3::normalized(){
	return (*this) / (*this).length();
}

float dot(Vector3 v1, Vector3 v2){
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 cross(Vector3 v1, Vector3 v2){
	return Vector3(v1.y * v2.z - v1.z * v2.y,
				   v1.z * v2.x - v1.x * v2.z,
				   v1.x * v2.y - v1.y * v2.x);
}

//r = d - 2 (d dot n) n
Vector3 Vector3::getReflection(const Vector3& normal){
	return *this - 2 * dot(*this, normal) * normal;
}

Vector3& Vector3::operator =(const Vector3& v){
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;

	return *this;
}

Vector3& Vector3::operator +=(const Vector3& v){
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	
	return *this;
}

Vector3& Vector3::operator -=(const Vector3& v){
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	
	return *this;
}

Vector3& Vector3::operator *=(float f){
	this->x *= f;
	this->y *= f;
	this->z *= f;
	
	return *this;
}

Vector3& Vector3::operator /=(float f){
	this->x /= f;
	this->y /= f;
	this->z /= f;
	
	return *this;
}

Vector3 Vector3::operator -() const{
	return Vector3(-x, -y, -z);
}
