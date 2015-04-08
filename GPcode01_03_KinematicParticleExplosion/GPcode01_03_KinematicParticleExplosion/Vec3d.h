//
//  Vec3d.h
//  GPcode01_01_xcode
//
//  Created by young-min kang on 3/28/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#ifndef __GPcode01_01_xcode__Vec3d__
#define __GPcode01_01_xcode__Vec3d__

#include <stdio.h>

#include <math.h>

//! 3 dimensional vector class
//!
/*!
	\brief Class for 3-D vectors
 
 - vector operations: + (add) , - (sub), * (cross), ^ (dot)
 - Copyright(c) Young-Min Kang */

class CVec3d {
public:
    /*! vector elements */
    double x,y,z;
    
public:
    
    //! Constructors
    CVec3d();
    CVec3d(double a, double b, double c);
    //! Copy Constructor
    CVec3d(CVec3d &v);
    
    virtual ~CVec3d();
    
    
    //! Set Elements
    void set(double a, double b, double c);
    
    //! Get Elements
    void get(double &a, double &b, double &c);
    
    //! Bracket Operators for indexing the vector elements
    double operator[](int idx) const;
    
    //! Vector Addition
    /*! vectorA + vectorB returns the addition result*/
    CVec3d operator+(const CVec3d& v) const;
    
    //! Vector Subtraction
    /*! vectorA - vectorB returns the subtraction result*/
    CVec3d operator-(const CVec3d& v) const;
    
    //! Scalar multiplication
    /*! vectorA * scalar returns a scaled vector*/
    CVec3d operator *(const double& s) const;
    
    //! Vector Cross Product
    /*! vectorA * vectorB returns the cross product of the vectors */
    CVec3d operator*(const CVec3d& v) const; // cross product
    
    //! Vector Dot Product
    /*! vectorA ^ vectorB returns the dot product of the vectors */
    double operator^(const CVec3d& v) const; // dot product
    
    //! Vector Length
    double	len(void);
    
    //! Vector Normalization
    /*! The vector itself is normalized, and there is no return values */
    void	normalize(void);
    
    //! Returns the normalized version of the vector
    /*! The vector itself is not normalized, and the length is preserved */
    CVec3d	getNormalized(void);
    
    
    // Friend Functions
    
    /*! cross [friend function]: cross product of the given two vectors
     - usage: crossResult = cross(vector1, vector2) */
    friend CVec3d cross(const CVec3d& v1, const CVec3d& v2);
    
    /*! dot [friend function]: dot product of the given two vectors
     - usage: dotResult = dot(vector1, vector2) */
    friend double dot(const CVec3d& v1, const CVec3d v2);
    
    /*! * [friend operator]: scales a vector 
     - usage: scaledVector = scalar * originalVector */
    friend CVec3d operator*(double scalar, const CVec3d& v);
    
    
};

#endif /* defined(__GPcode01_01_xcode__Vec3d__) */
