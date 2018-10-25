#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

struct Material{
	Color color;
	float kAmbient;
	float kDiffuse;
	float kSpecular;
	float shininess;
	
	bool isMirror;
	bool isTransparent;
	
	Material ();
	Material (Color color, float kA, float kD, float kS, float shininess);
	Material (Color color, float kA, float kD, float kS, float shininess, bool isMirror, bool isTransparent);
	Material (const Material& material);
	
	virtual ~Material();
};


#endif //MATERIAL_H
