//  DepthBox.cpp
//  shell
//  Created by 坂本 千彰 on 2018/05/12.

#include "DepthBox.h"

void DepthBox::setup(){
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    mesh.clear();
}
void DepthBox::tbSetSize(float w,float h,float d1,float d2){
    // create cube mesh
    float halfW=w/2;
    float halfH=h/2;
    
    glm::vec3 vertices[] = {
        glm::vec3(-1*halfW, -1*halfH,  1*d2),        // front square vertices
        glm::vec3( 1*halfW, -1*halfH,  1*d2),
        glm::vec3( 1*halfW,  1*halfH,  1*d1),
        glm::vec3(-1*halfW,  1*halfH,  1*d1),
        
        glm::vec3(-1*halfW, -1*halfH, 0),        // back square vertices
        glm::vec3( 1*halfW, -1*halfH, 0),
        glm::vec3( 1*halfW,  1*halfH, 0),
        glm::vec3(-1*halfW,  1*halfH, 0),
    };
    
    ofIndexType indices[] = {
        // -- winding is counter-clockwise (facing camera)
        0,1,2,        // pos z
        0,2,3,
        1,5,6,        // pos x
        1,6,2,
        2,6,7,        // pos y
        2,7,3,
        
        // -- winding is clockwise (facing away from camera)
        3,4,0,        // neg x
        3,7,4,
        4,5,1,        // neg y
        4,1,0,
        5,7,6,        // neg z
        5,4,7,
    };
    
    glm::vec3 normals[] = {
        glm::vec3( 0,  0,  1),
        glm::vec3( 1,  0,  0),
        glm::vec3( 0,  1,  0),
        glm::vec3(-1,  0,  0),
        glm::vec3( 0, -1,  0),
        glm::vec3( 0,  0, -1),
        glm::vec3(1,0,0), // can be anything, will not be used
        glm::vec3(1,0,0), //  -- " --
    };
    
    mesh.addVertices(vertices, 8);
    mesh.addNormals(normals,8);
    mesh.addIndices(indices, 3*2*6);
}

void DepthBox::lrSetSize(float w,float h,float d1,float d2){
    // create cube mesh
    float halfW=w/2;
    float halfH=h/2;
    
    glm::vec3 vertices[] = {
        glm::vec3(-1*halfW, -1*halfH,  1*d1),        // front square vertices
        glm::vec3( 1*halfW, -1*halfH,  1*d2),
        glm::vec3( 1*halfW,  1*halfH,  1*d2),
        glm::vec3(-1*halfW,  1*halfH,  1*d1),
        
        glm::vec3(-1*halfW, -1*halfH, 0),        // back square vertices
        glm::vec3( 1*halfW, -1*halfH, 0),
        glm::vec3( 1*halfW,  1*halfH, 0),
        glm::vec3(-1*halfW,  1*halfH, 0),
    };
    
    ofIndexType indices[] = {
        // -- winding is counter-clockwise (facing camera)
        0,1,2,        // pos z
        0,2,3,
        1,5,6,        // pos x
        1,6,2,
        2,6,7,        // pos y
        2,7,3,
        
        // -- winding is clockwise (facing away from camera)
        3,4,0,        // neg x
        3,7,4,
        4,5,1,        // neg y
        4,1,0,
        5,7,6,        // neg z
        5,4,7,
    };
    
    glm::vec3 normals[] = {
        glm::vec3( 0,  0,  1),
        glm::vec3( 1,  0,  0),
        glm::vec3( 0,  1,  0),
        glm::vec3(-1,  0,  0),
        glm::vec3( 0, -1,  0),
        glm::vec3( 0,  0, -1),
        glm::vec3(1,0,0), // can be anything, will not be used
        glm::vec3(1,0,0), //  -- " --
    };
    
    mesh.addVertices(vertices,8);
    mesh.addNormals(normals,8);
    mesh.addIndices(indices,3*2*6);
}

void DepthBox::drawFace(glm::vec3 pos){
    ofPushMatrix();
        ofTranslate(pos);
    mesh.drawFaces();
    ofPopMatrix();
}
void DepthBox::drawWireframe(glm::vec3 pos){
    ofPushMatrix();
        ofTranslate(pos);
    mesh.drawWireframe();
    ofPopMatrix();
}
void DepthBox::setPos(glm::vec3 pos){
    ofPopMatrix();
        ofTranslate(pos);
    ofPopMatrix();
}
void DepthBox::save(string saveName){
    mesh.save("test_" + saveName + ".ply");
//    img.grabScreen(0,0,ofGetWidth(), ofGetHeight());
//    img.save("test_" + saveName + ".png");
}
void DepthBox::clear(){
    mesh.clear();
}
ofMesh DepthBox::getMesh(){
    return mesh;
}








