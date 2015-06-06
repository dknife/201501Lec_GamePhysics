#include <stdlib.h>
#include "Particle.h"

CParticle::CParticle() {
    radius = 1.0f;
    loc.set(0.0, 0.0, 0.0);
    spin = 0.0;
}

void CParticle::setPosition(double x, double y, double z) {
    loc.set(x,y,z);
}
void CParticle::setVelocity(double vx, double vy, double vz) {
	vel.set(vx,vy,vz);
}

void CParticle::setMass  (double m) { mass = m; }
void CParticle::setRadius(double r) { radius = r; }
void CParticle::setColor (double r, double g, double b) { color.set(r,g,b); }
void CParticle::setSpin(double s) { spin = s; }

CVec3d CParticle::getPosition() { return loc ; }
CVec3d CParticle::getVelocity() { return vel ; }
double CParticle::getMass()     { return mass; }
double CParticle::getRadius()   { return radius; }
double CParticle::getSpin()     { return spin; }

void CParticle::drawWithGL(int drawMode) {
    glColor3f(color.x, color.y, color.z);

    glPushMatrix();
    glTranslated(loc[0], loc[1], loc[2]);
    if (drawMode == SPHERE_DRAW) {
        glutWireSphere(radius, 30, 30);
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
    if(this->vel.len()<10) vel.set(0.0,0.0,0.0);
}

void CParticle::resetForce(void) {	this->force.set(0.0, 0.0, 0.0); }
void CParticle::addForce(CVec3d &f) { this->force = this->force + f; }