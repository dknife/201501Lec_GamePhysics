#include <stdlib.h>
#include "Particle.h"

CParticle::CParticle() {
    radius = 1.0f;
    loc.set(0.0, 0.0, 0.0);
}

void CParticle::setType(int t) {
	switch(t) {
	case TYPE_WOOD:
	case TYPE_STEEL: type = t; break;
	default: printf("invalid material type");
	}
}

void CParticle::setPosition(double x, double y, double z) {
    loc.set(x,y,z);
}

void CParticle::setRadius(double r) {
    radius = r;
    
}

void CParticle::drawWithGL(int drawMode) {
    if(type==TYPE_WOOD) glColor3f(1.0, 0.5, 0.0);
	else glColor3f(0.3, 0.3, 0.3);

    glPushMatrix();
    glTranslated(loc[0], loc[1], loc[2]);
    if (drawMode == SPHERE_DRAW) {
        glutWireSphere(radius, 20, 20);
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
    double phi =   3.141592 * (rand()%10000 / 10000.0);
    double vx,vy,vz;
    vy = speed*cos(phi)+2.0;
    vx = speed*cos(theta)*sin(phi);
    vz = speed*sin(theta)*sin(phi);

    loc.set(0,2,rand()%20000 / 10000.0 - 1.0);
    vel.set(vx, vy, vz);
    gravity.set(0.0, -9.8, 0.0);
	force.set(0.0, 0.0, 0.0);
    mass = 1;
	radius = 0.1;
	type = TYPE_WOOD + rand()%NUM_MATERIAL_TYPES;
	if(type == TYPE_STEEL) mass*=2.0;
}
void CParticle::simulate(double dt, double et) {
	double rho = 350;
	double vol;
	if(loc[1] < 1.0) { // in water
		// buoyancy
		vol = 3.14159*(4/3)*radius*radius*radius;
		CVec3d f(0.0, rho*9.8*vol, 0.0);
		addForce(f);
		// drag force
        CVec3d drag;
        drag = -2.0 * vel;
		addForce(drag);
	}
	

	if(dt>0.1) dt=0.1;
    vel = vel + dt*(gravity + (1.0/mass) * force );
    loc = loc + dt*vel;
	
	double elasticity = 0.9;

	if(loc[1]<0) {
        loc.set(loc[0], -elasticity*loc[1], loc[2]);
        if(vel[1]<0) vel.set(vel[0], -elasticity*vel[1], vel[2]);
    }

	double wallPosition = 2.5;
	if(loc[0]> wallPosition) { // wall collision
		double penetration = loc[0] - wallPosition;
		loc.set(loc[0] - elasticity*penetration, loc[1], loc[2]);
		if(vel[0]>0) vel.set(-elasticity*vel[0], vel[1], vel[2]);
	}
	wallPosition = -2.5;
	if(loc[0]< wallPosition) { // wall collision
		double penetration = loc[0] - wallPosition;
		loc.set(loc[0] - elasticity*penetration, loc[1], loc[2]);
		if(vel[0]<0) vel.set(-elasticity*vel[0], vel[1], vel[2]);
	}
	wallPosition = 2.5;
	if(loc[2]> wallPosition) { // wall collision
		double penetration = loc[2] - wallPosition;
		loc.set(loc[0], loc[1], loc[2] - elasticity*penetration);
		if(vel[2]>0) vel.set(vel[0], vel[1], -elasticity*vel[2]);
	}
	wallPosition = -2.5;
	if(loc[2]< wallPosition) { // wall collision
		double penetration = loc[2] - wallPosition;
		loc.set(loc[0], loc[1], loc[2] - elasticity*penetration);
		if(vel[2]<0) vel.set(vel[0], vel[1], -elasticity*vel[2]);
	}

}

void CParticle::resetForce(void) {
	this->force.set(0.0, 0.0, 0.0);
}

void CParticle::addForce(CVec3d &f) {
	this->force = this->force + f;
}