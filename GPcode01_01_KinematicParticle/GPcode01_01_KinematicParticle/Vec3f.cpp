//
//  Vec3f.cpp
//  GPcode01_01_xcode
//
//  Created by young-min kang on 3/28/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#include "Vec3f.h"

CVec3f::CVec3f() { x=0; y=0; z=0; }
CVec3f::CVec3f(float a, float b, float c) { x=a; y=b; z=c; }
//! Copy Constructor
CVec3f::CVec3f(CVec3f &v) { x=v.x; y=v.y; z=v.z; }

/*! Sets the vector elements */
void CVec3f::set(float a, float b, float c)		{ x=a; y=b; z=c;}

/*! Stores the vector elements into the given parameters */
void CVec3f::get(float &a, float &b, float &c)	{ a=x; b=y; c=z;}

/*! Vector Addition */
CVec3f& CVec3f::operator+(const CVec3f& v) const  {
    return *(new CVec3f(x+v[0], y+v[1], z+v[2]));
}

/*! Vector Subtraction */
CVec3f& CVec3f::operator-(const CVec3f& v) const {
    return *(new CVec3f(x-v[0], y-v[1], z-v[2]));
}

/*! Scalar multiplication */
CVec3f& CVec3f::operator *(const float& s) const {
    return *(new CVec3f(x*s, y*s, z*s));
}

/*! Cross Product
	- Return: CVec3f */
CVec3f& CVec3f::operator*(const CVec3f& v) const { // cross product
    return *(new CVec3f(y*v[2]-z*v[1], -x*v[2]+z*v[0], x*v[1]-y*v[0]));
}

/*! Dot Product
	- Return: float */
float CVec3f::operator^(const CVec3f& v) const { // dot product
    return (x*v[0] + y*v[1] + z*v[2]);
}

/*! [] Operator for indexing x, y, and z */
float CVec3f::operator[](int idx) const {
    switch(idx) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: return 0;
    }
}

/*! Length: returns the length of the vector */
float	CVec3f::len(void) {	return sqrt(x*x+y*y+z*z);}
void	CVec3f::normalize(void) {
    float l=len();
    if(l==0.0f) { x=y=z=0.0f; return; }
    x/=l; y/=l; z/=l;
}

/*! Returns a new normalized vector with the same direction */
CVec3f&	CVec3f::getNormalized(void) {
    float l=len();	if(l==0) return *(new CVec3f(0,0,0));
    return *(new CVec3f(x/l, y/l, z/l));
}


/*! friend function for scalar X vector*/
CVec3f& cross(const CVec3f& v1, const CVec3f& v) {
    return *(new CVec3f(v1.y*v[2]-v1.z*v[1], -v1.x*v[2]+v1.z*v[0], v1.x*v[1]-v1.y*v[0]));
}

/*!  friend fuction for dot product of two vectors */
float dot(const CVec3f& v1, const CVec3f v2) {
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}

/*! frien operator for scalar X vector */
CVec3f& operator*(float s, const CVec3f& v) {
    return *(new CVec3f(s*v[0], s*v[1], s*v[2]));
}
