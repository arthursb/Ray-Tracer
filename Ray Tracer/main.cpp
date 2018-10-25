#include <iostream>
#include "glew.h"
#include "glfw3.h"
#include "FreeImage.h"

#include "camera.h"
#include "image.h"
#include "plane.h"
#include "triangle.h"
#include "sphere.h"
#include "light.h"

#ifndef MAX_ITERATIONS
#define MAX_ITERATIONS 1
#endif

const GLint WIDTH = 400;
const GLint HEIGHT = 300;

const bool imageAsBG = false;
const char* imagePath = "/Users/arthursb/Desktop/Ray Tracer/Ray Tracer/Images/img_mars.jpg";
FIBITMAP *bitmap;
const Color bgColor = Color(0.4f, 0.4f, 0.4f);

/*
 
 if(imageAsBG == true){
 RGBQUAD color;
 FreeImage_GetPixelColor(bitmap, x, y, &color);
 *curPixel = Color((float)color.rgbRed/255, (float)color.rgbGreen/255, (float)color.rgbBlue/255);
 }
 else
 *curPixel = bgColor;
 
 */

Color rayCast_BG(Ray& ray, LightSet* lightSet, ShapeSet* shapeSet, int iterationCount){
	Color finalColor;
	
	Intersection intersection(ray);
	
	if (shapeSet->intersect(intersection)){
		Point contactPoint = intersection.position();
		Point observerPoint = ray.origin;
		
		Color ambient = intersection.pShape->getAmbientColor();
		Color diffuse = Color(0);
		Color specular = Color(0);
		
		for (std::vector<Light*>::iterator  iter = lightSet->lights.begin();
			 iter != lightSet->lights.end();
			 ++iter){
			
			Light *curLight = *iter;
			Vector3 contactToLight = (curLight->position - contactPoint).normalized();
			Ray shadowRay = Ray(contactPoint, contactToLight, T_MAX);
			
			Intersection shadowIntersection(shadowRay);
			
			if(!shapeSet->intersect(shadowIntersection)){
				diffuse += intersection.pShape->getDiffuseColor(contactPoint, observerPoint, *curLight);
				specular += intersection.pShape->getDiffuseColor(contactPoint, observerPoint, *curLight);
			}
		}
		
		finalColor = ambient + diffuse + specular;
	}
	else{
		finalColor = bgColor;
	}
	
	return finalColor;
}


void rayTrace(Image& image, Camera* camera, LightSet* lightSet, ShapeSet* shapeSet){
	for (int x = 0; x < WIDTH; x++){
		for (int y = 0; y < HEIGHT; y++){
			float screenX = (2.0f*x) / WIDTH - 1.0f;
			float screenY = (-2.0f*y) / HEIGHT + 1.0f;
			
			Ray ray = camera->makeRay(screenX, screenY);
			
			Color* curPixel = image.getColor(x, y);
			
			*curPixel = rayCast_BG(ray, lightSet, shapeSet, 0);
			
		}
	}

	
}

//SET DRAW SCENE
void drawScene(){
	ShapeSet sceneShapeSet;
	LightSet sceneLightSet;
	
	Material planeMaterial(Color(0.23f, 0.37f, 0.70f), 0.6f, 1.0f, 1.0f, 1);
	Material bodyMaterial(Color(1.0f, 1.0f, 0.98f), 0.8f, 0.6f, 0.6f, 20);
	Material eyeMaterial(Color(1.0f, 1.0f, 1.0f), 0, 0, 0, 1);
	Material crystalMaterial(Color(0.23f, 0.37f, 0.70f), 1.0f, 0.2f, 0.2f, 1);

	Plane floor(Point(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), planeMaterial);
	Sphere sphere1(Point(0.0f, 1.0f, 0.0f), 1.0f, bodyMaterial);
	Sphere sphere2(Point(0.0f, 2.0f, 0.0f), 0.75f, bodyMaterial);
	Sphere sphere3(Point(0.0f, 3.0f, 0.0f), 0.5f, bodyMaterial);
	Sphere crystal(Point(-0.75f, 2.0f, 0.0f), 0.125f, crystalMaterial);
	Sphere eye1(Point(-0.5f, 3.0f, -0.2f), 0.07f, eyeMaterial);
	Sphere eye2(Point(-0.5f, 3.0f, 0.2f), 0.07f, eyeMaterial);
	
	Light light1(Point(-500.0f, 100.0f, -300.0f), Color(0.5f, 0.5f, 0.5f));
	Light light2(Point(0.0f, 100.0f, -100.0f), Color(0.0f, 1.0f, 0.0f));
	Light light3(Point(100.0f, 100.0f, 100.0f), Color(0.0f, 0.0f, 1.0f));

	sceneShapeSet.addShape(&floor);
	sceneShapeSet.addShape(&sphere1);
	sceneShapeSet.addShape(&sphere2);
	sceneShapeSet.addShape(&sphere3);
	sceneShapeSet.addShape(&crystal);
	sceneShapeSet.addShape(&eye1);
	sceneShapeSet.addShape(&eye2);
	
	sceneLightSet.addLight(&light1);
	//sceneLightSet.addLight(&light2);
	//sceneLightSet.addLight(&light3);
	
	Image image(WIDTH, HEIGHT);

	Camera camera(Point(-7.0f, 1.0f, 0.0f),
				  Vector3(0.0f, 2.0f, -2.0f),
				  Vector3(0.0f, -1.0f, 0.0f),
				  25.0f * PI / 180.0f,
				  (float)WIDTH / (float)HEIGHT);
 
	rayTrace(image, &camera, &sceneLightSet, &sceneShapeSet);

	glPointSize(2);
	glBegin(GL_POINTS);
	for(float x = 0; x < WIDTH; x++){
		for(float y = 0; y < HEIGHT; y++){
			Color* refColor = image.getColor(x, y);
			glColor3d(refColor->r, refColor->g, refColor->b);
			glVertex3d(x, y, 0);
		}
	}
	glEnd();
}

int main( ){
	//INITIALIZE WINDOW
	GLFWwindow *window;

	if (!glfwInit( ))
		return -1;
	window = glfwCreateWindow( WIDTH, HEIGHT, "TEST", NULL, NULL );
	
	if (!window){
		glfwTerminate();
		return -1;
	}

	//SET GL WINDOW STUFF
	glfwMakeContextCurrent( window );
	glViewport(0, 0, WIDTH*2, HEIGHT*2);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, WIDTH, 0, HEIGHT, -1, 1);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	//GET BG IMAGE STUFF
	FreeImage_Initialise ();
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(imagePath);
	bitmap = FreeImage_Load(fif, imagePath);
	
	//DRAW
	while (!glfwWindowShouldClose(window)){
		glClearColor(0.7f, 0.7f, 0.7f, 1);
		glClear( GL_COLOR_BUFFER_BIT );
		
		drawScene();
		
		glfwSwapBuffers( window );

		glfwPollEvents( );
	}
	
	//FINALIZE
	FreeImage_DeInitialise ();
	glfwTerminate( );
	return 0;
}
