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

void CParticle::drawWithGL(void) {
    glPushMatrix();
    glTranslated(center[0], center[1], center[2]);
    glBegin(GL_POINTS);
    glVertex3f(0,0,0);
    glEnd();
    //glutWireSphere(radius, 3, 3);
    glPopMatrix();
}

void CParticle::randomInit() {
    double speed = rand()%10000 / 10000.0 + 1.0;
    double theta = 2.0*3.141592 * (rand()%10000 / 10000.0);
    double phi =   2.0*3.141592 * (rand()%10000 / 10000.0);
    double vx,vy,vz;
    vy = speed*cos(phi)+2.0;
    vx = speed*cos(theta)*sin(phi);
    vz = speed*sin(theta)*sin(phi);
    initialLoc.set(0,1,0);
    initialVel.set(vx, vy, vz);
    gravity.set(0.0, -9.8, 0.0);
    radius = 0.01;
    currentLoc = initialLoc;
}

void CParticle::simulate(double dt, double et) {
    currentLoc = initialLoc + et*initialVel + (0.5 * et * et)  * gravity ;
    
    setPosition(currentLoc[0], currentLoc[1], currentLoc[2]);
}