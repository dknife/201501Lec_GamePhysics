#include "Particle.h"

CParticle::CParticle() {
    radius = 0.1f;
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
    glutWireSphere(radius, 20, 20);
    glPopMatrix();
}