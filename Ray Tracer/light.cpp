#include "light.h"

//todas as luzes são consideradas direction light

Light::Light () {
	this->position = Vector3(0.0f, 0.0f, 0.0f);
	this->color = Color(1.0f,1.0f,1.0f);
}

Light::Light (const Point& position, const Color& color) {
	this->position = position;
	this->color = color;
}

Light::~Light () {
}

LightSet::LightSet(){
}

LightSet::~LightSet(){
}

void LightSet::addLight(Light* light){
	lights.push_back(light);
}
