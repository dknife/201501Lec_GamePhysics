#ifndef _TONGMYONG_YMKANG_KINEMATIC_PARTICLE_2015_
#define _TONGMYONG_YMKANG_KINEMATIC_PARTICLE_2015_

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

#include "Vec3d.h"

enum DrawMode {
    POINT_DRAW,
    SPHERE_DRAW
};

class CParticle {
public:
	int type;	
    double radius;
	double mass;
    
    CVec3d loc, vel, force, gravity;
    CVec3d color;
    
private:
    void forceIntegration(double dt, double et);
    
public:
	CParticle();

	void setPosition(double x, double y, double z);
	void setVelocity(double vx, double vy, double vz);
	void setMass(double m);
    void setRadius(double r);
    void setColor(double r, double g, double b);
    
	CVec3d getPosition();
	CVec3d getVelocity();
	double getMass();
	double getRadius();
	

	void resetForce(void);
	void addForce(CVec3d &f);

	void drawWithGL(int drawMode = SPHERE_DRAW);
    void simulate(double dt, double eT);
};

#endif