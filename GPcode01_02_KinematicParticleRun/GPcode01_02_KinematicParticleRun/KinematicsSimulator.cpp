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

    for(int i=0;i<NUMPARTS;i++)particle[i].randomInit();
}

void CKinematicSimulator::doBeforeSimulation(double dt, double currentTime) {
    
}

void CKinematicSimulator::doSimulation(double dt, double currentTime) {
    for(int i=0;i<NUMPARTS;i++){
        particle[i].simulate(dt, currentTime);
        particle[i].drawWithGL(SPHERE_DRAW);
    }
}


void CKinematicSimulator::doAfterSimulation(double dt, double currentTime) {
    
}