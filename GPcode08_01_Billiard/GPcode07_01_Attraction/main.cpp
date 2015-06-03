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
#include "DynamicSimulator.h"
#include "Vec3d.h"

CStopWatch myWatch;
CDynamicSimulator mySimulator;
CSimulator* Simulator = (CSimulator *) &mySimulator;

double deltaTime = 0.0; // unit: second
double currentTime = 0.0; // unit: second



void setupOpenGL(int *argcPtr, char *argv[], char title[], int sizeX, int sizeY) {
	glutInit(argcPtr, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(sizeX, sizeY);
	glutCreateWindow(title);
	glEnable(GL_DEPTH_TEST);
}


void setupCamera(
			float x, float y, float z, 
			float targetx, float targety, float targetz,
			float upx, float upy, float upz) {
	glLoadIdentity();
	gluLookAt(x, y, z, targetx, targety, targetz, upx, upy, upz);
}



void Init(void) {
	glClearColor(0.75, 0.75, 0.75, 0);
    Simulator->init();
    glPointSize(2);

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
    gluPerspective(60, ratio, 0.1, 5000);
	glMatrixMode(GL_MODELVIEW);
}

void key_ready(unsigned char key) {
    switch (key) {
    case 's': // start game
            Simulator->start(); myWatch.start();
            ((CDynamicSimulator *)Simulator)->setMode(AIMING);
            break;
    }
}

void key_aiming(unsigned char key) {
    switch (key) {
        case '.': ((CDynamicSimulator *)Simulator)->rotateAim( 0.05);break;
        case ',': ((CDynamicSimulator *)Simulator)->rotateAim(-0.05);break;
        case 'm': ((CDynamicSimulator *)Simulator)->rotateAim(-0.01);break;
        case '/': ((CDynamicSimulator *)Simulator)->rotateAim( 0.01);break;
        case ' ': ((CDynamicSimulator *)Simulator)->shot();break;
    }
}
void key_simulating(unsigned char key) {
    switch (key) {
        case 'p': myWatch.pause(); Simulator->pause(); break;
        case 'r': myWatch.resume(); break;
        case ' ': ((CDynamicSimulator *)Simulator)->turnOver();break;
        default: break;
    }
}

void KEY_turnover(unsigned char key) {
    switch (key) {
        case ' ':((CDynamicSimulator *)Simulator)->setMode(AIMING); break;
    }
}

void keyboardFunction(unsigned char key, int x, int y) {
	if (key == 27) exit(0);
    gameMode mode = ((CDynamicSimulator *)Simulator)->getMode();
    switch(mode) {
    case READY: key_ready(key); break;
    case AIMING: key_aiming(key); break;
    case SIMULATING: key_simulating(key); break;
    case TURNOVER: KEY_turnover(key); break;
    default: break;
    }
}

void idleFunction(void) {
	glutPostRedisplay();
}

void displayFunction(void) {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setupCamera(0, 2500, 0, 0, 0, 0, 1, 0, 0);
    
    
    // check DT (in microsecond) from StopWatch and store it to "deltaTime" (in seconds)
	deltaTime = myWatch.checkAndComputeDT() / 1000000.0;
    currentTime = myWatch.getTotalElapsedTime() / 1000000.0;
	Simulator->actions(deltaTime, currentTime);

	glutSwapBuffers();
}

int main(int argc, char **argv) {


	setupOpenGL(&argc, argv, "BILLIARDS", 512, 512);

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