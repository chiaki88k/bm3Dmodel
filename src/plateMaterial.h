//
//  plateMaterial.h
//  bm3Dmodel
//
//  Created by 坂本 千彰 on 2018/08/23.
//

#ifndef plateMaterial_h
#define plateMaterial_h
#include "ofMain.h"

class plateMaterial {
private:
public:
    void setup();
    void setSize(float w, float h, float d);
    void fbSetSize(float w, float hFront,float hBack, float t, float d);
//    void lrSetSize(float w, float hLeft,float hRight, float t, float d);
    void drawFace(glm::vec3 pos);
    void drawWireframe(glm::vec3 pos);
    void setPos(glm::vec3 pos);
    void clear();
    void save(string saveName);
    ofMesh getMesh();
    ofVboMesh mesh;
    ofImage img;
};


#endif /* plateMaterial_h */
