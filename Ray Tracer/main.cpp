#include <iostream>
#include "glew.h"
#include "glfw3.h"

#include "camera.h"
#include "image.h"
#include "plane.h"
#include "sphere.h"
#include "light.h"

const GLint WIDTH = 400;
const GLint HEIGHT = 300;

void rayTrace(Image& image, Camera* camera, Light& light, ShapeSet* scene){
	for (int x = 0; x < WIDTH; x++){
		for (int y = 0; y < HEIGHT; y++){
			float screenX = (2.0f*x) / WIDTH - 1.0f;
			float screenY = (-2.0f*y) / HEIGHT + 1.0f;
			
			Ray ray = camera->makeRay(screenX, screenY);
			
			Color* curPixel = image.getColor(x, y);
			
			Intersection intersection(ray);
			
			if (scene->intersect(intersection)){
				Point contactPoint = intersection.position();
				Point observerPoint = camera->origin;
				
				*curPixel = intersection.pShape->getFinalColor(contactPoint, observerPoint, light);
			}
			else{
				*curPixel = Color(0.3f, 0.3f, 0.3f);
			}
		}
	}
}

void drawScene(){
	ShapeSet scene;
	
	Light ambientLight(Point(-7.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f));
	
	Material planeMaterial(0.6f, 0.2f, 0.2f, 1);
	Material sphereMaterial(0.5f, 0.6f, 0.6f, 10);
	
	Plane floor(Point(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Color(0.5f, 1.0f, 0.5f), planeMaterial);
	Sphere sphere(Point(0.0f, 1.0f, 0.0f), 1.0f, Color(0.5f, 0.5f, 1.0f), sphereMaterial);
	
	scene.addShape(&floor);
	scene.addShape(&sphere);
	
	Image image(WIDTH, HEIGHT);

	Camera camera(Point(-5.0f, 0.5f, 0.0f),
				  Vector3(0.0f, 1.0f, 0.0f),
				  Vector3(0.0f, -1.0f, 0.0f),
				  25.0f * PI / 180.0f,
				  (float)WIDTH / (float)HEIGHT);
 
	rayTrace(image, &camera, ambientLight, &scene);

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
	GLFWwindow *window;

	if (!glfwInit( )){
		return -1;
	}
	
	window = glfwCreateWindow( WIDTH, HEIGHT, "TEST", NULL, NULL );
	
	if (!window){
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent( window );
	
	glViewport(0, 0, WIDTH*2, HEIGHT*2);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, WIDTH, 0, HEIGHT, -1, 1);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	while (!glfwWindowShouldClose(window)){
		glClearColor(0.7f, 0.7f, 0.7f, 1);
		glClear( GL_COLOR_BUFFER_BIT );
		
		drawScene();
		
		glfwSwapBuffers( window );

		glfwPollEvents( );
	}
	
	glfwTerminate( );
	return 0;
}