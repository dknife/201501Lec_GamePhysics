//
//  Vec3f.h
//  GPcode01_01_xcode
//
//  Created by young-min kang on 3/28/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#ifndef __GPcode01_01_xcode__Vec3f__
#define __GPcode01_01_xcode__Vec3f__

#include <stdio.h>

#include <math.h>

//! 3 dimensional vector class
//!
/*!
	\brief Class for 3-D vectors
 
 - vector operations: + (add) , - (sub), * (cross), ^ (dot)
 - Copyright(c) Young-Min Kang */

class CVec3f {
    /*! vector elements */
    float x,y,z;
    
public:
    
    //! Constructors
    CVec3f();
    CVec3f(float a, float b, float c);
    //! Copy Constructor
    CVec3f(CVec3f &v);
    
    
    //! Set Elements
    void set(float a, float b, float c);
    
    //! Get Elements
    void get(float &a, float &b, float &c);
    
    //! Bracket Operators for indexing the vector elements
    float operator[](int idx) const;
    
    //! Vector Addition
    /*! vectorA + vectorB returns the addition result*/
    CVec3f& operator+(const CVec3f& v) const;
    
    //! Vector Subtraction
    /*! vectorA - vectorB returns the subtraction result*/
    CVec3f& operator-(const CVec3f& v) const;
    
    //! Scalar multiplication
    /*! vectorA * scalar returns a scaled vector*/
    CVec3f& operator *(const float& s) const;
    
    //! Vector Cross Product
    /*! vectorA * vectorB returns the cross product of the vectors */
    CVec3f& operator*(const CVec3f& v) const; // cross product
    
    //! Vector Dot Product
    /*! vectorA ^ vectorB returns the dot product of the vectors */
    float operator^(const CVec3f& v) const; // dot product
    
    //! Vector Length
    float	len(void);
    
    //! Vector Normalization
    /*! The vector itself is normalized, and there is no return values */
    void	normalize(void);
    
    //! Returns the normalized version of the vector
    /*! The vector itself is not normalized, and the length is preserved */
    CVec3f&	getNormalized(void);
    
    
    // Friend Functions
    
    /*! cross [friend function]: cross product of the given two vectors
     - usage: crossResult = cross(vector1, vector2) */
    friend CVec3f& cross(const CVec3f& v1, const CVec3f& v2);
    
    /*! dot [friend function]: dot product of the given two vectors
     - usage: dotResult = dot(vector1, vector2) */
    friend float dot(const CVec3f& v1, const CVec3f v2);
    
    /*! * [friend operator]: scales a vector 
     - usage: scaledVector = scalar * originalVector */
    friend CVec3f& operator*(float scalar, const CVec3f& v);
    
    
};

#endif /* defined(__GPcode01_01_xcode__Vec3f__) */
