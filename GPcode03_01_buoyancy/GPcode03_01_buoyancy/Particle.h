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

enum MaterialType {
	TYPE_WOOD,
	TYPE_STEEL,
	NUM_MATERIAL_TYPES
};

class CParticle {
public:
	int type;	
    double radius;
	double mass;
    
    CVec3d loc;
    CVec3d vel;
    CVec3d force;
    CVec3d gravity;
    
private:
    void handleCollision(void);
    void forceIntegration(double dt, double et);
    void computeBuoyancyAndDrag(void);
    
public:
	CParticle();

	void setType(int t);
	void setPosition(double x, double y, double z);
	void setRadius(double r);

	void resetForce(void);
	void addForce(CVec3d &f);

    void randomInit(void);
	void drawWithGL(int drawMode = SPHERE_DRAW);
    void simulate(double dt, double eT);
};

#endif