//
//  SpringDamper.h
//  GPcode06_01Xcode
//
//  Created by young-min kang on 5/20/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#ifndef __GPcode06_01Xcode__SpringDamper__
#define __GPcode06_01Xcode__SpringDamper__

#include "Particle.h"
#include "Vec3d.h"
#include <stdio.h>

class CSpring {
    CParticle *particles;
    int i;
    int j;
    double ks;
    double kd;
    double l0; // rest length;
public:
    CSpring() ;
    void setParticleArray(CParticle *partArray);

    CVec3d computeForce();
    int getLinkedParticle(int idx);
    
    void setSpringCoefficient(double val);
    void setDampingCoefficient(double val);
    void setParticles(int idx0, int idx1);
    void setRestLength(double val);
};

class CSpringDamperModel {
    CSpring *springs;
    CParticle *particles;
    int numSprings;
    int numParticles;
    
public:
    CSpringDamperModel();
    
    void setSpringNetwork(CSpring *springArray, int nSprings, CParticle *particleArray, int nParticles);
    
    void simulate(double dt);
    
};
#endif /* defined(__GPcode06_01Xcode__SpringDamper__) */
