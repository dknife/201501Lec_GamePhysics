//
//  TextureManager.h
//  XCode
//
//  Created by young-min kang on 6/10/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#ifndef __XCode__TextureManager__
#define __XCode__TextureManager__

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

#include <stdio.h>

class CTextureManager {
    int nTexture;
    GLuint tex[256];
    
public:    
    CTextureManager();
    ~CTextureManager();
    
    int addTexture(char *fileName);
    void useTexture(int);
};

#endif /* defined(__XCode__TextureManager__) */
