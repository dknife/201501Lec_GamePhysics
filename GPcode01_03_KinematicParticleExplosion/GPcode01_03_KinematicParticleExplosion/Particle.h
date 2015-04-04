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

class CParticle {
    CVec3d center;
    float radius;
    
    CVec3d currentLoc;
    CVec3d initialLoc;
    CVec3d initialVel;
    CVec3d gravity;
    
public:
	CParticle();

	void setPosition(double x, double y, double z);
	void setRadius(double r);

    void randomInit(void);
	void drawWithGL(void);
    void simulate(double dt, double eT);
};

#endif