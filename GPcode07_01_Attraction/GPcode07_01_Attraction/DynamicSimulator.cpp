//
//  DynamicSimulator.cpp
//  GPcode01_01_xcode
//
//  Created by young-min kang on 3/27/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#include "DynamicSimulator.h"
#include <stdlib.h>

CDynamicSimulator::CDynamicSimulator() : CSimulator() {}


void CDynamicSimulator::init() {

	for(int i=0;i<NUMPARTS;i++) {
        particle[i].setPosition(i, 1, 0);
        particle[i].setVelocity(0,0,0);
		particle[i].setMass(1.0);
	}
    
    
    for(int i=0;i<NUMPARTS-1;i++) {
        spring[i].setParticleArray(particle);
        spring[i].setParticles(i, i+1);
        spring[i].setSpringCoefficient(10.0);
        spring[i].setDampingCoefficient(0.1);
        spring[i].setRestLength(1.0);
    }
	
    mySpringDamper.setSpringNetwork(spring, NUMPARTS-1, particle, NUMPARTS);
}

void CDynamicSimulator::clean() {
    
}

void CDynamicSimulator::doBeforeSimulation(double dt, double currentTime) {
	// buoyancy here
}

void CDynamicSimulator::doSimulation(double dt, double currentTime) {


    mySpringDamper.simulate(dt);
	
}

void CDynamicSimulator::doAfterSimulation(double dt, double currentTime) {
    for(int i=0;i<NUMPARTS;i++) {
		particle[i].resetForce();
	}
}

void CDynamicSimulator::visualize(void) {
    for(int i=0;i<NUMPARTS;i++) {
        particle[i].drawWithGL(SPHERE_DRAW);
    }
}

void CDynamicSimulator::collisionHandler(int i, int j) {
	// collision detect
    CVec3d p1; p1 = particle[i].getPosition();
    CVec3d p2; p2 = particle[j].getPosition();
    CVec3d N ; N = p1 - p2;
	double dist = N.len();
	if(dist < particle[i].getRadius() + particle[j].getRadius()) {
		// collision detected
		N.normalize();
        CVec3d v1; v1 = particle[i].getVelocity();
        CVec3d v2; v2 = particle[j].getVelocity();
		double v1N = v1 ^ N;
		double v2N = v2 ^ N;
		double m1 = particle[i].getMass();
		double m2 = particle[j].getMass();
		// approaching ?
		if( v2N - v1N > 0 ) { // approaching
			double v1New = ( (m1-m2)*v1N + 2.0*m2*v2N ) / (m1+m2);
			double v2New = ( (m2-m1)*v2N + 2.0*m1*v1N ) / (m1+m2);
			v1 = v1 - v1N * N + v1New*N;
			v2 = v2 - v2N * N + v2New*N;
			particle[i].setVelocity(v1.x, v1.y, v1.z);
			particle[j].setVelocity(v2.x, v2.y, v2.z);
		}	
	}
}