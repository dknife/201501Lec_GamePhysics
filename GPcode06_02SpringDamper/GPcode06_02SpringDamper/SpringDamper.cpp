#include "SpringDamper.h"

CSpring::CSpring() { // constructor
	particles = NULL;
	i = j = 0;
	ks = kd = 0;
}

CVec3d CSpring::computeForce() {
	CVec3d force;
	CVec3d xi, vi;
	CVec3d xj, vj;
	CVec3d xij, vij;
	xi = particles[i].loc;
	xj = particles[j].loc;
	vi = particles[i].vel;
	vj = particles[j].vel;
	vij = vj - vi;
	xij = xj - xi;
	double l = xij.len(); // spring length
	xij.normalize(); // spring force direction : unit vector
	force = ks*(l-l0)*xij;

	CVec3d damp;
	damp = kd*vij;

	return force+damp;
}

int CSpring::getLinkedParticle(int idx) {
	if(idx==0) return i;
	else if(idx==1) return j;
	else return -1;
}

void CSpring::setSpringCoefficient(double val) { ks = val; }
void CSpring::setDampingCoefficient(double val) { kd = val; }
void CSpring::setParticles(int idx0, int idx1) { i = idx0; j = idx1; }
void CSpring::setParticleArray(CParticle *partArray) { particles = partArray; }
void CSpring::setRestLength(double val) { l0 = val; }

void CSpring::drawWithGL(void) {
	glColor3f(0.0, 0.0, 1.0);

	CVec3d xi = particles[i].loc;
	CVec3d xj = particles[j].loc;

    glBegin(GL_LINES);
		glVertex3d(xi.x, xi.y, xi.z);
		glVertex3d(xj.x, xj.y, xj.z);
	glEnd();
}
//////////////////////////
// Spring-Damper

CSpringDamperModel::CSpringDamperModel() {
	springs = NULL;
	particles = NULL;
	numSprings = numParticles = 0;
}

void CSpringDamperModel::setSpringNetwork(CSpring *sArray, int nSprings,
						CParticle *partArray, int nParticles) {
	springs = sArray;
	particles = partArray;
	numSprings = nSprings;
	numParticles = nParticles;
}

void CSpringDamperModel::simulate(double dt) {
	if(dt>0.03) dt=0.03;
	// reset forces
	for(int i=0; i<numParticles; i++) particles[i].resetForce();

	// add spring forces
	for(int i=0; i<numSprings; i++) {
		CVec3d fi, fj;
		fi = springs[i].computeForce();
		fj = -1.0*fi;
		int idx0 = springs[i].getLinkedParticle(0);
		int idx1 = springs[i].getLinkedParticle(1);
		particles[idx0].addForce(fi);
		particles[idx1].addForce(fj);
	}

	// simulate each particle
	for(int i=1; i<numParticles; i++) {
		CVec3d gravityForce(0, -9.8*particles[i].mass, 0);
		particles[i].addForce(gravityForce);
		particles[i].simulate(dt, 0);
	}
}

void CSpringDamperModel::visualize(void) {

	for(int i=0; i<numSprings; i++) {
		springs[i].drawWithGL();
	}

	for(int i=0; i<numParticles; i++) {
		particles[i].drawWithGL(SPHERE_DRAW);
	}
}
