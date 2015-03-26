#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include "StopWatch.h"
#include "Simulator.h"

CStopWatch myWatch;
CSimulator mySimulator;

bool bRunning = false;
double elapsed = 0.0; // second
double dt;



void setupOpenGL(int *argcPtr, char **argv, char *title, int sizeX, int sizeY) {
	glutInit(argcPtr, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(sizeX, sizeY);
	glutCreateWindow(title);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.8, 0.8, 1.0, 1.0);
}


void setupCamera(float x, float y, float z, float targetx, float targety, float targetz, float upx, float upy, float upz) {
	glLoadIdentity();
	gluLookAt(x, y, z, targetx, targety, targetz, upx, upy, upz);
}

void DrawSphere(float radius, float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glutWireSphere(radius, 10, 10);
	glPopMatrix();
}

void DrawLine(float x, float y, float z, float xx, float yy, float zz) {
	glBegin(GL_LINES);
	glVertex3f(x, y, z);
	glVertex3f(xx, yy, zz);
	glEnd();
}

void Init(void) {
	glClearColor(0, 0.5, 0.5, 0);

}


/***********************************************************************
*** CALL-BACK Functions
*
* Reshape, Keyboard, Display, Idle Functions
************************************************************************/
void reshapeFunction(int w, int h) {
	if (h == 0) h = 1;
	float ratio = 1.0* w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void keyboardFunction(unsigned char key, int x, int y) {
	if (key == 27) exit(0);
}

void idleFunction(void) {
	glutPostRedisplay();
}

void displayFunction(void) {

	if (!bRunning) {
		myWatch.start();
		bRunning = true;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setupCamera(1, 2, 2, 0, 0, 0, 0, 1, 0);

	glColor3f(1.0, 0.0, 0.0); DrawLine(0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0); DrawLine(0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0); DrawLine(0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	myWatch.stop();
	dt = myWatch.getElapsedTime();
	myWatch.start();

	DrawSphere(0.1, 0.0, 0.0, 0.0);

	glutSwapBuffers();
}

int main(int argc, char **argv) {


	setupOpenGL(&argc, argv, "Kinematics", 512, 512);

	// initialization code 
	Init();

	// registration of callbacks
	glutDisplayFunc(displayFunction);
	glutIdleFunc(idleFunction);
	glutKeyboardFunc(keyboardFunction);
	glutReshapeFunc(reshapeFunction);
	
	// entering the main loop
	glutMainLoop();

	return 0;
}
