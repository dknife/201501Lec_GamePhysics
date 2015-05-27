//
//  SpringDamper.cpp
//  GPcode06_01Xcode
//
//  Created by young-min kang on 5/20/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#include "SpringDamper.h"


CSpring::CSpring() {
    particles = NULL;
    i  = j  = 0;
    ks = kd = 0;
}

CVec3d CSpring::computeForce() {
    CVec3d force;
    CVec3d xi;
    CVec3d xj;
    CVec3d xij;
    int i = getLinkedParticle(0);
    int j = getLinkedParticle(1);
    xi = particles[i].loc;
    xj = particles[j].loc;
    xij = xj - xi;
    double l = xij.len();
    xij.normalize();
    force = ks*(l - l0)*xij;
    return force;
}
int CSpring::getLinkedParticle(int idx) {
    if(idx==0) return i;
    if(idx==1) return j;
    else return -1;
}
    
void CSpring::setSpringCoefficient(double val) { ks = val; }
void CSpring::setDampingCoefficient(double val){ kd = val; }
void CSpring::setParticles(int idx0, int idx1) { i=idx0; j=idx1; }
void CSpring::setParticleArray(CParticle *partArray) { particles = partArray; }
void CSpring::setRestLength(double val) { l0 = val; }

CSpringDamperModel::CSpringDamperModel() {
    springs = NULL;
    particles = NULL;
    numSprings = 0;
    numParticles = 0;
}

void CSpringDamperModel::setSpringNetwork(CSpring *springArray, int nSprings, CParticle *particleArray, int nParticles) {
    springs = springArray;
    particles = particleArray;
    numSprings = nSprings;
    numParticles = nParticles;
};

void CSpringDamperModel::simulate(double dt) {
    for(int i=0;i<numParticles;i++) {
        particles[i].resetForce();
    }
    for (int i=0; i<numSprings; i++) {
        CVec3d fi,fj;
        fi = springs[i].computeForce();
        fj = -1.0*fi;
        int idx0 = springs[i].getLinkedParticle(0);
        int idx1 = springs[i].getLinkedParticle(1);
        particles[idx0].addForce(fi);
        particles[idx1].addForce(fj);
    }
    for(int i=1;i<numParticles;i++) {
        CVec3d gravityForce(0,-9.8 * particles[i].mass ,0);
        particles[i].addForce(gravityForce);
        particles[i].simulate(dt, 0);
    }
}