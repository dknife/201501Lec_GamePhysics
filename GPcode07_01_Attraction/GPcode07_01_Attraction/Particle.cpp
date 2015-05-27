#include <stdlib.h>
#include "Particle.h"

CParticle::CParticle() {
    radius = 1.0f;
    loc.set(0.0, 0.0, 0.0);
}



void CParticle::setPosition(double x, double y, double z) {
    loc.set(x,y,z);
}

void CParticle::setVelocity(double vx, double vy, double vz) {
	vel.set(vx,vy,vz);
}

void CParticle::setMass(double m) {
	mass = m;
    radius = sqrt(mass); 
}
CVec3d CParticle::getPosition() {
	return loc;
}
CVec3d CParticle::getVelocity() {
	return vel;
}

double CParticle::getMass() {
	return mass;
}

double CParticle::getRadius() {
	return radius;
}


void CParticle::drawWithGL(int drawMode) {
    glColor3f(1.0, 0.5, 0.0);

    glPushMatrix();
    glTranslated(loc[0], loc[1], loc[2]);
    if (drawMode == SPHERE_DRAW) {
        glutWireSphere(radius*0.5, 15, 15);
    }
    else {
        glBegin(GL_POINTS);
        glVertex3f(0,0,0);
        glEnd();
    }
    glPopMatrix();
    
}



void CParticle::forceIntegration(double dt, double et) {
    
    if(dt>0.1) dt=0.1;
    vel = vel + dt*((1.0/mass) * force );
    loc = loc + dt*vel;
}


void CParticle::simulate(double dt, double et) {
    
    forceIntegration(dt, et);

    
}

void CParticle::resetForce(void) {
	this->force.set(0.0, 0.0, 0.0);
}

void CParticle::addForce(CVec3d &f) {
	this->force = this->force + f;
}