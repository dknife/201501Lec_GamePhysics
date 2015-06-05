//
//  Vec3d.cpp
//  GPcode01_01_xcode
//
//  Created by young-min kang on 3/28/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#include "Vec3d.h"

CVec3d::CVec3d() { x=0; y=0; z=0; }
CVec3d::CVec3d(double a, double b, double c) { x=a; y=b; z=c; }
//! Copy Constructor
CVec3d::CVec3d(CVec3d &v) { this->x=v.x; this->y=v.y; this->z=v.z; }

CVec3d::~CVec3d() {}

/*! Sets the vector elements */
void CVec3d::set(double a, double b, double c)		{ x=a; y=b; z=c;}

/*! Stores the vector elements into the given parameters */
void CVec3d::get(double &a, double &b, double &c)	{ a=x; b=y; c=z;}

/*! Vector Addition */
CVec3d CVec3d::operator+(const CVec3d& v) const  {
    CVec3d res(x+v[0], y+v[1], z+v[2]);
    return res;
}

/*! Vector Subtraction */
CVec3d CVec3d::operator-(const CVec3d& v) const {
    CVec3d res(x-v[0], y-v[1], z-v[2]);
    return res;
}

/*! Scalar multiplication */
CVec3d CVec3d::operator *(const double& s) const {
    CVec3d res(x*s, y*s, z*s);
    return res;
}

/*! Cross Product
	- Return: CVec3d */
CVec3d CVec3d::operator*(const CVec3d& v) const { // cross product
    CVec3d res(y*v[2]-z*v[1], -x*v[2]+z*v[0], x*v[1]-y*v[0]);
    return res;
}

/*! Dot Product
	- Return: double */
double CVec3d::operator^(const CVec3d& v) const { // dot product
    return (x*v[0] + y*v[1] + z*v[2]);
}

/*! [] Operator for indexing x, y, and z */
double CVec3d::operator[](int idx) const {
    switch(idx) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: return 0;
    }
}

/*! Length: returns the length of the vector */
double	CVec3d::len(void) {	return sqrt(x*x+y*y+z*z);}
void	CVec3d::normalize(void) {
    double l=len();
    if(l==0.0f) { x=y=z=0.0f; return; }
    x/=l; y/=l; z/=l;
}

/*! Returns a new normalized vector with the same direction */
CVec3d	CVec3d::getNormalized(void) {
    double l=len();	if(l==0) return *(new CVec3d(0,0,0));
    CVec3d res(x/l, y/l, z/l);
    return res;
}


/*! friend function for scalar X vector*/
CVec3d cross(const CVec3d& v1, const CVec3d& v) {
    CVec3d res(v1.y*v[2]-v1.z*v[1], -v1.x*v[2]+v1.z*v[0], v1.x*v[1]-v1.y*v[0]);
    return res;
}

/*!  friend fuction for dot product of two vectors */
double dot(const CVec3d& v1, const CVec3d v2) {
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}

/*! frien operator for scalar X vector */
CVec3d operator*(double s, const CVec3d& v) {
    CVec3d res(s*v[0], s*v[1], s*v[2]);
    return res;
}