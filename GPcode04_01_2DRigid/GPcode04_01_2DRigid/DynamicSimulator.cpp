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

    
}

void CDynamicSimulator::clean() {
    
}

void CDynamicSimulator::doBeforeSimulation(double dt, double currentTime) {

}

void CDynamicSimulator::doSimulation(double dt, double currentTime) {

    hover.simulate(dt);
}

void CDynamicSimulator::doAfterSimulation(double dt, double currentTime) {

}

void CDynamicSimulator::visualize(void) {
    
    hover.draw();
    
}

void CDynamicSimulator::control(unsigned char key) {
    int engineNumber = (int) (key-'1');
    hover.switchEngine(engineNumber, hover.isEngineOn(engineNumber)?false:true);
}

CVec3d CDynamicSimulator::getCameraPosition(void) {
    CVec3d loc;
    loc = hover.getLocation();
    return loc;
}