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
    
/*
    balls[0].setPosition( 10, BALL_RADIUS, -TABLE_H/2.0 + BALL_RADIUS + 300); balls[0].setColor(1.0, 1.0, 1.0);
    balls[1].setPosition(0, BALL_RADIUS, -TABLE_H/2.0 + BALL_RADIUS); balls[1].setColor(1.0, 0.0, 0.0);
    balls[2].setPosition( 300, BALL_RADIUS,-3.0*TABLE_H/8.0); balls[2].setColor(1.0, 1.0, 0.0);
    balls[3].setPosition( 300, BALL_RADIUS,-3.0*TABLE_H/8.0-BALL_RADIUS*2.5); balls[3].setColor(1.0, 0.0, 0.0);
*/
    
    balls[0].setPosition( TABLE_W/20.0, BALL_RADIUS, 3.0*TABLE_H/8.0); balls[0].setColor(1.0, 1.0, 1.0);
    balls[1].setPosition(-TABLE_W/20.0, BALL_RADIUS, 3.0*TABLE_H/8.0); balls[1].setColor(1.0, 0.0, 0.0);
    balls[2].setPosition( 0, BALL_RADIUS,-3.0*TABLE_H/8.0); balls[2].setColor(1.0, 1.0, 0.0);
    balls[3].setPosition( 0, BALL_RADIUS,-2.0*TABLE_H/8.0); balls[3].setColor(1.0, 0.0, 0.0);
 
    
    aim.set(1.0, 0.0, 0.0);
    shotSpin = topSpin = 0.0;
    shotPower = 1.0;
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
        
        if(turn==0) glColor3f(1.0, 1.0, 1.0);
        else glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
        for(int i=0;i<100;i++) {
            double angle = 2.0*3.141592*i/100.0;
            glVertex3d(TABLE_W*4.0/5.0 + 300.0*cos(angle), 0, 300.0*sin(angle));
        }
        glEnd();
        
        
        
        double powerX =  TABLE_W/2.0 + 30.0;
        double powerZ = -TABLE_H*2.0/10.0;
        double powerW = 750.0;
        double powerH = 20.0;
        glColor3f(1.0, 1.0, 0.0);
        glPointSize(10);
        glBegin(GL_QUADS);
        glVertex3d(powerX, 0, powerZ);
        glVertex3d(powerX, 0, powerZ+powerH);
        glVertex3d(powerX+powerW, 0, powerZ+powerH);
        glVertex3d(powerX+powerW, 0, powerZ);
        glEnd();
        
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3d(powerX, 10, powerZ);
        glVertex3d(powerX, 10, powerZ+powerH);
        glVertex3d(powerX+powerW*shotPower, 10, powerZ+powerH);
        glVertex3d(powerX+powerW*shotPower, 10, powerZ);
        glEnd();
      
        glColor3f(1.0, 0.0, 0.0);
        glPointSize(4);
        glBegin(GL_POINTS);
        glVertex3d(TABLE_W*4.0/5.0 + 0.95*300.0*shotSpin, 10, -0.95*300*topSpin);
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
        float v1Mag = v1.len();
        float v2Mag = v2.len();
        
		double v1N = v1 ^ N; // velocity along the line of action
		double v2N = v2 ^ N; // velocity along the line of action
		double m1 = balls[i].getMass();
		double m2 = balls[j].getMass();
        double s1 = balls[i].getSpin();
        double s2 = balls[j].getSpin();
		// approaching ?
		if( v1N-v2N < 0 ) { // approaching
            double vr = v1N - v2N;
            double s2add = 0.5*s1*(-vr/(-vr+v1Mag));
            double s1add = 0.5*s2*(-vr/(-vr+v2Mag));
            s1 += s1add;
            s2 += s2add;
            
            balls[i].setSpin(s1);
            balls[j].setSpin(s2);
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
    double drag = 0.1;
    for(int i=0;i<NUMBALLS;i++) {
        vel = balls[i].getVelocity();
        dragForce = -drag*vel;
        balls[i].addForce(dragForce);

        CVec3d roll;
        roll = 200.0*balls[i].getRoll();
        balls[i].addForce(roll);
    }
}
void CDynamicSimulator::cushion(void) {

    // collision detect
    for(int i=0;i<NUMBALLS; i++) {
        CVec3d pos; pos = balls[i].getPosition();
        CVec3d vel; vel = balls[i].getVelocity();
        CVec3d N;
        double r = balls[i].getRadius();
        double pene = -1.0;
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
        else {
            continue;
        }
       
        
        double vDotN = vel^N;
        double s = balls[i].getSpin();
        CVec3d spin(0,s,0);
        CVec3d vTangent;
        CVec3d vTangentAdd;
        vTangent = vel - vDotN*N;
        vTangentAdd = 0.4*vDotN*(N*spin);
        
        
        
        if (vDotN<0.0) { // penetrating
            vTangent = vTangent + vTangentAdd;
            vel = vTangent - 0.9*vDotN*N;
            balls[i].setVelocity(vel.x, vel.y, vel.z);
        }
        pos = pos + (2.0*pene)*N;
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
void CDynamicSimulator::increaseShotSpin(double spinAdd) {
    shotSpin+=spinAdd;
    if(shotSpin>1.0) shotSpin=1.0;
    if(shotSpin<-1.0) shotSpin=-1.0;
    double l = shotSpin*shotSpin+topSpin*topSpin;
    if(l>1.0) {
        double sqrL = sqrt(l);
        shotSpin /= sqrL;
        topSpin /= sqrL;
    }
}

void CDynamicSimulator::increaseTopSpin(double spinAdd) {
    topSpin+=spinAdd;
    if(topSpin>1.0) shotSpin=1.0;
    if(topSpin<-1.0) shotSpin=-1.0;
    double l = shotSpin*shotSpin+topSpin*topSpin;
    if(l>1.0) {
        double sqrL = sqrt(l);
        shotSpin /= sqrL;
        topSpin /= sqrL;
    }
}

void CDynamicSimulator::increaseShotPower(double pAdd) {
    shotPower+=pAdd;
    if(shotPower>1.0) shotPower=1.0;
    if(shotPower<0.0) shotPower=0.0;
}

void CDynamicSimulator::shot(void) {
    balls[turn*2].setVelocity(5000*shotPower*aim.x, 0.0, 5000*shotPower*aim.z);
    balls[turn*2].setSpin(shotSpin);
    
    double localRollX = topSpin;
    double localRollZ = 0.0; //shotSpin*topSpin;
    double rollX = aim.x * localRollX - aim.z * localRollZ;
    double rollZ = aim.z * localRollX + aim.x * localRollZ;
    balls[turn*2].setRoll(rollX, rollZ);
    mode = SIMULATING;
}

void CDynamicSimulator::turnOver(void) {
    for(int i=0;i<NUMBALLS;i++) {
        balls[i].setVelocity(0.0, 0.0, 0.0);
        balls[i].setSpin(0.0);
        balls[i].setRoll(0.0, 0.0);
    }
    turn = turn==PLAYER1?PLAYER2:PLAYER1;
    mode = TURNOVER;
}