#ifndef MATERIAL_H
#define MATERIAL_H

struct Material{
	float kAmbient;
	float kDiffuse;
	float kSpecular;
	float shininess;
	
	Material ();
	Material (float kA, float kD, float Ks, float shininess);
	
	virtual ~Material();
};


#endif //MATERIAL_H
