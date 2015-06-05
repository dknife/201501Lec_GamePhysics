#ifndef _GPSpringDamper2015_1_hhh_
#define _GPSpringDamper2015_1_hhh_

#include "Particle.h"
#include "Vec3d.h"
#include <stdio.h>

class CSpring { // one spring
	CParticle *particles; // particle array
	int i;
	int j;

	// spring properties
	double ks; // spring coefficient
	double kd; // damping coefficient
	double l0; // rest length
public:
	CSpring(); // constructor
	void setParticleArray(CParticle *partArray);

	CVec3d computeForce();
	int getLinkedParticle(int idx); // idx=0 -> return i, idx=1 -> return j
	void setSpringCoefficient(double val);
	void setDampingCoefficient(double val);
	void setParticles(int idx0, int idx1);
	void setRestLength(double val);

	void drawWithGL(void);
};

class CSpringDamperModel {  // spring-particle network
	CSpring *springs;
	CParticle *particles;
	int numSprings;
	int numParticles;

public:
	CSpringDamperModel();
	void setSpringNetwork(CSpring *springArray, int nSprings,
						CParticle *particleArray, int nParticles);
	void simulate(double dt);
	void visualize(void);
};


#endif