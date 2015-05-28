//
//  DynamicSimulator.cpp
//  GPcode01_01_xcode
//
//  Created by young-min kang on 3/27/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#include "DynamicSimulator.h"
#include <stdlib.h>
#include <math.h>

double rand(double min, double max) {
    return (max-min)*(double(rand()%10001)/10000.0)+min;
}

CDynamicSimulator::CDynamicSimulator() : CSimulator() {}


void CDynamicSimulator::init() {

	for(int i=0;i<NUMPARTS;i++) {
        particle[i].setPosition(rand(-7,7), rand(-7,7), rand(-7,7));
        particle[i].setVelocity(rand(-1,1), rand(-1,1), rand(-1,1));
		particle[i].setMass(rand(0.01,0.05));
	}
    
}

void CDynamicSimulator::clean() {
    
}

void CDynamicSimulator::doBeforeSimulation(double dt, double currentTime) {
	// buoyancy here
}

void CDynamicSimulator::doSimulation(double dt, double currentTime) {
    
    if(dt>0.01)dt=0.01; // maximum dt
    
    CVec3d forcei;
    CVec3d forcej;
    
	for (int i=0; i<NUMPARTS; i++) {
        for (int j=i+1; j<NUMPARTS; j++) {
            forcei = computeAttraction(i, j);
            forcej = -1.0*forcei;
            particle[i].addForce(forcei);
            particle[j].addForce(forcej);
        }
    }
    
    for (int i=0; i<NUMPARTS; i++) {
        particle[i].simulate(dt, currentTime);
    }
    
    for (int i=0; i<NUMPARTS; i++) {
        for (int j=i+1; j<NUMPARTS; j++) {
            collisionHandler(i, j);
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
        particle[i].drawWithGL(POINT_DRAW);
    }
}

CVec3d CDynamicSimulator::computeAttraction(int i, int j) {
    // collision detect
    CVec3d xi; xi = particle[i].getPosition();
    CVec3d xj; xj = particle[j].getPosition();
    double minDist = particle[i].getRadius()+particle[j].getRadius();
    CVec3d xij; xij = xj-xi;
    double dist = xij.len();
    if(dist<minDist) dist=minDist;
    
    xij.normalize();
    double mi = particle[i].getMass();
    double mj = particle[j].getMass();
    
    double G = 120;
    CVec3d force;
    force = (G*mi*mj/(dist*dist))*xij;
    return force;
    
}

void CDynamicSimulator::collisionHandler(int i, int j) {
	// collision detect
    CVec3d p1; p1 = particle[i].getPosition();
    CVec3d p2; p2 = particle[j].getPosition();
    CVec3d N ; N = p1 - p2;
	double dist = N.len();
    double e = 0.0;
	if(dist < particle[i].getRadius() + particle[j].getRadius()) {
        
        double penetration = particle[i].getRadius() + particle[j].getRadius() - dist;
        
		// collision detected
		N.normalize();
        CVec3d v1; v1 = particle[i].getVelocity();
        CVec3d v2; v2 = particle[j].getVelocity();
		double v1N = v1 ^ N; // velocity along the line of action
		double v2N = v2 ^ N; // velocity along the line of action
		double m1 = particle[i].getMass();
		double m2 = particle[j].getMass();
		// approaching ?
		if( v1N-v2N < 0 ) { // approaching
            double vr = v1N - v2N;
            double J = -vr*(e+1.0)/(1.0/m1 + 1.0/m2);
			double v1New = v1N + J/m1;
            double v2New = v2N - J/m2;
			v1 = v1 - v1N * N + v1New*N;
			v2 = v2 - v2N * N + v2New*N;
			particle[i].setVelocity(v1.x, v1.y, v1.z);
			particle[j].setVelocity(v2.x, v2.y, v2.z);
		}
        p1 = p1 + 0.5*((1.0+e)*penetration)*N;
        p2 = p2 - 0.5*((1.0+e)*penetration)*N;
        particle[i].setPosition(p1.x, p1.y, p1.z);
        particle[j].setPosition(p2.x, p2.y, p2.z);
	}
}