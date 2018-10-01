#include "image.h"

Image::Image(int width, int height){
	this->width = width;
	this->height = height;
	this->data = new Color[width * height];
}

Image::~Image(){
	delete[] data;
}

Color* Image::getColor(int x, int y){
	return data + (x + y * width);
}
