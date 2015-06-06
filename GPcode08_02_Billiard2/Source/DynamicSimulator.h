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

#define NUMBALLS 4
#define TABLE_W 1420
#define TABLE_H 2840
#define BALL_RADIUS 40.75

typedef enum MODE {
    READY,
    AIMING,
    SIMULATING,
    TURNOVER
} gameMode;

enum TURNS {
    PLAYER1,
    PLAYER2,
    NUMPLAYERS
};

class CDynamicSimulator : public CSimulator {
    CParticle balls[NUMBALLS];
    TURNS turn;
    MODE mode;
    CVec3d aim;
    float aimAngle;
    float shotSpin;
    float shotPower;
    
public:
    CDynamicSimulator();
    
    void init(void);
    void clean(void);
    
    MODE getMode(void);
    void setMode(MODE m);
    void rotateAim(double angle);
    void increaseShotSpin(double spinAdd);
    void increaseShotPower(double powerAdd);
    void shot(void);
    void turnOver(void);
    
    
private:
    // Actions to be performed before the simulation frame
    void doBeforeSimulation(double dt, double currentTime);
    // Simulation is done here
    void doSimulation(double dt, double currentTime);
    // Actions to be performed after the simulation frame
    void doAfterSimulation(double dt, double currentTime);
    
    // Visualization of the simulation
    void visualize(void);

    CVec3d computeAttraction(int i, int j);
	void collisionHandler(int i, int j);
    void floorDrag(void);
    void cushion(void);
    
};

#endif /* defined(__GPcode01_01_xcode__KinematicsSimulator__) */