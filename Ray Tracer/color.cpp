#include "color.h"

#include <cmath>

Color::Color(){
	this->r = 0.0f;
	this->g = 0.0f;
	this->b = 0.0f;
}

Color::Color(float r, float g, float b){
	this->r = r;
	this->g = g;
	this->b = b;
}

Color::~Color(){
}

void Color::clamp(){
	this->r = fmax(0, fmin(1, r));
	this->g = fmax(0, fmin(1, g));
	this->b = fmax(0, fmin(1, b));
}

float Color::getBrightness(){
	return r + b + g;
}

Color& Color::operator =(const Color& c){
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
	
	return *this;
}

Color& Color::operator +=(const Color& c){
	this->r += c.r;
	this->g += c.g;
	this->b += c.b;
	
	return *this;
}

Color& Color::operator *=(const Color& c){
	this->r *= c.r;
	this->g *= c.g;
	this->b *= c.b;
	
	return *this;
}

Color& Color::operator *=(float f){
	this->r *= f;
	this->g *= f;
	this->b *= f;
	
	return *this;
}
