#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "color.h"

class Image
{
protected:
	Color* data;

public:
	int width;
	int height;
	
	Image(int width, int height);

	virtual ~Image();

	Color* getColor(int x, int y);
};

#endif
