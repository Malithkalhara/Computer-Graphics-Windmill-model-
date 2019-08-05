#include <iostream>
#include <stdio.h>
#include "stdafx.h"
#include <GL/freeglut.h>  
#include <Windows.h>
#include <math.h>
#include <stb_image.h>

using namespace std;


// vertices for the cube
GLfloat x = 2.0f;
GLfloat y = 2.0f;
GLfloat z = 2.0f;

// variables to move outermost Object Frame (to move all the rendered environment)
GLfloat moveX = 0.0f;
GLfloat moveY = 0.0f;
GLfloat moveZ = 0.0f;

// variables to rotate outermost Object Frame (to move all the rendered environment)
GLfloat rotX = 0.0f;
GLfloat rotY = 0.0f;
GLfloat rotZ = 0.0f;

GLint moveCar = 1;

// For animating the rotation of the objects
GLfloat animateRotation = 0.0f;

//variables to move the camera
GLfloat camY = 0.0f;
GLfloat camX = 0.0f;
GLfloat camZ = 0.0f;

GLfloat rotFan = 0.0f;
GLfloat transVeh = 0.0f;

unsigned int textures[5];

// A quadratic object pointer used to draw the sides of the cylinder
GLUquadricObj *qobj;
GLUquadric* sphere;

//An array to store the normal vector data for the faces
GLfloat vNormal[3] = {};


//Function to initialize the lighting properties. you can add upto 8 lights in openGL (0-7)
void initLighting(){

	//Decalring the Ambient, Diffuse components of the LIght_0 and the position in the eye coordinate system
	GLfloat L0_Ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat L0_Diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat L0_postion[] = { 5, 5, 0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, L0_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, L0_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, L0_postion);

	GLfloat L1_Ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat L1_Diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat L1_Specular[] = { 0.0, 1.0, 0.0, 1.0 };   //Declaration of the specular component of the light_1
	GLfloat L1_postion[] = { -5, 5, 0, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, L1_Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, L1_Specular);
	glLightfv(GL_LIGHT1, GL_POSITION, L1_postion);

	//Declaration of the ligt reflecting properties for the materials
	GLfloat specularReflectance[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflectance);
	glMateriali(GL_FRONT, GL_SHININESS, 50);


	GLfloat L2_Ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat L2_Diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat L2_Specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat L2_postion[] = { 0, 5, 5, 1.0 };
	GLfloat L2_SpotDirection[] = { 0.0, -1.0, -1.0 };

	glLightfv(GL_LIGHT2, GL_AMBIENT, L2_Ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, L2_Diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, L2_Specular);
	glLightfv(GL_LIGHT2, GL_POSITION, L2_postion);

	//Creating a spotlight from light_2 by declaring the direction vetor and area that the spotligt can shine(fov of the spotlight)
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, L2_SpotDirection);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);


}


void initTextures(){
	glGenTextures(5, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("grass3.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		//cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	unsigned char *data1 = stbi_load("grass3.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		//cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data1);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	unsigned char *data2 = stbi_load("sky1.jpg", &width, &height, &nrChannels, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		//cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data2);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *data3 = stbi_load("wall3.jpg", &width, &height, &nrChannels, 0);
	if (data3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		//cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data3);

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *data4 = stbi_load("roof1.jpg", &width, &height, &nrChannels, 0);
	if (data4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		//cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data4);
}


void init(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GLfloat globalAmbient[] = { 0.4, 0.4, 0.4, 1.0 };
	glEnable(GL_DEPTH_TEST);

	//Enable the adding of lights
	glEnable(GL_LIGHTING);


	glShadeModel(GL_SMOOTH);

	// Changing the global Ambient illumination without any lights present
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	initLighting();

	// Enabling the color tracking of each faces of the materials. this enables the color visibility of the materials
	glEnable(GL_COLOR_MATERIAL);

	//Turn on lighting
	glEnable(GL_LIGHT0);
	// glEnable(GL_LIGHT1);
	// glEnable(GL_LIGHT2);

	// enable the normalization of the normal vectors (converting the vector values to the range 0-1)
	glEnable(GL_NORMALIZE);

	qobj = gluNewQuadric();
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);

	initTextures();

}


//Calculate the normals for two vectors va, vb ( normal for a plane/face )
GLfloat* calNormal(GLfloat* va, GLfloat* vb){
	vNormal[0] = va[1] * vb[2] - va[2] * vb[1];
	vNormal[1] = va[0] * vb[2] - va[2] * vb[0];
	vNormal[2] = va[0] * vb[1] - va[1] * vb[0];

	return vNormal;
}

// Find the Normal from three points in 3d space.
// BE AWARE THAT THE POINTS SHOULD BE DECLARED IN ANTI-CLOCKWISE ORDER FOR THE TWO SIDES(FORMING THE TWO VECTORS)
// HAVING ONE VERTEX COMMON TO BOTH SIDES (vertices abc form two sides as 'ab' and 'ac')
// Otherwise you'll get the wrong/ reverse vector
GLfloat* findNormal(GLfloat* a, GLfloat* b, GLfloat* c){

	GLfloat va[] = { b[0] - a[0], b[1] - a[1], b[2] - a[2] };
	GLfloat vb[] = { c[0] - a[0], c[1] - a[1], c[2] - a[2] };

	return calNormal(va, vb);
}


void drawCube(){
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 2, 0);
	glVertex3f(2, 0, 0);
	glVertex3f(2, 2, 0);

	glVertex3f(2, 0, 2);
	glVertex3f(2, 2, 2);

	glVertex3f(0, 0, 2);
	glVertex3f(0, 2, 2);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 2, 0);
	//(1, 1, 0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.6, 0.5);
	glVertex3f(0, 2, 0);
	glVertex3f(2, 2, 0);
	glVertex3f(2, 2, 2);
	glVertex3f(0, 2, 2);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2, 0.5, 0.5);
	glVertex3f(0, 0, 0);
	glVertex3f(2, 0, 0);
	glVertex3f(2, 0, 2);
	glVertex3f(0, 0, 2);
	glEnd();



}

GLfloat  M_PI = 3.14;

void drawCircle(GLfloat radius){

	
	//fill circle
	glBegin(GL_TRIANGLE_FAN);

	glVertex3f(0.0, 0.0, 0.0);
	for (GLfloat d = 0; d < 2 * M_PI; d = d + 0.001) {
		glVertex3f(radius*cos(d), radius*sin(d), 0);
		//glVertex3f(radius*cos(d+0.5), radius*sin(d+0.5), 0);
	}
	glEnd();
}


void drawFan(){

	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(0,0,0);
	glVertex3f(-1, 8, 0);
	glVertex3f(1, 8, 0);
	glEnd();

}

void drawHome(){

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_QUAD_STRIP);

	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0, 10);
	glVertex3f(0, 2, 0);
	glTexCoord2f(2.5, 0);
	glVertex3f(5, 0, 0);
	glTexCoord2f(2.5, 10);
	glVertex3f(5, 2, 0);

	/*
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 2,0);
	glVertex3f(5,0, 0);
	glVertex3f(5, 2, 0);
	*/
	glTexCoord2f(5, 0);
	glVertex3f(5,0, 2);
	glTexCoord2f(5, 10);
	glVertex3f(5, 2, 2);

	glTexCoord2f(7.5, 0);
	glVertex3f(0, 0, 2);
	glTexCoord2f(7.5, 10);
	glVertex3f(0, 2, 2);

	glTexCoord2f(10, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(10, 10);
	glVertex3f(0, 2, 0);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_TRIANGLES);

	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(5, 2, 2);
	glVertex3f(5, 2, 0);
	glVertex3f(5, 2.5, 1);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_TRIANGLES);

	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, 0);
	glVertex3f(0, 2.5, 1);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);

	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 2);
	glVertex3f(8, 0, 2);
	glVertex3f(8, 0, 0);

	glEnd();
	glPopMatrix();


	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_QUADS);

	glColor3f(0.3, 0.3, 0.3);
	glTexCoord2f(1,1);
	glVertex3f(5, 2, 0.25);
	glTexCoord2f(0, 1);
	glVertex3f(5, 2, 1.75);
	glTexCoord2f(0, 0);
	glVertex3f(7, 2, 1.75);
	glTexCoord2f(1, 0);
	glVertex3f(7, 2, 0.25);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	//Rotatef(90, 1, 0, 0);
	glTranslatef(6.5, 0, 0.4);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 0.05, 0.05, 2, 6, 6);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	//Rotatef(90, 1, 0, 0);
	glTranslatef(6.5, 0, 1.6);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 0.05, 0.05, 2, 10, 10);
	glPopMatrix();

	//roof
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_QUADS);

	glTexCoord2f(0,1);
	glVertex3f(-0.5, 2.5, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 2, 2);
	glTexCoord2f(1, 0);
	glVertex3f(5.5, 2, 2);
	glTexCoord2f(1, 1);
	glVertex3f(5.5, 2.5, 1);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 2.5, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 2, 0);
	glTexCoord2f(1, 1);
	glVertex3f(5.5, 2, 0);
	glTexCoord2f(1, 0);
	glVertex3f(5.5, 2.5, 1);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	/*
	glPushMatrix();
	glBegin(GL_QUAD_STRIP);

	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-0.5, 2.5, 1);
	glVertex3f(-0.5, 2, 0);
	glVertex3f(5.5, 2, 0);
	glVertex3f(5.5, 2.5, 1);

	glEnd();
	glPopMatrix();
	*/

}


void drawTyre(){
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glutSolidTorus(0.2, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 0, 0.01);
	drawCircle(0.3);
	glPopMatrix();

}

void drawLight(){

	glPushMatrix();
	glColor3f(0, 0, 0);
	glutSolidTorus(0.1,0.2,15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslatef(0, 0, 0.01);
	drawCircle(0.1);
	glPopMatrix();
}

void drawShell(){

	for (GLfloat t = 0.3; t < 1; t = t + 0.3){
		glPushMatrix();
		glColor3f(0.4, 0.5, 0.4);
		glTranslatef(0, t,0);
		gluCylinder(qobj, 0.1, 0.1, 2, 10, 10);
		glPopMatrix();
	}

}

//Part of Fence
void drawFencePart(){
	
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 0.2, 0.2, 3, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(0, 3, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.2, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(3, 0, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 0.2, 0.2, 3, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(3, 3, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.2, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(0, 2.5, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(qobj, 0.1, 0.1, 3, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(0, 1.5, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(qobj, 0.1, 0.1, 3, 10, 10);
	glPopMatrix();
}

void drawFence(){
	
	glPushMatrix();
	drawFencePart();
	for (GLfloat t = 0; t < 20; t++){
		glTranslatef(3, 0, 0);
		drawFencePart();

	}
	glPopMatrix();
}

void drawFenceSmall(){

	glPushMatrix();
	drawFencePart();
	for (GLfloat t = 0; t < 12; t++){
		glTranslatef(3, 0, 0);
		drawFencePart();

	}
	glPopMatrix();
}

void drawVehicle(){

	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 4);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 2, 4);
	glVertex3f(0, 2, 0);

	glVertex3f(2, 2, 4);
	glVertex3f(2, 2, 0);

	glVertex3f(3, 1, 4);
	glVertex3f(3, 1, 0);

	glVertex3f(5, 1, 4);
	glVertex3f(5, 1, 0);

	glVertex3f(5, 0, 4);
	glVertex3f(5, 0, 0);

	glVertex3f(3, 0, 4);
	glVertex3f(3, 0, 0);

	glVertex3f(0,0, 4);
	glVertex3f(0, 0, 0);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(3, 1, 4);
	glVertex3f(5, 1, 4);
	glVertex3f(5, 0, 4);
	glVertex3f(3, 0, 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(3, 1, 0);
	glVertex3f(5, 1, 0);
	glVertex3f(5, 0, 0);
	glVertex3f(3, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	glColor3f(0, 0, 1);
	glVertex3f(-6,1, 4);
	glVertex3f(0, 1, 4);
	glVertex3f(-6,0, 4);
	glVertex3f(0, 0, 4);

	glVertex3f(-6, 0, 0);
	glVertex3f(0, 0, 0);

	glVertex3f(-6, 1, 0);
	glVertex3f(0, 1, 0);

	glEnd();
	glPopMatrix();


	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(0.5, 1.5, 4);
	glVertex3f(0, 2, 4);
	glVertex3f(2, 1.5, 4);
	glVertex3f(2, 2, 4);

	glVertex3f(2.5, 1, 4);
	glVertex3f(3, 1, 4);

	glVertex3f(2.5, 1, 4);
	glVertex3f(3, 0, 4);

	glVertex3f(0.5, 1, 4);
	glVertex3f(0, 0, 4);

	glVertex3f(0.5, 1.5, 4);
	glVertex3f(0, 2, 4);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(0.5, 1.5, 0);
	glVertex3f(0, 2, 0);
	glVertex3f(2, 1.5, 0);
	glVertex3f(2, 2, 0);

	glVertex3f(2.5, 1, 0);
	glVertex3f(3, 1, 0);

	glVertex3f(2.5, 1, 0);
	glVertex3f(3, 0, 0);

	glVertex3f(0.5, 1, 0);
	glVertex3f(0, 0, 0);

	glVertex3f(0.5, 1.5, 0);
	glVertex3f(0, 2, 0);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, 0, 4);
	drawTyre();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5, 0, 4);
	drawTyre();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, 0, 0);
	glRotatef(-180, 1, 0, 0);
	drawTyre();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5, 0, 0);
	glRotatef(-180, 1, 0, 0);
	drawTyre();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0.5, 3.5);
	glRotatef(90,0, 1, 0);
	drawLight();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0.5, 0.5);
	glRotatef(90, 0, 1, 0);
	drawLight();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0, 1);
	drawShell();
	glPopMatrix();

	
}

void fanWings(){

	glPushMatrix();
	glTranslatef(0, 0, -2);
	drawFan();

	for (GLfloat a = 0; a < 360; a = a + 60){
		glPushMatrix();
		glRotatef(a, 0, 0, 1);
		drawFan();
		glPopMatrix();
	}

	glPopMatrix();

}


//Windmill
void drawWindmill(){

	glPushMatrix();
	glColor3f(0.6, 0.6, 0.6);
	glRotatef(90, 1, 0, 0);
	gluCylinder(qobj, 1, 2, 15, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.4, 0.7, 0.6);
	glRotatef(90, 1, 0, 0);
	drawCircle(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	//glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -2);
	gluCylinder(qobj, 0.25, 0.5, 3, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(0, 0, -2);
	drawCircle(0.25);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.4, 0.5, 0.6);
	glTranslatef(0, 0, 1);
	drawCircle(0.5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(rotFan, 0, 0, 1);
	fanWings();	
	glPopMatrix();
}

/*
void drawRoad(){
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(6,-1,-1);
	glVertex3f(0, -1, -1);
	glVertex3f(0, -1, 6+transVeh);
	glVertex3f(6, -1, 6+transVeh);
	glEnd();
	glPopMatrix();
}
*/
void drawModel(){

	glPushMatrix();
	glTranslatef(-4, -0.9, 0);
	glRotatef(-20, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	drawHome();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(5, -0.3, -3);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.4, 0.4, 0.4);
	glPushMatrix();
	glTranslatef(transVeh, -1, -1);
	drawVehicle();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 5, -5);
	glRotatef(-150, 0, 1, 0);
	glScalef(0.4, 0.4, 0.4);
	drawWindmill();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6, -1, 3.5);
	glPushMatrix();
	glScalef(0.2, 0.2, 0.2);
	glRotatef(90, 0, 1, 0);
	drawFence();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6, -1, 3.5);
	glRotatef(-90, 0, 1, 0);
	glPushMatrix();
	glScalef(0.2, 0.2, 0.2);
	glRotatef(90, 0, 1, 0);
	drawFenceSmall();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.6, -1, 3.5);
	//glRotatef(-90, 0, 1, 0);
	glPushMatrix();
	glScalef(0.2, 0.2, 0.2);
	glRotatef(90, 0, 1, 0);
	drawFence();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6, -1, -9.1);
	glRotatef(-90, 0, 1, 0);
	glPushMatrix();
	glScalef(0.2, 0.2, 0.2);
	glRotatef(90, 0, 1, 0);
	drawFence();
	glPopMatrix();
	glPopMatrix();

}

void clipPlane(){
	glColor3f(0.8, 0.8, 0.8);
	GLdouble plane3[] = { 0, 1, 0, 0 };
	glClipPlane(GL_CLIP_PLANE0, plane3);
	glEnable(GL_CLIP_PLANE0);
	glEnable(GL_TEXTURE_2D);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluSphere(sphere, 15, 50, 50);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CLIP_PLANE0);

	

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(0.0, -0.01, 0.0);
	for (GLfloat i = 0; i <= 360; i=i + 0.1){
		glTexCoord2f(15 * cos(i) + 15, 15 * sin(i) + 15);
		glVertex3f(15 * sin(i), -0.01, 15 * cos(i));
	}

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void drawFloor(){
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
		glTexCoord2f(0, 10);
	glVertex3f(-6, -1, 3.5);
		glTexCoord2f(0, 0);
	glVertex3f(6.6, -1, 3.5);
		glTexCoord2f(10, 0);
	glVertex3f(6.6, -1, -9.1);
		glTexCoord2f(10, 10);
	glVertex3f(-6, -1, -9.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


}



void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	// camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	gluLookAt(0.0 + camX, 4.0 + camY, 6.0 + camZ, 0, 4, 0, 0, 1.0, 0);

	// move the object frame using keyboard keys
	glTranslatef(moveX, moveY, moveZ);
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);


	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(1.0, 1.0, 0.0);
	//DrawGrid();

	glPushMatrix();
	glRotatef(animateRotation, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 1.6, 0.0);

	//drawVehicle();
	//drawFence();
	//drawCircle(0.25);
	glPushMatrix();
	glTranslatef(0, 1, 0);
	drawFloor();
	drawModel();
	glPopMatrix();
	clipPlane();
	glPopMatrix();
	//drawRoad();

	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();

}

void Timer(int x){
	animateRotation += animateRotation >= 360.0 ? -animateRotation : 5;
	glutPostRedisplay();

	glutTimerFunc(60, Timer, 1);
}

void TimerFan(int x){
	rotFan += rotFan >= 360.0 ? -rotFan : 5;
	glutPostRedisplay();

	glutTimerFunc(40, TimerFan, 1);
}

GLfloat xstep = 0.1f;
//GLfloat windowW = 10;


void TimerVehical(int value){

	if (moveCar == 1){
		if (transVeh >= 10){
			xstep = -xstep;
		}
		transVeh += xstep;
		if (transVeh <= 0){
			moveCar = 0;
			xstep = -xstep;
		}
	}


	glutPostRedisplay();         // invoke a recall of the display function
	glutTimerFunc(30, TimerVehical, 1);        // inorder to continue animating the Timer function is called within itself

}


void keyboardSpecial(int key, int x, int y){
	if (key == GLUT_KEY_UP){
		moveZ += 1;
		if (moveZ >= 17){
			moveZ -= 1;
		}
	}
		

	if (key == GLUT_KEY_DOWN){
		moveZ -= 1;
		if (moveZ <= -9){
			moveZ += 1;
		}
	}
		

	if (key == GLUT_KEY_LEFT)
		rotY += 5.0;

	if (key == GLUT_KEY_RIGHT)
		rotY -= 5.0;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
	if (key == 'w')
		camY += 0.5;
	if (key == 's')
		camY -= 0.5;

	if (key == 'c')
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// glPolygonMode(GL_FRONT, GL_FILL);
	if (key == 'C')
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (key == 'k')
		glDisable(GL_LIGHT0);
	if (key == 'K')
		glEnable(GL_LIGHT0);
	if (key == 'l')
		glDisable(GL_LIGHT1);
	if (key == 'L')
		glEnable(GL_LIGHT1);
	if (key == 'j')
		glDisable(GL_LIGHT2);
	if (key == 'J')
		glEnable(GL_LIGHT2);
	if (key == 'v')
		moveCar = 1;
	if (key == 'V')
		moveCar = 0;
	if (key == 'm')
		glutTimerFunc(90, TimerFan, 1);
	glutPostRedisplay();

}


void changeSize(GLsizei w, GLsizei h){
	glViewport(0, 0, w, h);
	GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Define the Perspective projection frustum 
	// (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
	gluPerspective(120.0, aspect_ratio, 1.0, 100.0);

	// if(w <= h)
	//     glOrtho(-20.0, 20.0, -20/aspect_ratio, 20/aspect_ratio, 20.0, -20.0);

	// else
	//     glOrtho(-20.0* aspect_ratio, 20.0* aspect_ratio, -20.0, 20.0, 20.0, -20.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutCreateWindow("OpenGL Setup Test");
	glutInitWindowSize(100, 100);
	glutInitWindowPosition(150, 150);
	init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	// keyboard function activation
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);

	//glutTimerFunc(60.0, Timer, 1);
	glutTimerFunc(40, TimerFan, 1);
	glutTimerFunc(30, TimerVehical, 1);
	glutMainLoop();


	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}



