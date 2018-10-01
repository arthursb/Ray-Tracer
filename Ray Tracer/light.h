#ifndef LIGHT_H
#define LIGHT_H

#include "vector3.h"
#include "color.h"

class Light{
public:
	Point position;
	Color color;
	
	Light ();
	Light (const Point& position, const Color& color);
	
	virtual ~Light();
};

#endif //LIGHT_H
