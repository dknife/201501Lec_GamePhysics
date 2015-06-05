//
//  Hovercraft.h
//  GPcode0401_Xcode
//
//  Created by young-min kang on 4/22/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#ifndef __GPcode0401_Xcode__Hovercraft__
#define __GPcode0401_Xcode__Hovercraft__

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Vec3d.h"

enum ENGINE_NUMBER {
    LEFT_THRUST,
    RIGHT_THRUST,
    RIGHT_SIDE,
    FRONT_BRAKE,
    LEFT_SIDE,
    NUMBER_OF_ENGINES
};


class CHovercraft {
    
    double mass;
    double inertia;
    
    CVec3d loc;
    CVec3d vel;
    CVec3d force;
    
    double angle;
    double aVel;
    double torque;
    
    CVec3d r[NUMBER_OF_ENGINES];
    CVec3d fLocal[NUMBER_OF_ENGINES];
    bool   on[NUMBER_OF_ENGINES];
    
    CVec3d localVectorToWorldVector(const CVec3d &lV);
    

public:
    CHovercraft();
    ~CHovercraft();
    
    
    
    void draw(void);
    void switchEngine(int engineNumber, bool switch_state);
    bool isEngineOn(int engineNumber);
    void simulate(double dt);
    void setLocation(CVec3d location);
    CVec3d getLocation(void);
};


#endif /* defined(__GPcode0401_Xcode__Hovercraft__) */
