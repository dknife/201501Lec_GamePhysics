//
//  KinematicsSimulator.h
//
//  Created by young-min kang on 3/27/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#ifndef __GPcode01_01_xcode__KinematicsSimulator__
#define __GPcode01_01_xcode__KinematicsSimulator__

#include "Simulator.h"
#include "Particle.h"
class CKinematicSimulator : public CSimulator {
    CParticle particle;
    CVec3d currentLoc;
	CVec3d initialLoc;
	CVec3d initialVel;
	CVec3d gravity;
    
public:
    CKinematicSimulator();
    
    void init(void);
    
private:
    // Actions to be performed before the simulation frame
    void doBeforeSimulation(double dt, double currentTime);
    // Simulation is done here
    void doSimulation(double dt, double currentTime);
    // Actions to be performed after the simulation frame
    void doAfterSimulation(double dt, double currentTime);
};

#endif /* defined(__GPcode01_01_xcode__KinematicsSimulator__) */
