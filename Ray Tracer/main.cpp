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

const GLint WIDTH = 400;
const GLint HEIGHT = 300;

const float mirrorK = 0.85f;

//debug: everything is either air or glass
const float snellK_air = 1.0f;
const float snellK_water = 1.333f;
const float snellK_glass = 1.5f;

const bool imageAsBG = false;
const char* imagePath = "/Users/arthursb/Desktop/Ray Tracer/Ray Tracer/Images/img_mars.jpg";
FIBITMAP *bitmap;
const Color bgColor = Color(0.4f, 0.4f, 0.4f);

//================================================================
//ray cast main
Color rayCast(Ray& ray, LightSet* lightSet, ShapeSet* shapeSet, int x, int y){
	//set final color as the pre-defined background color
	Color finalColor = bgColor;
	
	Intersection intersection(ray);
	bool intersected = shapeSet->intersect(intersection);

	//if there was no intersection...
	if(intersected == false){
		//if I want an image as the background...
		if(imageAsBG == true){
			//get the equivalent pixel color from the specified image and set it as the final color
			RGBQUAD color;
			FreeImage_GetPixelColor(bitmap, x, y, &color);
			finalColor = Color((float)color.rgbRed/255, (float)color.rgbGreen/255, (float)color.rgbBlue/255);
		}
		
		return finalColor;
	}
	//otherwise, if intersection hit...
	//get contact and observer
	Point contactPoint = intersection.position();
	Point observerPoint = ray.origin;
	
	//set final as ambient
	finalColor = intersection.pShape->getAmbientColor();
	
	//for each light in the scene...
	for (std::vector<Light*>::iterator iter = lightSet->lights.begin(); iter != lightSet->lights.end(); ++iter){
		//set current light
		Light *curLight = *iter;
		
		//set a new ray starting from intersection point to light source
		Vector3 contactToLight = (curLight->position - contactPoint).normalized();
		Ray shadowRay = Ray(contactPoint, contactToLight, T_MAX);
		Intersection shadowIntersection(shadowRay);
		
		if(shapeSet->intersect(shadowIntersection)){
			//check if ray is passing through a transparent object
			if(shadowIntersection.pShape->isTransparent()){
				Point shadowPoint = shadowIntersection.position();
				Vector3 normal = shadowIntersection.pShape->getNormal(shadowPoint);
				Vector3 refractionDirection = shadowRay.direction.getRefraction(normal, snellK_glass).normalized();
				Ray refractedRay = Ray(shadowPoint, refractionDirection, T_MAX);
				Intersection shadowRefractedIntersection(refractedRay);
				
				if(!shapeSet->intersect(shadowRefractedIntersection)){
					float factor = dot(shadowRay.direction, refractionDirection);
					
					Color diff = intersection.pShape->getDiffuseColor(contactPoint, observerPoint, *curLight);
					Color spec = intersection.pShape->getSpecularColor(contactPoint, observerPoint, *curLight);
					
					finalColor += factor * diff;
					finalColor += factor * spec;
				}
				
			}
		}
		//if there is no object between the contact point and the light source,
		//add diffuse and specular contributions
		else{
			finalColor += intersection.pShape->getDiffuseColor(contactPoint, observerPoint, *curLight);
			finalColor += intersection.pShape->getSpecularColor(contactPoint, observerPoint, *curLight);
		}
	}
	
	//if collided object is a mirror, we need to cast additional reflection rays
	if(intersection.pShape->isMirror() == true){
		//create a reflection ray from contact point
		Vector3 reflectedDirection = ray.direction.getReflection(intersection.normal()).normalized();
		Ray reflectedRay = Ray(contactPoint, reflectedDirection, T_MAX);
		
		//recursively add reflection rays contributions to the final color
		finalColor += mirrorK * rayCast(reflectedRay, lightSet, shapeSet, x, y);
	}
	
	//if collided object is a transparent, we need to cast additional refraction rays
	if(intersection.pShape->isTransparent() == true){
		//create a refraction ray from contact point

		Vector3 refractionDirection = ray.direction.getRefraction(intersection.normal(), snellK_glass).normalized();
		Ray refractedRay = Ray(contactPoint, refractionDirection, T_MAX);
		
		//recursively add refraction rays contributions to the final color
		finalColor += rayCast(refractedRay, lightSet, shapeSet, x, y);
	}
	
	//return final color clamped between 0 and 1
	finalColor.clamp();
	return finalColor;
}

//================================================================
//ray trace
void rayTrace(Image& image, Camera* camera, LightSet* lightSet, ShapeSet* shapeSet){
	for (int x = 0; x < WIDTH; x++){
		for (int y = 0; y < HEIGHT; y++){
			float screenX = (2.0f*x) / WIDTH - 1.0f;
			float screenY = (-2.0f*y) / HEIGHT + 1.0f;
			
			Ray ray = camera->makeRay(screenX, screenY);
			
			Color* curPixel = image.getColor(x, y);
			*curPixel = rayCast(ray, lightSet, shapeSet, x, y);
		}
	}
}

//================================================================
//3D scene
void drawScene(){
	ShapeSet sceneShapeSet;
	LightSet sceneLightSet;
	
	
	Material planeMaterial(Color(0.2, 0.2, 0.2), 1.0f, 1.0f, 1.0f, 1);
	Material bodyMaterial(Color(0.0f, 1.0f, 0.0f), 0.1f, 0.0f, 0.0f, 50, false, true);
	Material nerveMaterial(Color(0.76f, 0.0f, 0.0f), 0.8f, 1.2f, 1.2f, 20);
	Material teethMaterial(Color(0.98f, 0.84f, 0.67f), 0.8f, 1.2f, 1.2f, 20);
	Material triMaterial(Color(0.1f, 0.1f, 0.1f), 0.0f, 0.0f, 0.0f, 1, true, false);

	Plane floor(Point(0.0f, -2.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), planeMaterial);
	Sphere sphereBody(Point(0.0, 1.0f, 0.0f), 0.9f, bodyMaterial);
	Sphere sphereNerve1(Point(-0.2f, 0.9f, 0.0f), 0.2f, nerveMaterial);
	Sphere sphereNerve2(Point(0.2f, 0.9f, 0.0f), 0.2f, nerveMaterial);
	Sphere sphereNerve3(Point(0.0f, 1.25f, 0.0f), 0.2f, nerveMaterial);
	Triangle tooth1(Point(-1.0, -0.0f, 0.0f), Point(-0.75, 0.4f, 0.0f), Point(-0.4, 0.1f, 0.0f), teethMaterial);
	Triangle tooth1_1(Point(-1.0, -0.0f, 0.0f), Point(-0.5, 0.1f, 0.0f),Point(-0.85, -0.2f, 0.0f), teethMaterial);
	Triangle tooth1_2(Point(-0.85, -0.2f, 0.0f), Point(-0.75, -0.0f, 0.0f), Point(-0.55, -0.3f, 0.0f), teethMaterial);
	Triangle tooth2(Point(0.4, 0.1f, 0.0f), Point(0.75, 0.4f, 0.0f), Point(1.0, -0.0f, 0.0f), teethMaterial);
	Triangle tooth2_1(Point(1.0, -0.0f, 0.0f), Point(0.85, -0.2f, 0.0f), Point(0.5, 0.1f, 0.0f), teethMaterial);
	Triangle tooth2_2(Point(0.85, -0.2f, 0.0f), Point(0.55, -0.3f, 0.0f), Point(0.75, -0.0f, 0.0f), teethMaterial);
	Triangle tooth3(Point(-0.35, 0.12f, 0.0f), Point(-0.18, 0.05f, 0.0f), Point(-0.35, -0.2f, 0.0f), teethMaterial);
	Triangle tooth4(Point(0.35, 0.12f, 0.0f), Point(0.35, -0.2f, 0.0f), Point(0.18, 0.05f, 0.0f), teethMaterial);
	
	Triangle triangleMirror(Point(4.0f, -1.0f, 6.0f), Point(0.0f, 6.0f, 4.0f), Point(-4.0f, -1.0f, 6.0f), triMaterial);
	Sphere sphere1(Point(1.0f, 0.0f, 2.0f), 0.2f, nerveMaterial);
	Sphere sphere2(Point(-1.0f, 0.0f, 2.0f), 0.2f, nerveMaterial);
	Sphere sphere3(Point(0.0f, 0.0f, 1.0f), 0.2f, nerveMaterial);
	Sphere sphere4(Point(0.0f, 1.0f, 1.0f), 0.2f, nerveMaterial);
	Sphere sphere5(Point(0.0f, -1.0f, 2.0f), 0.2f, nerveMaterial);
	
	
	Light light1(Point(-500.0f, 100.0f, -300.0f), Color(0.5f, 0.5f, 0.5f));

	sceneShapeSet.addShape(&floor);
	
	//DEMO MIRROR
	/*
	sceneShapeSet.addShape(&sphere1);
	sceneShapeSet.addShape(&sphere2);
	sceneShapeSet.addShape(&sphere3);
	sceneShapeSet.addShape(&sphere4);
	sceneShapeSet.addShape(&sphere5);
	sceneShapeSet.addShape(&triangleMirror);
	*/
	
	
	//METROID
	
	sceneShapeSet.addShape(&sphereBody);
	sceneShapeSet.addShape(&sphereNerve1);
	sceneShapeSet.addShape(&sphereNerve2);
	sceneShapeSet.addShape(&sphereNerve3);
	sceneShapeSet.addShape(&tooth1);
	sceneShapeSet.addShape(&tooth1_1);
	sceneShapeSet.addShape(&tooth1_2);
	sceneShapeSet.addShape(&tooth2);
	sceneShapeSet.addShape(&tooth2_1);
	sceneShapeSet.addShape(&tooth2_2);
	sceneShapeSet.addShape(&tooth3);
	sceneShapeSet.addShape(&tooth4);
	
	
	
	sceneLightSet.addLight(&light1);
	
	Image image(WIDTH, HEIGHT);

	Camera camera(Point(0.0f, 0.0f, -5.0f),
				  Vector3(0.0f, 0.0f, 0.0f),
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

//================================================================
//main
int main( ){
	//INITIALIZE WINDOW
	GLFWwindow *window;

	if (!glfwInit()){
		return -1;
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, "ARTHUR RAYTRACER", NULL, NULL);
	
	if (!window){
		glfwTerminate();
		return -1;
	}

	//SET GL WINDOW STUFF
	glfwMakeContextCurrent(window);
	glViewport(0, 0, WIDTH*2, HEIGHT*2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//GET BG IMAGE STUFF
	FreeImage_Initialise();
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(imagePath);
	bitmap = FreeImage_Load(fif, imagePath);
	
	//DRAW
	while (!glfwWindowShouldClose(window)){
		glClearColor(0.7f, 0.7f, 0.7f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		
		drawScene();
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	
	//FINALIZE
	FreeImage_DeInitialise();
	glfwTerminate();
	return 0;
}
