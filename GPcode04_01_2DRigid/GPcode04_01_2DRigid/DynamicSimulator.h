//
//  DynamicSimulator.h
//
//  Created by young-min kang on 4/5/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#ifndef __GPcode02_01_xcode__DynamicsSimulator__
#define __GPcode02_01_xcode__DynamicsSimulator__

#include "Simulator.h"
#include "Hovercraft.h"
#include "Vec3d.h"

class CDynamicSimulator : public CSimulator {
    CHovercraft hover;
    
    
public:
    CDynamicSimulator();

    
    void init(void);
    void clean(void);
    
    CVec3d getCameraPosition(void);
    
private:
    // Actions to be performed before the simulation frame
    void doBeforeSimulation(double dt, double currentTime);
    // Simulation is done here
    void doSimulation(double dt, double currentTime);
    // Actions to be performed after the simulation frame
    void doAfterSimulation(double dt, double currentTime);
    
    // Visualization of the simulation
    void visualize(void);
    void control(unsigned char key);

};

#endif /* defined(__GPcode01_01_xcode__KinematicsSimulator__) */
