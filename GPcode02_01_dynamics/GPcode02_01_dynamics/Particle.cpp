#include <stdlib.h>
#include "Particle.h"

CParticle::CParticle() {
    radius = 1.0f;
    loc.set(0.0, 0.0, 0.0);
}

void CParticle::setPosition(double x, double y, double z) {
    loc.set(x,y,z);
}

void CParticle::setRadius(double r) {
    radius = r;
    
}

void CParticle::drawWithGL(int drawMode) {
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslated(loc[0], loc[1], loc[2]);
    if (drawMode == SPHERE_DRAW) {
        glutWireSphere(radius, 10, 10);
    }
    else {
        glBegin(GL_POINTS);
        glVertex3f(0,0,0);
        glEnd();
    }
    glPopMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
    glTranslated(loc[0], 0, loc[2]);
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
    double speed = rand()%10000 / 10000.0 + 1.0;
    double theta = 2.0*3.141592 * (rand()%10000 / 10000.0);
    double phi =   2.0*3.141592 * (rand()%10000 / 10000.0);
    double vx,vy,vz;
    vy = speed*cos(phi)+2.0;
    vx = speed*cos(theta)*sin(phi);
    vz = speed*sin(theta)*sin(phi);
    loc.set(0,1,0);
    vel.set(vx, vy, vz);
    gravity.set(0.0, -9.8, 0.0);
    radius = 0.01;
}

void CParticle::simulate(double dt, double et) {
    vel = vel + dt*gravity;
    loc = loc + dt*vel;
    if(loc[1]<0) {
        loc.set(loc[0], -0.9*loc[1], loc[2]);
        if(vel[1]<0) vel.set(vel[0], -0.9*vel[1], vel[2]);
    }
    
    setPosition(loc[0], loc[1], loc[2]);
}