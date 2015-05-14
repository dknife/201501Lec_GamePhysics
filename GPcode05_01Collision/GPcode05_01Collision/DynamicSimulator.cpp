//
//  DynamicSimulator.cpp
//  GPcode01_01_xcode
//
//  Created by young-min kang on 3/27/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#include "DynamicSimulator.h"

CDynamicSimulator::CDynamicSimulator() : CSimulator() {}


void CDynamicSimulator::init() {

	for(int i=0;i<NUMPARTS;i++) {
		particle[i].setPosition((i%2)?5:-5,0,i/2);
		particle[i].setVelocity((i%2)?-5:5,0,(rand()%1000)/1000.0);
		particle[i].setMass(2.0*(rand()%1000)/1000.0 + 2.0);
	}
	
}

void CDynamicSimulator::clean() {
    
}

void CDynamicSimulator::doBeforeSimulation(double dt, double currentTime) {
	// buoyancy here
}

void CDynamicSimulator::doSimulation(double dt, double currentTime) {


	for(int i=0;i<NUMPARTS;i++)
        particle[i].simulate(dt, currentTime);

	for(int i=0;i<NUMPARTS;i++) {
		for(int j=i+1;j<NUMPARTS;j++) {
			collisionHandler(i,j);
		}
	}
	
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
	CVec3d p1 = particle[i].getPosition();
	CVec3d p2 = particle[j].getPosition();
	CVec3d N = p1 - p2;
	double dist = N.len();
	if(dist < particle[i].getRadius() + particle[j].getRadius()) {
		// collision detected
		N.normalize();
		CVec3d v1 = particle[i].getVelocity();
		CVec3d v2 = particle[j].getVelocity();
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