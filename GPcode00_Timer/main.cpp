#include <stdio.h>
#include <stdlib.h>
#include <GLUT/GLUT.h>

#include "StopWatch.h"

StopWatch stopWatch;
bool started = false;

void Draw(int i) {
	// drawing clock
	double d;
	glPushMatrix();
	glRotatef(i*6, 0,0,1);
	if(i%5==0) d=2.0;
	else d = 1.0;
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.01*d, 1.0, 0.0);
	glVertex3f( 0.01*d, 1.0, 0.0);
	glVertex3f( 0.0 , 1.0-0.1*d, 0.0);
	glEnd();
	glPopMatrix();
}
void changeSize(int w, int h) {
	if(h == 0) h = 1;
	float ratio = 1.0* w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}
void renderScene(void) {
	if(!started) {
		stopWatch.start();
		started = true;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0, 0.0,0.0,-1.0, 0.0f,1.0f,0.0f);
	for(int i=0; i<60; i++) { Draw(i); }
	glColor3f(0,0,0);
	
	static float angle;
	stopWatch.stop();
	float dt = stopWatch.getElapsedTime();
	stopWatch.start();
	angle += dt*6.0/1000000.0;
	
	glPushMatrix();
	glRotatef(-angle, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,1.0,0.0);
	glEnd();
	glPopMatrix();
	
	glutSwapBuffers();
}
void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27) exit(0);
}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Dr.Kang's Animation Lecture - 00");
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.8,0.8,1.0,1.0);
	glutMainLoop();
	return 0;
}