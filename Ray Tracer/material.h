#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

struct Material{
	Color color;
	float kAmbient;
	float kDiffuse;
	float kSpecular;
	float shininess;
	
	Material ();
	Material (Color color, float kA, float kD, float kS, float shininess);
	Material (const Material& material);
	
	virtual ~Material();
};


#endif //MATERIAL_H
