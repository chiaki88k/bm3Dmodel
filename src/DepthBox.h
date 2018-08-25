//
//  DepthBox.hpp
//  shell
//
//  Created by 坂本 千彰 on 2018/05/12.
//
#pragma once
#include "ofMain.h"
class DepthBox {
    private:
    public:
        void setup();
        void tbSetSize(float w,float h,float d1,float d2);
        void lrSetSize(float w,float h,float d1,float d2);
        void drawFace(glm::vec3 pos);
        void drawWireframe(glm::vec3 pos);
        void setPos(glm::vec3 pos);
        void clear();
        void save(string saveName);
        ofMesh getMesh();
        ofVboMesh mesh;
        ofImage img;
};



//#ifndef DepthBox_hpp
//#define DepthBox_hpp

//#include <stdio.h>
//
//#endif /* DepthBox_hpp */

