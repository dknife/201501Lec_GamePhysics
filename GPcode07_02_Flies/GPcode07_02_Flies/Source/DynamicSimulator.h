//
//  DynamicSimulator.h
//
//  Created by young-min kang on 4/5/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#ifndef __GPcode02_01_xcode__DynamicsSimulator__
#define __GPcode02_01_xcode__DynamicsSimulator__

#include "Simulator.h"
#include "Particle.h"

#define NUMPARTS 800

class CDynamicSimulator : public CSimulator {
	CParticle prey;
    CParticle particle[NUMPARTS];
    
public:
    CDynamicSimulator();
    
    void init(void);
    void clean(void);
    
private:
    // Actions to be performed before the simulation frame
    void doBeforeSimulation(double dt, double currentTime);
    // Simulation is done here
    void doSimulation(double dt, double currentTime);
    // Actions to be performed after the simulation frame
    void doAfterSimulation(double dt, double currentTime);
    
    // Visualization of the simulation
    void visualize(void);

	CVec3d followingForce(int i); // attraction force to prey
    CVec3d computeAttraction(int i, int j);
	void collisionHandler(int i, int j);
};

#endif /* defined(__GPcode01_01_xcode__KinematicsSimulator__) */