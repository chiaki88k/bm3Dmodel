//
//  plateMaterial.cpp
//  bm3Dmodel
//
//  Created by 坂本 千彰 on 2018/08/23.
//

#include "plateMaterial.h"

void plateMaterial:: setup(){
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    mesh.clear();
}

void plateMaterial:: setSize(float w, float h,  float d){
    float halfW=w/2;
    float halfH=h/2;
    float depth=d/2;
    glm::vec3 vertices[]={
        glm::vec3(-1*halfW, -1*halfH,  1*depth),//front square
        glm::vec3(1*halfW, -1*halfH,  1*depth),
        glm::vec3(1*halfW, 1*halfH,  1*depth),
        glm::vec3(-1*halfW, 1*halfH,  1*depth),
        
        glm::vec3(-1*halfW, -1*halfH,  -1*depth),//back square
        glm::vec3(1*halfW, -1*halfH,  -1*depth),
        glm::vec3(1*halfW, 1*halfH,  -1*depth),
        glm::vec3(-1*halfW, 1*halfH,  -1*depth)
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

void plateMaterial:: fbSetSize(float w, float hFront,float hBack, float t, float d){
    // create cube mesh
    float halfW=w/2;
    float halfT=t/2;
    float depth=d/2;
//    float halfH;
    glm::vec3 vertices[8];
  /*
    if(hFront>=hBack){
        halfH=(hFront-hBack)/2;
        vertices[0]=glm::vec3(-1*halfW, -1*halfT+halfH,  1*depth);        // front square vertices
        vertices[1]=glm::vec3( 1*halfW, -1*halfT+halfH,  1*depth);
        vertices[2]=glm::vec3( 1*halfW,  1*halfT+halfH,  1*depth);
        vertices[3]=glm::vec3(-1*halfW,  1*halfT+halfH,  1*depth);
        
        vertices[4]=glm::vec3(-1*halfW, -1*halfT-halfH, -1*depth);       // back square vertices
        vertices[5]=glm::vec3( 1*halfW, -1*halfT-halfH, -1*depth);
        vertices[6]=glm::vec3( 1*halfW,  1*halfT-halfH, -1*depth);
        vertices[7]=glm::vec3(-1*halfW,  1*halfT-halfH, -1*depth);
        
    }else if(hFront<hBack){
        halfH=(hBack-hFront)/2;
        vertices[0]=glm::vec3(-1*halfW, -1*halfT-halfH,  1*depth);        // front square vertices
        vertices[1]=glm::vec3( 1*halfW, -1*halfT-halfH,  1*depth);
        vertices[2]=glm::vec3( 1*halfW,  1*halfT-halfH,  1*depth);
        vertices[3]=glm::vec3(-1*halfW,  1*halfT-halfH,  1*depth);
        
        vertices[4]=glm::vec3(-1*halfW, -1*halfT+halfH, -1*depth);       // back square vertices
        vertices[5]=glm::vec3( 1*halfW, -1*halfT+halfH, -1*depth);
        vertices[6]=glm::vec3( 1*halfW,  1*halfT+halfH, -1*depth);
        vertices[7]=glm::vec3(-1*halfW,  1*halfT+halfH, -1*depth);
    }
   */
    vertices[0]=glm::vec3(-1*halfW, -1*halfT+hFront,  1*depth);        // front square vertices
    vertices[1]=glm::vec3( 1*halfW, -1*halfT+hFront,  1*depth);
    vertices[2]=glm::vec3( 1*halfW,  1*halfT+hFront,  1*depth);
    vertices[3]=glm::vec3(-1*halfW,  1*halfT+hFront,  1*depth);
    
    vertices[4]=glm::vec3(-1*halfW, -1*halfT+hBack, -1*depth);       // back square vertices
    vertices[5]=glm::vec3( 1*halfW, -1*halfT+hBack, -1*depth);
    vertices[6]=glm::vec3( 1*halfW,  1*halfT+hBack, -1*depth);
    vertices[7]=glm::vec3(-1*halfW,  1*halfT+hBack, -1*depth);
    
    
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

void plateMaterial:: drawFace(glm::vec3 pos){
    ofPushMatrix();
        ofTranslate(pos);
        mesh.drawFaces();
    ofPopMatrix();
}

void plateMaterial:: drawWireframe(glm::vec3 pos){
    ofPushMatrix();
        ofTranslate(pos);
        mesh.drawWireframe();
    ofPopMatrix();
}

void plateMaterial:: setPos(glm::vec3 pos){
    ofPopMatrix();
        ofTranslate(pos);
    ofPopMatrix();
}

void plateMaterial::clear(){
    mesh.clear();
}

ofMesh plateMaterial:: getMesh(){
    return mesh;
}


