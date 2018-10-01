#include "shape.h"

ShapeSet::ShapeSet(){
}

ShapeSet::~ShapeSet(){
}

void ShapeSet::addShape(Shape* shape){
	shapes.push_back(shape);
}

bool ShapeSet::intersect(Intersection& intersection){
	bool doesIntersect = false;
	
	for (std::vector<Shape*>::iterator iter = shapes.begin(); iter != shapes.end(); ++iter){
		Shape *curShape = *iter;
		if (curShape->intersect(intersection))
			doesIntersect = true;
	}
	
	return doesIntersect;
}
