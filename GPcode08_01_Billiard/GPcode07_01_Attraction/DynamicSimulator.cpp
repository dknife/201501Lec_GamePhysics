//
//  DynamicSimulator.cpp
//  GPcode01_01_xcode
//
//  Created by young-min kang on 3/27/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#include "DynamicSimulator.h"
#include <stdlib.h>
#include <math.h>

double rand(double min, double max) {
    return (max-min)*(double(rand()%10001)/10000.0)+min;
}

CDynamicSimulator::CDynamicSimulator() : CSimulator() {}


void CDynamicSimulator::init() {
    
    turn = PLAYER1;
    mode = READY;
    
    for(int i=0;i<NUMBALLS;i++) {
        balls[i].setRadius(BALL_RADIUS);
        balls[i].setMass(0.16);
        balls[i].setVelocity(0.0, 0.0, 0.0);
    }
    balls[0].setPosition( TABLE_W/20.0, BALL_RADIUS, 3.0*TABLE_H/8.0); balls[0].setColor(1.0, 1.0, 1.0);
    balls[1].setPosition(-TABLE_W/20.0, BALL_RADIUS, 3.0*TABLE_H/8.0); balls[1].setColor(1.0, 0.0, 0.0);
    balls[2].setPosition( 0, BALL_RADIUS,-3.0*TABLE_H/8.0); balls[2].setColor(1.0, 1.0, 0.0);
    balls[3].setPosition( 0, BALL_RADIUS,-2.0*TABLE_H/8.0); balls[3].setColor(1.0, 0.0, 0.0);

    
    
    aim.set(1.0, 0.0, 0.0);
    
}

void CDynamicSimulator::clean() {
    
}

void CDynamicSimulator::doBeforeSimulation(double dt, double currentTime) {
	// buoyancy here
}

void CDynamicSimulator::doSimulation(double dt, double currentTime) {
    
    if(dt>0.01)dt=0.01; // maximum dt
    
    if(mode!=SIMULATING) return;
    
    floorDrag();
    
    for (int i=0; i<NUMBALLS; i++) {
        balls[i].simulate(dt, currentTime);
    }
    
    cushion();
    
    
    for (int i=0; i<NUMBALLS; i++) {
        for (int j=i+1; j<NUMBALLS; j++) {
            collisionHandler(i, j);
        }
    }
}

void CDynamicSimulator::doAfterSimulation(double dt, double currentTime) {
    for(int i=0;i<NUMBALLS;i++) {
		balls[i].resetForce();
	}
}

void CDynamicSimulator::visualize(void) {
    // Draw Table
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-TABLE_W/2.0, 0.0,-TABLE_H/2.0);
    glVertex3f(-TABLE_W/2.0, 0.0, TABLE_H/2.0);
    glVertex3f( TABLE_W/2.0, 0.0, TABLE_H/2.0);
    glVertex3f( TABLE_W/2.0, 0.0,-TABLE_H/2.0);
    glEnd();
    for(int i=0;i<NUMBALLS;i++) {
        balls[i].drawWithGL(SPHERE_DRAW);
    }
    
    if (mode == AIMING) {
        CVec3d pos; pos = balls[turn*2].getPosition();
        glBegin(GL_LINES);
        glVertex3f(pos.x, pos.y, pos.z);
        glVertex3f(pos.x+aim.x*2000.0, pos.y+aim.y*2000.0, pos.z+aim.z*2000.0);
        glEnd();
    }
}



void CDynamicSimulator::collisionHandler(int i, int j) {
	// collision detect
    CVec3d p1; p1 = balls[i].getPosition();
    CVec3d p2; p2 = balls[j].getPosition();
    CVec3d N ; N = p1 - p2;
	double dist = N.len();
    double e = 0.9;
	if(dist < balls[i].getRadius() + balls[j].getRadius()) {
        
        double penetration = balls[i].getRadius() + balls[j].getRadius() - dist;
        
		// collision detected
		N.normalize();
        CVec3d v1; v1 = balls[i].getVelocity();
        CVec3d v2; v2 = balls[j].getVelocity();
		double v1N = v1 ^ N; // velocity along the line of action
		double v2N = v2 ^ N; // velocity along the line of action
		double m1 = balls[i].getMass();
		double m2 = balls[j].getMass();
		// approaching ?
		if( v1N-v2N < 0 ) { // approaching
            double vr = v1N - v2N;
            double J = -vr*(e+1.0)/(1.0/m1 + 1.0/m2);
			double v1New = v1N + J/m1;
            double v2New = v2N - J/m2;
			v1 = v1 - v1N * N + v1New*N;
			v2 = v2 - v2N * N + v2New*N;
			balls[i].setVelocity(v1.x, v1.y, v1.z);
			balls[j].setVelocity(v2.x, v2.y, v2.z);
		}
        p1 = p1 + 0.5*((1.0+e)*penetration)*N;
        p2 = p2 - 0.5*((1.0+e)*penetration)*N;
        balls[i].setPosition(p1.x, p1.y, p1.z);
        balls[j].setPosition(p2.x, p2.y, p2.z);
	}
}

void CDynamicSimulator::floorDrag(void) {
    CVec3d vel, dragForce;
    double drag = 0.05;
    for(int i=0;i<NUMBALLS;i++) {
        vel = balls[i].getVelocity();
        dragForce = -drag*vel;
        balls[i].addForce(dragForce);
    }
}
void CDynamicSimulator::cushion(void) {

    // collision detect
    for(int i=0;i<NUMBALLS; i++) {
        CVec3d pos; pos = balls[i].getPosition();
        CVec3d vel; vel = balls[i].getVelocity();
        CVec3d N;
        double r = balls[i].getRadius();
        double pene = 0.0;
        if(pos.x + r > TABLE_W/2.0) {
            pene = pos.x + r - TABLE_W/2.0;
            N.set(-1.0, 0, 0);
        }
        else if(pos.x - r < -TABLE_W/2.0) {
            pene = -TABLE_W/2.0 - pos.x + r;
            N.set(1.0,0.0,0.0);
        }
        else if(pos.z + r > TABLE_H/2.0) {
            pene = pos.z + r - TABLE_H/2.0;
            N.set(0.0, 0.0, -1.0);
        }
        else if(pos.z - r < -TABLE_H/2.0) {
            pene = -TABLE_H/2.0 - pos.z + r;
            N.set(0.0, 0.0, 1.0);
        }
    
        double vN = vel^N;
        if (vN<0.0) { // penetrating
            vel = vel - (2.0 * vN)*N;
        }
        pos = pos + (2.0*pene)*N;
        balls[i].setVelocity(vel.x, vel.y, vel.z);
        balls[i].setPosition(pos.x, pos.y, pos.z);
    }
    
}

MODE CDynamicSimulator::getMode(void)   { return mode; }
void CDynamicSimulator::setMode(MODE m) { mode = m; }

void CDynamicSimulator::rotateAim(double angle) {
    aimAngle+=angle;
    if(aimAngle>3.141592*2.0) aimAngle-=3.141592*2.0;
    aim.set(cos(aimAngle), 0.0, sin(aimAngle));
}

void CDynamicSimulator::shot(void) {
    balls[turn*2].setVelocity(5000*aim.x, 0.0, 5000*aim.z);
    mode = SIMULATING;
}

void CDynamicSimulator::turnOver(void) {
    for(int i=0;i<NUMBALLS;i++) balls[i].setVelocity(0.0, 0.0, 0.0);
    turn = turn==PLAYER1?PLAYER2:PLAYER1;
    mode = TURNOVER;
}