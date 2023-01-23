

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "GL\glut.h"
#include "GL\gl.h"
#include "GL\glu.h"


int shape;	//1=point, 2=line, 3=triangle, 4=square, 5=hexagon, 6=circle, 7=cube

			// colors
GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat red[] = { 0.8, 0.0, 0.0, 1.0 };
GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat purple[] = { 0.5, 0.0, 0.5, 1.0 };
GLfloat cyan[] = { 0.0, 0.5, 0.5, 1.0 };
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat orange[] = { 1.0, 0.5, 0.0, 1.0 };
GLfloat yellow[] = { 1.0, 0.8, 0.0, 1.0 };
GLfloat greenYellow[] = { 0.5, 1.0, 0.0 };
GLfloat darkGreen[] = { 0.0, 0.5, 0.0 };
GLfloat emissiveWhite[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat darkGrey[] = { 0.3, 0.3, 0.3, 1.0 };

// light0 is pointing at an infinite location
GLfloat light0_pos[] = { -4, 0.0, 5.0, 0.0 };

// light1 is pointing at a finite location
GLfloat light1_pos[] = { -1, 0, 5, 1.0 };
GLfloat light1_pos1[] = { -0.5, 1, 5, 1.0 };
GLfloat light1_pos2[] = { 0.5, 1, 5, 1.0 };
GLfloat light1_pos3[] = { 1, 0, 5, 1.0 };

// light2 is the spotlight
GLfloat light2_pos[] = { -.25, 0.95, 0.0, 1.0 };
GLfloat light2_direction[] = { 0.25, -0.75, 0.0, 1.0 };
GLfloat light2_cutoff = 75;
GLfloat light2_exp = 5;

// white ambient light
GLfloat ambientColor[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat planeFloor[] = { 0,1,0,0 };

GLfloat normX;
GLfloat normY;
GLfloat normZ;

float no_shiny = 0.0;
float low_shiny = 5.0;
float high_shiny = 100.0;

//calculates normal for planar polygons using 3 vertices
void getNormal_from3Points(GLfloat vertex1[], GLfloat vertex2[], GLfloat vertex3[], GLfloat *normX, GLfloat *normY, GLfloat *normZ) {

	GLfloat uX;
	GLfloat uY;
	GLfloat uZ;
	GLfloat vX;
	GLfloat vY;
	GLfloat vZ;

	uX = vertex2[0] - vertex1[0];
	uY = vertex2[1] - vertex1[1];
	uZ = vertex2[2] - vertex1[2];

	vX = vertex3[0] - vertex1[0];
	vY = vertex3[1] - vertex1[1];
	vZ = vertex3[2] - vertex1[2];

	*normX = uY*vZ - uZ*vY;
	*normY = uX*vZ - uZ*vX;
	*normZ = uX*vY - uY*vX;
}

void drawPoint() {
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(0.15, 0.15, 0.0);
	glEnd();
}

void drawLine() {
	GLfloat v1[] = { -1.0, 0.0, 0.0 };
	GLfloat v2[] = { 1.0, 0.0, 0.0 };

	glBegin(GL_LINES);
	glNormal3f(0, 0, 1);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glEnd();
}

void drawTriangle() {
	GLfloat v1[] = { -0.5, -0.5, 0.0 };
	GLfloat v2[] = { 0.0, 0.5, 0.0 };
	GLfloat v3[] = { 0.5, -0.5, 0.0 };

	//FLAT shading
	glBegin(GL_POLYGON);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	getNormal_from3Points(v1, v2, v3, &normX, &normY, &normZ);
	glNormal3f(normX, normY, normZ);
	glEnd();
}

void drawSquare() {
	GLfloat v1[] = { -0.5, -0.5, 0.0 };
	GLfloat v2[] = { -0.5, 0.5, 0.0 };
	GLfloat v3[] = { 0.5, 0.5, 0.0 };
	GLfloat v4[] = { 0.5, -0.5, 0.0 };

	//FLAT shading
	glBegin(GL_POLYGON);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	getNormal_from3Points(v1, v2, v3, &normX, &normY, &normZ);
	glNormal3f(normX, normY, normZ);
	glEnd();
}

void drawHexagon() {
	GLfloat v1[] = { 0.5, 0.0, 0.0 };
	GLfloat v2[] = { 0.25, 0.433, 0.0 };
	GLfloat v3[] = { -0.25, 0.433, 0.0 };
	GLfloat v4[] = { -0.5, 0.0, 0.0 };
	GLfloat v5[] = { -0.25, -0.433, 0.0 };
	GLfloat v6[] = { 0.25, -0.433, 0.0 };

	//FLAT shading
	glBegin(GL_POLYGON);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glVertex3fv(v5);
	glVertex3fv(v6);
	getNormal_from3Points(v1, v2, v3, &normX, &normY, &normZ);
	glNormal3f(normX, normY, normZ);
	glEnd();
}

void drawCircle() {
	glBegin(GL_LINE_LOOP);
	const float PI = 3.1415926535;
	double radius = 0.5;
	int i;
	int sides = 200;

	for (i = 0; i < 360; i += 360 / sides)
	{

		double angle = PI * i / 180;
		glVertex2d(cos(angle)*radius, sin(angle)*radius);
	}
	glEnd();
}

void drawSphere(double radius) {
	glutSolidSphere(radius, 30, 30);
}

void drawSphere2(double radius) {
	double alpha;
	double beta;
	double deltaAlpha;
	double deltaBeta;
	GLfloat x, y, z;

	deltaAlpha = 0.25;
	deltaBeta = 0.25;

	for (alpha = -90.0; alpha + deltaAlpha <= 90.0; alpha += deltaAlpha) {
		glBegin(GL_QUAD_STRIP);
		for (beta = 0.0; beta <= 360.0; beta += deltaBeta) {
			x = radius * cos(beta) * cos(alpha);
			y = radius * sin(beta) * cos(alpha);
			z = radius * sin(alpha);

			//calculate normals
			getNormal_from3Points(&x, &y, &z, &normX, &normY, &normZ);
			GLfloat normal[] = { normX, normY, normZ };
			glNormal3fv(normal);
			glVertex3f(x, y, z);

			x = radius * cos(beta) * cos(alpha + deltaAlpha);
			y = radius * sin(beta) * cos(alpha + deltaAlpha);
			z = radius * sin(alpha + deltaAlpha);
			getNormal_from3Points(&x, &y, &z, &normX, &normY, &normZ);
			GLfloat normal2[] = { normX, normY, normZ };
			glNormal3fv(normal2);
			glVertex3f(x, y, z);

			glVertex3f(x, y, z);
		}
		glEnd();

	}
}

void drawCube() {
	GLfloat v1[] = { 0.5, -0.5, -0.5 };
	GLfloat v2[] = { 0.5, 0.5, -0.5 };
	GLfloat v3[] = { -0.5, 0.5, -0.5 };
	GLfloat v4[] = { -0.5, -0.5, -0.5 };
	GLfloat v5[] = { 0.5, -0.5, 0.5 };
	GLfloat v6[] = { 0.5, 0.5, 0.5 };
	GLfloat v7[] = { -0.5, 0.5, 0.5 };
	GLfloat v8[] = { -0.5, -0.5, 0.5 };

	double tempX, tempY, tempZ;

	//calculate surface normals
	getNormal_from3Points(v1, v2, v3, &normX, &normY, &normZ);
	GLfloat frontNormal[] = { normX, normY, normZ };

	getNormal_from3Points(v5, v6, v7, &normX, &normY, &normZ);
	GLfloat backNormal[] = { normX, normY, normZ };

	getNormal_from3Points(v1, v2, v6, &normX, &normY, &normZ);
	GLfloat rightNormal[] = { normX, normY, normZ };

	getNormal_from3Points(v8, v7, v3, &normX, &normY, &normZ);
	GLfloat leftNormal[] = { normX, normY, normZ };

	getNormal_from3Points(v6, v2, v3, &normX, &normY, &normZ);
	GLfloat topNormal[] = { normX, normY, normZ };

	getNormal_from3Points(v1, v5, v8, &normX, &normY, &normZ);
	GLfloat bottomNormal[] = { normX, normY, normZ };

	//calculate v1 normal with RIGHT, BOTTOM, and BACK surface normals
	tempX = (rightNormal[0] + bottomNormal[0] + backNormal[0]) / 3;
	tempY = (rightNormal[1] + bottomNormal[1] + backNormal[1]) / 3;
	tempZ = (rightNormal[2] + bottomNormal[2] + backNormal[2]) / 3;

	GLfloat v1_normal[] = { tempX, tempY, tempZ };

	//calculate v2 normal with RIGHT, TOP, and BACK surface normals
	tempX = (rightNormal[0] + topNormal[0] + backNormal[0]) / 3;
	tempY = (rightNormal[1] + topNormal[1] + backNormal[1]) / 3;
	tempZ = (rightNormal[2] + topNormal[2] + backNormal[2]) / 3;

	GLfloat v2_normal[] = { tempX, tempY, tempZ };

	//calculate v3 normal with LEFT, TOP, and BACK surface normals
	tempX = (leftNormal[0] + topNormal[0] + backNormal[0]) / 3;
	tempY = (leftNormal[1] + topNormal[1] + backNormal[1]) / 3;
	tempZ = (leftNormal[2] + topNormal[2] + backNormal[2]) / 3;

	GLfloat v3_normal[] = { tempX, tempY, tempZ };

	//calculate v4 normal with LEFT, BOTTOM, and BACK surface normals
	tempX = (leftNormal[0] + bottomNormal[0] + backNormal[0]) / 3;
	tempY = (leftNormal[1] + bottomNormal[1] + backNormal[1]) / 3;
	tempZ = (leftNormal[2] + bottomNormal[2] + backNormal[2]) / 3;

	GLfloat v4_normal[] = { tempX, tempY, tempZ };

	//calculate v5 normal with RIGHT, BOTTOM, and FRONT surface normals
	tempX = (rightNormal[0] + bottomNormal[0] + frontNormal[0]) / 3;
	tempY = (rightNormal[1] + bottomNormal[1] + frontNormal[1]) / 3;
	tempZ = (rightNormal[2] + bottomNormal[2] + frontNormal[2]) / 3;

	GLfloat v5_normal[] = { tempX, tempY, tempZ };

	//calculate v6 normal with RIGHT, TOP, and FRONT surface normals
	tempX = (rightNormal[0] + topNormal[0] + frontNormal[0]) / 3;
	tempY = (rightNormal[1] + topNormal[1] + frontNormal[1]) / 3;
	tempZ = (rightNormal[2] + topNormal[2] + frontNormal[2]) / 3;

	GLfloat v6_normal[] = { tempX, tempY, tempZ };

	//calculate v7 normal with LEFT, TOP, and FRONT surface normals
	tempX = (leftNormal[0] + topNormal[0] + frontNormal[0]) / 3;
	tempY = (leftNormal[1] + topNormal[1] + frontNormal[1]) / 3;
	tempZ = (leftNormal[2] + topNormal[2] + frontNormal[2]) / 3;

	GLfloat v7_normal[] = { tempX, tempY, tempZ };

	//calculate v8 normal with LEFT, BOTTOM, and FRONT surface normals
	tempX = (leftNormal[0] + bottomNormal[0] + frontNormal[0]) / 3;
	tempY = (leftNormal[1] + bottomNormal[1] + frontNormal[1]) / 3;
	tempZ = (leftNormal[2] + bottomNormal[2] + frontNormal[2]) / 3;

	GLfloat v8_normal[] = { tempX, tempY, tempZ };

	//FRONT
	glBegin(GL_POLYGON);
	glNormal3fv(v1_normal);
	glVertex3fv(v1);
	glNormal3fv(v2_normal);
	glVertex3fv(v2);
	glNormal3fv(v3_normal);
	glVertex3fv(v3);
	glNormal3fv(v4_normal);
	glVertex3fv(v4);
	glEnd();

	//BACK
	glBegin(GL_POLYGON);
	glNormal3fv(v5_normal);
	glVertex3fv(v5);
	glNormal3fv(v6_normal);
	glVertex3fv(v6);
	glNormal3fv(v7_normal);
	glVertex3fv(v7);
	glNormal3fv(v8_normal);
	glVertex3fv(v8);
	glEnd();

	//RIGHT
	glBegin(GL_POLYGON);
	glNormal3fv(v1_normal);
	glVertex3fv(v1);
	glNormal3fv(v2_normal);
	glVertex3fv(v2);
	glNormal3fv(v6_normal);
	glVertex3fv(v6);
	glNormal3fv(v5_normal);
	glVertex3fv(v5);
	glEnd();

	//LEFT
	glBegin(GL_POLYGON);
	glNormal3fv(v8_normal);
	glVertex3fv(v8);
	glNormal3fv(v7_normal);
	glVertex3fv(v7);
	glNormal3fv(v3_normal);
	glVertex3fv(v3);
	glNormal3fv(v4_normal);
	glVertex3fv(v4);
	glEnd();

	//TOP
	glBegin(GL_POLYGON);
	glNormal3fv(v6_normal);
	glVertex3fv(v6);
	glNormal3fv(v2_normal);
	glVertex3fv(v2);
	glNormal3fv(v3_normal);
	glVertex3fv(v3);
	glNormal3fv(v7_normal);
	glVertex3fv(v7);
	glEnd();

	//BOTTOM
	glBegin(GL_POLYGON);
	glNormal3fv(v1_normal);
	glVertex3fv(v1);
	glNormal3fv(v5_normal);
	glVertex3fv(v5);
	glNormal3fv(v8_normal);
	glVertex3fv(v8);
	glNormal3fv(v4_normal);
	glVertex3fv(v4);
	glEnd();
}

void shadowMatrix(GLfloat ground[4], GLfloat light[4])
{
	float  dot;
	float  shadowMat[4][4];

	dot = ground[0] * light[0] +
		ground[1] * light[1] +
		ground[2] * light[2] +
		ground[3] * light[3];

	shadowMat[0][0] = dot - light[0] * ground[0];
	shadowMat[1][0] = 0.0 - light[0] * ground[1];
	shadowMat[2][0] = 0.0 - light[0] * ground[2];
	shadowMat[3][0] = 0.0 - light[0] * ground[3];

	shadowMat[0][1] = 0.0 - light[1] * ground[0];
	shadowMat[1][1] = dot - light[1] * ground[1];
	shadowMat[2][1] = 0.0 - light[1] * ground[2];
	shadowMat[3][1] = 0.0 - light[1] * ground[3];

	shadowMat[0][2] = 0.0 - light[2] * ground[0];
	shadowMat[1][2] = 0.0 - light[2] * ground[1];
	shadowMat[2][2] = dot - light[2] * ground[2];
	shadowMat[3][2] = 0.0 - light[2] * ground[3];

	shadowMat[0][3] = 0.0 - light[3] * ground[0];
	shadowMat[1][3] = 0.0 - light[3] * ground[1];
	shadowMat[2][3] = 0.0 - light[3] * ground[2];
	shadowMat[3][3] = dot - light[3] * ground[3];

	glMultMatrixf((const GLfloat*)shadowMat);
}


void reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)(width), (GLsizei)(height));
	/*if (width > height)
	glViewport((width-height)/2,0,height,height);
	else
	glViewport(0,(height-width)/2,width,width);
	*/
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(25, 4.0/3.0, 1.0, 5.0);
	//glLoadIdentity();
	//place the camera at (0,0,5) and point towards (0,0,0) with y-axis as up vector
	//gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0, 1, 0);
}

void myInit(void) {

	//setWindow();
	//setViewport(0, 2000, 0, 2000);

	glEnable(GL_NORMALIZE);
	//glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_SCISSOR_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25, 1.0, 1.0, 15.0);
	//glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	//place the camera at (0,0,5) and point towards (0,0,0) with y-axis as up vector
	gluLookAt(0.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0, 1, 0);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(3.0);
	glPointSize(6.0);







}


void renderScene() {

	glPushMatrix();
	glScaled(2.0, 2.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, darkGreen);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkGreen);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, &no_shiny);
	drawPoint();
	glPopMatrix();

	glPushMatrix();
	glRotated(-10.0, 0.0, 0.0, 1.0);
	glScaled(0.25, 0.25, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, greenYellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, greenYellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, &no_shiny);
	drawLine();
	glPopMatrix();

	glPushMatrix();
	glRotated(-15.0, 0.0, 0.0, 1.0);
	glScaled(0.15, 0.15, 0.0);
	glTranslated(0.25, 2.5, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, &no_shiny);
	drawTriangle();
	glPopMatrix();

	glPushMatrix();
	glRotated(25.0, 0.0, 0.0, 1.0);
	glScaled(0.5, 0.5, 0.0);
	glTranslated(-0.5, -1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, orange);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, orange);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, &no_shiny);
	drawSquare();
	glPopMatrix();

	glPushMatrix();
	glRotated(45.0, 0.0, 0.0, 1.0);
	glScaled(0.25, 0.75, 0.0);
	glTranslated(-1.5, 0.5, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, &no_shiny);
	drawCircle();
	glPopMatrix();

	glPushMatrix();
	glRotated(-45.0, 0.0, 0.0, 1.0);
	glScaled(0.15, 0.75, 0.0);
	glTranslated(4.0, 0.5, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, green);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, &no_shiny);
	drawHexagon();
	glPopMatrix();

	glPushMatrix();
	glScaled(0.2, 0.2, 0.2);
	glTranslated(-2.5, 2.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, purple);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, purple);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, &high_shiny);
	drawCube();
	glPopMatrix();


	glPushMatrix();
	glScaled(0.15, 0.15, 0.0);
	glTranslated(-0.5, 0.75, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, &low_shiny);
	drawCube();
	glPopMatrix();


	glPushMatrix();
	glTranslated(0.0, 0.75, -0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, cyan);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, &high_shiny);
	drawSphere2(0.1);
	glPopMatrix();

	//this is the visible light source object with emissive properties
	glPushMatrix();
	glTranslated(-0.25, 0.95, 0.0);
	glMaterialfv(GL_FRONT, GL_EMISSION, white);
	glMaterialfv(GL_FRONT, GL_AMBIENT, white);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, &no_shiny);
	drawSphere2(0.05);
	glMaterialfv(GL_FRONT, GL_EMISSION, black);

	glPopMatrix();


	//FLOOR- this is the plane that shadows will be cast on
	glPushMatrix();

	glScaled(2.25, 2.25, 1);
	glTranslatef(0.0, -.5, 0);
	glRotated(90.0, 1, 0, 0);
	//glRotated(45.0, 1, 0, 0);
	//glTranslatef(0.0, 2.0, -1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, darkGrey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkGrey);
	glMaterialfv(GL_FRONT, GL_SPECULAR, darkGrey);
	glMaterialfv(GL_FRONT, GL_SHININESS, &no_shiny);
	/*glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	glVertex3f(2.0, -1.0, -5.0);
	glVertex3f(2.0, -1.0, 5.0);
	glVertex3f(-2.0, -1.0, 5.0);
	glVertex3f(-2.0, -1.0, -5.0);
	glEnd();*/
	drawSquare();
	glPopMatrix();

	//draw a 'shadow' object of the sphere
	glPushMatrix();
	glTranslatef(0.0, -1.2, 0);
	shadowMatrix(planeFloor, light2_pos);
	glMaterialfv(GL_FRONT, GL_AMBIENT, darkGrey);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, darkGrey);
	glMaterialfv(GL_FRONT, GL_SPECULAR, darkGrey);
	glMaterialfv(GL_FRONT, GL_SHININESS, &no_shiny);
	//glTranslated(0.75, 0.75, -0.0);

	drawSphere2(0.3);

	glPopMatrix();


	//draw a 'shadow' object of the cube
	glPushMatrix();
	glScaled(0.2, 0.2, 0.2);
	glTranslatef(-3, -5.5, 0);
	shadowMatrix(planeFloor, light2_pos);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, darkGrey);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, darkGrey);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, darkGrey);
	//glMaterialfv(GL_FRONT, GL_SHININESS, &no_shiny);
	//glTranslated(0.75, 0.75, -0.0);

	drawCube();
	glPopMatrix();





	// glFlush();
}

void myDisplay(void) {
	int width = 800;
	int height = 600;

	int viewportNum;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (viewportNum = 1; viewportNum <= 4; viewportNum++) {
		switch (viewportNum) {
		case 1:
			//TOP LEFT
			//glViewport(0, height / 2, width / 2, height / 2);
			glViewport(100, height / 2, height / 2, height / 2);
			glShadeModel(GL_SMOOTH);
			glLightfv(GL_LIGHT0, GL_AMBIENT, cyan);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, cyan);
			glLightfv(GL_LIGHT0, GL_SPECULAR, cyan);
			glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
			glEnable(GL_LIGHT0);

			//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

			// light1 parameters- finite

			glLightfv(GL_LIGHT1, GL_AMBIENT, purple);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, purple);
			glLightfv(GL_LIGHT1, GL_SPECULAR, purple);
			glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
			glEnable(GL_LIGHT1);

			// light2 parameters- spot
			glLightfv(GL_LIGHT2, GL_AMBIENT, white);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, white);
			glLightfv(GL_LIGHT2, GL_SPECULAR, black);
			glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_direction);
			glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, &light2_cutoff);
			glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, &light2_exp);
			glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
			glEnable(GL_LIGHT2);


			break;
		case 2:
			//TOP RIGHT
			glViewport(400, height / 2, height / 2, height / 2);
			glShadeModel(GL_SMOOTH);

			// light1 parameters- finite
			glLightfv(GL_LIGHT1, GL_POSITION, light1_pos1);
			glEnable(GL_LIGHT1);

			// light2 parameters- spot
			glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_direction);
			glEnable(GL_LIGHT2);

			break;
		case 3:
			//BOTTOM LEFT
			//glViewport(0, 0, width / 2, height / 2);
			glViewport(100, 0, height / 2, height / 2);
			glShadeModel(GL_FLAT);

			// light1 parameters- finite
			glLightfv(GL_LIGHT1, GL_POSITION, light1_pos2);
			glEnable(GL_LIGHT1);

			// light2 parameters- spot
			glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_direction);
			glEnable(GL_LIGHT2);
			break;

		case 4:
			//BOTTOM RIGHT
			glViewport(400, 0, height / 2, height / 2);
			glShadeModel(GL_SMOOTH);

			// light1 parameters- finite
			glLightfv(GL_LIGHT1, GL_POSITION, light1_pos3);
			glEnable(GL_LIGHT1);

			// light2 parameters- spot
			glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_direction);
			glEnable(GL_LIGHT2);

			// light3 parameters- ambient
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
			break;
		}
		renderScene();

		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);

	}

	glutSwapBuffers();
}

void myKeyboard(unsigned char key, int mouseX, int mouseY) {

	switch (key)
	{
	case 'Q':
	case'q':
		exit(-1);

	case 'p':
		shape = 1;
		glutPostRedisplay();
		break;
	case 'l':
		shape = 2;
		glutPostRedisplay();
		break;
	case 't':
		shape = 3;
		glutPostRedisplay();
		break;
	case 's':
		shape = 4;
		glutPostRedisplay();
		break;
	case 'h':
		shape = 5;
		glutPostRedisplay();
		break;
	case 'c':
		shape = 6;
		glutPostRedisplay();
		break;
	case 'u':
		shape = 7;
		glutPostRedisplay();
		break;
	default:
		break;
	}

}

int main(int argc, char** argv) {

	glutInit(&argc, argv);		//initialize toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 150);

	glutCreateWindow("Interactive Shape Display!");
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc(reshape);

	myInit();

	glutMainLoop();
	return 0;
}
