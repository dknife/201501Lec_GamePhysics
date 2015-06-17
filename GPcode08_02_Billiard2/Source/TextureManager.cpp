//
//  TextureManager.cpp
//  XCode
//
//  Created by young-min kang on 6/10/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#include "TextureManager.h"
#include "STBImage.h"
    
CTextureManager::CTextureManager() {
    nTexture = 0;
}

CTextureManager::~CTextureManager() {
    
}

int CTextureManager::addTexture(char *fileName) {
    int w, h, nComp;
    unsigned char *img = stbi_load(fileName, &w, &h, &nComp, 0);
    
    glGenTextures(1, &tex[nTexture]);
    glBindTexture(GL_TEXTURE_2D, tex[nTexture]);
    if(nComp==3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    stbi_image_free(img);
    glBindTexture(GL_TEXTURE_2D,NULL);
    
    nTexture++;
    return nTexture-1;
}

void CTextureManager::useTexture(int i) {
    if(i<0) {
        glBindTexture(GL_TEXTURE_2D,NULL);
        return;
    }
    glBindTexture(GL_TEXTURE_2D, tex[i]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}
