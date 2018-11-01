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

//snellK = refraction index of the object a ray is getting inside or leaving
// https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
Vector3 Vector3::getRefraction(const Vector3& normal, float snellK){
	Vector3 correctNormal = Vector3(normal);
	
	//η=η1/η2
	float snellFinal;
	
	//c1=cos(θ1)=N⋅I
	float thisDotN = dot(*this, normal);

	if(thisDotN < 0){
		thisDotN = -thisDotN;
		snellFinal = 1/snellK;
	}
	else{
		snellFinal = snellK;
		correctNormal = -normal;
	}

	//c2= √(1−(n1/n2)2 * (1−cos2(θ1)))
	float calc = 1 - (snellFinal * snellFinal) * (1 - thisDotN * thisDotN);
	
	if(calc < 0)
		return Vector3(); //zero
	
	//T=ηI+(ηc1−c2)N
	Vector3 refraction = (snellFinal * *this) + (snellFinal * thisDotN - sqrt(calc)) * correctNormal;
	
	return  refraction;
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
