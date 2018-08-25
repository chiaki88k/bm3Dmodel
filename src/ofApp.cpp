#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    ofEnableDepthTest();
    
    gui.setup();
    gui.add(width.setup("width",300,15,1800));
    gui.add(depth.setup("depth",350,15,900));
    gui.add(sHeight.setup("seatHeight",400,15,900));
    gui.add(backrestHeight.setup("backrest",700,15,1500));
    gui.add(lHeight.setup("leftHeight",400,15,1200));
    gui.add(rHeight.setup("rightHeight",400,15,1200));
    gui.add(fHeight.setup("frontHeight",15,15,900));
    gui.add(bHeight.setup("backHeight",400,15,900));
    gui.add(thickness.setup("thickness",15,1,30));
    gui.add(ambient.setup("light_ambientColor",ofFloatColor(0.5,0.5,0.5),ofFloatColor(0,0),ofFloatColor(1.0,1.0)));
    gui.add(diffuse.setup("light_diffuseColor",ofFloatColor(0.5,0.5,0.5),ofFloatColor(0,0),ofFloatColor(1.0,1.0)));
    gui.add(lightPos.setup("light_Pos",ofVec2f(ofGetWidth()*.5, ofGetHeight()*.5), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));

    for(int i=0;i<5;i++){plate[i].setup();}
    
    cam.setDistance(1000);
    cam.setPosition(0, 500, 0);
    light.setup();

    plane.set(800, 800, 30, 30);
    plane.rotateDeg(90, 1, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    mesh.clear();
//    cam.lookAt(glm::vec3(0));
    light.setPosition(ofPoint(lightPos->x,1000,lightPos->y));
    light.setAmbientColor(ambient);
    light.setDiffuseColor(diffuse);

    for(int i=0;i<5;i++){plate[i].clear();}
    //Naname_Style
    plate[0].fbSetSize(width, fHeight, bHeight, thickness, depth);//secondPlate
    plate[1].setSize(thickness, lHeight, depth);//left
    plate[2].setSize(width, backrestHeight, thickness);//backrest
    plate[3].setSize(thickness, rHeight, depth);//right
    plate[4].setSize(width, thickness, depth);//seat
    
    if(fHeight>bHeight)spHeight=fHeight;
    if(fHeight<bHeight)spHeight=bHeight;

    
    /*`plate[0].setPos(glm::vec3(0,sHeight/2,0));
     plate[1].setPos(glm::vec3(-width/2+thickness,sHeight/2,0));
     plate[2].setPos(glm::vec3(width/2-thickness,sHeight/2,0));
     plate[3].setPos(glm::vec3(0,backrestHeight/2,-depth/2-thickness/2));
     plate[4].setPos(glm::vec3(0,sHeight+thickness/2,0));
     */
    
    for(int i=0;i<5;i++){
        mesh.push_back(plate[i].getMesh());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(250);
    ofSetColor(255);
    
    
    ofPushMatrix();
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    light.enable();
        cam.begin();
    //        for(int i=0;i<mesh.size();i++){
    //            mesh[i].drawWireframe();
    //        }
            if(face){
                plate[0].drawFace(glm::vec3(0,spHeight/2,0));
                plate[1].drawFace(glm::vec3(-width/2+thickness/2,lHeight/2,0));
                plate[2].drawFace(glm::vec3(0,backrestHeight/2,-depth/2-thickness/2));
                plate[3].drawFace(glm::vec3(width/2-thickness/2,rHeight/2,0));
                plate[4].drawFace(glm::vec3(0,sHeight+thickness/2,0));
            }else if(face==0){
                plate[0].drawWireframe(glm::vec3(0,spHeight/2,0));
                plate[1].drawWireframe(glm::vec3(-width/2+thickness/2,lHeight/2,0));
                plate[2].drawWireframe(glm::vec3(0,backrestHeight/2,-depth/2-thickness/2));
                plate[3].drawWireframe(glm::vec3(width/2-thickness/2,rHeight/2,0));
                plate[4].drawWireframe(glm::vec3(0,sHeight+thickness/2,0));
            }
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        cam.end();
    light.disable();
    ofPopMatrix();
    
    if(infomation)gui.draw();
    ofSetColor(30, 255);
    drawInfo(ofGetWidth()-200, 30);

}


void ofApp:: drawInfo(int x,int y){
    string info;
    info="info\n";
    info+="frameRate_"+ofToString(ofGetFrameRate())+"\n";
    info+="mouseX_"+ofToString(ofGetMouseX())+"\n";
    info+="mouseY_"+ofToString(ofGetMouseY())+"\n";
    info+="\n";
    
    ofDrawBitmapString(info,x,y);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'h':
            infomation=!infomation;
            break;
        case 'f':
            face=!face;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
