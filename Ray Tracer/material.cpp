#include "material.h"

Material::Material(){
	this->kAmbient = 1.0f;
	this->kDiffuse = 1.0f;
	this->kSpecular = 1.0f;
	this->shininess = 1.0f;
}

Material::Material(float kA, float kD, float Ks, float shininess){
	this->kAmbient = kA;
	this->kDiffuse = kD;
	this->kSpecular = Ks;
	this->shininess = shininess;
}

Material::~Material(){
}
