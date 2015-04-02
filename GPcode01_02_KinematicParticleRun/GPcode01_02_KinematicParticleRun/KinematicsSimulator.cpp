//
//  KinematicsSimulator.cpp
//  GPcode01_01_xcode
//
//  Created by young-min kang on 3/27/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#include "KinematicsSimulator.h"

CKinematicSimulator::CKinematicSimulator() : CSimulator() {}


void CKinematicSimulator::init() {
	initialLoc.set(0,1,0);
	initialVel.set(0,3,0);
	gravity.set(0.0, -9.8, 0.0);
	currentLoc = initialLoc;
	particle.setPosition(currentLoc[0], currentLoc[1], currentLoc[2]);
	particle.setRadius(0.1);
}

void CKinematicSimulator::doBeforeSimulation(double dt, double currentTime) {
    
}

void CKinematicSimulator::doSimulation(double dt, double currentTime) {
    currentLoc = initialLoc 
		+ currentTime*initialVel 
		+ (0.5 * currentTime * currentTime)  * gravity ;
	
    particle.setPosition(currentLoc[0], currentLoc[1], currentLoc[2]);
    particle.drawWithGL();
}


void CKinematicSimulator::doAfterSimulation(double dt, double currentTime) {
    
}