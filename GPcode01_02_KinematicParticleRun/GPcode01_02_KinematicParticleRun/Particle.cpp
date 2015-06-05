#include <stdlib.h>
#include "Particle.h"

CParticle::CParticle() {
    radius = 1.0f;
    center.set(0.0, 0.0, 0.0);
}

void CParticle::setPosition(double x, double y, double z) {
    center.set(x,y,z);
}

void CParticle::setRadius(double r) {
    radius = r;
    
}

void CParticle::drawWithGL(int drawMode) {
    glPushMatrix();
    glTranslated(center[0], center[1], center[2]);
    if (drawMode == SPHERE_DRAW) {
        glutWireSphere(radius, 10, 10);
    }
    else {
        glBegin(GL_POINTS);
        glVertex3f(0,0,0);
        glEnd();
    }
    glPopMatrix();
}

void CParticle::randomInit() {
    initialLoc.set(0,1,0);
    initialVel.set((rand()%20000)/10000.0-1.0, (rand()%20000)/10000.0 + 1.0, (rand()%20000)/10000.0-1.0);
    gravity.set(0.0, -9.8, 0.0);
    radius = 0.1;
    currentLoc = initialLoc;
}

void CParticle::simulate(double dt, double et) {
    currentLoc = initialLoc + et*initialVel + (0.5 * et * et)  * gravity ;
    
    setPosition(currentLoc[0], currentLoc[1], currentLoc[2]);
}