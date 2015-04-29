//
//  Hovercraft.cpp
//  GPcode0401_Xcode
//
//  Created by young-min kang on 4/22/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//


#include "Hovercraft.h"
#include <math.h>


CHovercraft::CHovercraft() :
mass(1.0), inertia(0.1), angle(0.0), aVel(0.0), torque(0.0) {
    loc.set(0.0, 0.0, 0.0);
    vel.set(0.0, 0.0, 0.0);
    force.set(0.0, 0.0, 0.0);
    
    r[LEFT_THRUST].set(-1.0, -1.0, 0.0);
    r[RIGHT_THRUST].set(1.0, -1.0, 0.0);
    r[LEFT_SIDE].set(-1.0, 1.0, 0.0);
    r[RIGHT_SIDE].set(1.0, 1.0, 0.0);
    r[FRONT_BRAKE].set(0.0, 1.5, 0.0);
    
    fLocal[LEFT_THRUST].set( 0.0, 1.0, 0.0);
    fLocal[RIGHT_THRUST].set(0.0, 1.0, 0.0);
    fLocal[LEFT_SIDE].set(   1.0, 0.0, 0.0);
    fLocal[RIGHT_SIDE].set( -1.0, 0.0, 0.0);
    fLocal[FRONT_BRAKE].set( 0.0,-1.0, 0.0);
    
    for (int i=0; i<NUMBER_OF_ENGINES; i++) on[i] = false;
}

CHovercraft::~CHovercraft() {
    
}

void CHovercraft::simulate(double dt) {
    force.set(0.0, 0.0, 0.0);
    torque = 0.0;
    
    // rigid body
    CVec3d fWorld;
    CVec3d torqueVec;
    for (int i=0; i<NUMBER_OF_ENGINES; i++) {
        if(on[i]) {
            fWorld = localVectorToWorldVector(fLocal[i]);
            force = force + fWorld;
            torqueVec = r[i]*fLocal[i];
            torque += torqueVec[2];
        }
    }
    // drag force
    double kd = 0.5;
    force  = force -kd*vel;
    torque += -kd*aVel;
    vel = vel + (dt/mass)*force;
    loc = loc + dt * vel;
    
    aVel = aVel + (dt/inertia)*torque;
    angle = angle + dt * aVel;
    
}

CVec3d CHovercraft::localVectorToWorldVector(const CVec3d &lV) {
    double c = cos(angle);
    double s = sin(angle);
    
    CVec3d res(c*lV[0]-s*lV[1], s*lV[0]+c*lV[1], 0.0);
    return res;
}

void CHovercraft::switchEngine(int engineNumber, bool switch_state) {
    if (engineNumber>-1 && engineNumber < NUMBER_OF_ENGINES) {
        on[engineNumber] = switch_state;
    }
}

bool CHovercraft::isEngineOn(int engineNumber) {
    return on[engineNumber];
}

void CHovercraft::draw() {
    
    glPushMatrix();
    
    glTranslatef(loc[0], loc[1], loc[2]);
    glRotatef(angle*180.0/3.14, 0.0, 0.0, 1.0);
    
    glColor3f(0.5,0.5,1.0);
    glBegin(GL_POLYGON);
    for(int i=0; i<NUMBER_OF_ENGINES; i++) {
        glVertex3d(r[i][0], r[i][1], r[i][2]);
    }
    glEnd();
    
    
    for(int i=0; i<NUMBER_OF_ENGINES; i++) {
        
        if(!on[i]) continue;
        
        glPushMatrix();
        glTranslatef(r[i][0], r[i][1], r[i][2]);
        switch(i) {
            case RIGHT_SIDE: glRotatef(90, 0.0, 0.0, 1.0); break;
            case LEFT_SIDE: glRotatef(270, 0.0, 0.0, 1.0); break;
            case FRONT_BRAKE: glRotatef(180, 0.0, 0.0, 1.0); break;
        }
        glColor3f(1.0, 0.3, 0.2);
        glBegin(GL_POLYGON);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(-0.2, -0.5, 0.0);
        glVertex3d(0.2, -0.5, 0.0);
        glEnd();
        glPopMatrix();
    }
    
    glPopMatrix();
}

void CHovercraft::setLocation(CVec3d location) {
    loc = location;
}

CVec3d CHovercraft::getLocation(void) {
    return loc;
}