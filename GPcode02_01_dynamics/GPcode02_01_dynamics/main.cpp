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


void drawPlane(double wx, double wz, int nStepX, int nStepZ) {
    CVec3d startVert(-wx/2.0, 0.0, -wz/2.0);
    double stepZ = wz/nStepZ;
    double stepX = wx/nStepX;
    
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for(int i=0;i<nStepZ+1; i++) {
        glVertex3d( startVert.x,      startVert.y, startVert.z + stepZ*i);
        glVertex3d( startVert.x + wx, startVert.y, startVert.z + stepZ*i);
    }
    for(int i=0;i<nStepX+1; i++) {
        glVertex3d( startVert.x + stepX*i, startVert.y, startVert.z);
        glVertex3d( startVert.x + stepX*i, startVert.y, startVert.z + wz);
    }
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    
}


void drawAxes(void) {

	GLfloat cData[] = {
		1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 1.0, 0.0, 0.0, 1.0,};
	GLfloat vData[] = {
		0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cData);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vData);
	glDrawArrays(GL_LINES, 0, 6 );
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
	gluPerspective(60, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void keyboardFunction(unsigned char key, int x, int y) {
	if (key == 27) exit(0);
    switch (key) {
        case 's':
            if(!myWatch.bRunning()) { Simulator->start(); myWatch.start(); }
            else { myWatch.stop(); Simulator->stop(); }
            break;
        case 'p':
            myWatch.pause(); Simulator->pause();
            break;
        case 'r':
            myWatch.resume();
        default:
            break;
    }
}

void idleFunction(void) {
	glutPostRedisplay();
}

void displayFunction(void) {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setupCamera(3, 2, 1, 0, 0, 0, 0, 1, 0);

    drawPlane(30.0, 30.0, 150, 150);
    glLineWidth(3); drawAxes(); glLineWidth(1);
    
    // check DT (in microsecond) from StopWatch and store it to "deltaTime" (in seconds)
	deltaTime = myWatch.checkAndComputeDT() / 1000000.0;
    currentTime = myWatch.getTotalElapsedTime() / 1000000.0;
	Simulator->actions(deltaTime, currentTime);

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
