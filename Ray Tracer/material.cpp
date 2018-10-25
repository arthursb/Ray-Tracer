#include "material.h"

Material::Material(){
	this->color = Color();
	this->kAmbient = 1.0f;
	this->kDiffuse = 1.0f;
	this->kSpecular = 1.0f;
	this->shininess = 1.0f;
	this->isMirror = false;
	this->isTransparent = false;
}

Material::Material(Color color, float kA, float kD, float kS, float shininess){
	this->color = color;
	this->kAmbient = kA;
	this->kDiffuse = kD;
	this->kSpecular = kS;
	this->shininess = shininess;
	this->isMirror = false;
	this->isTransparent = false;
}

Material::Material(Color color, float kA, float kD, float kS, float shininess, bool isMirror, bool isTransparent){
	this->color = color;
	this->kAmbient = kA;
	this->kDiffuse = kD;
	this->kSpecular = kS;
	this->shininess = shininess;
	this->isMirror = isMirror;
	this->isTransparent = isTransparent;
}

Material::Material(const Material& material){
	this->color = material.color;
	this->kAmbient = material.kAmbient;
	this->kDiffuse = material.kDiffuse;
	this->kSpecular = material.kSpecular;
	this->shininess = material.shininess;
}

Material::~Material(){
}
