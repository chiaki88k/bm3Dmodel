#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    window = ofGetWindowSize();
    
    guiSetup();
        brh = backrestHeight;
        d = depth;
        fh = fHeight;
        bh = bHeight;
        lh = lHeight;
        rh = rHeight;
        sh = sHeight;
    
    for(int i=0;i<5;i++){plate[i].setup();}
    
    cam.setDistance(1000);
    cam.setPosition(0, 400, 2000);
    camRect.set(0,0,window.x/2,window.y);
    
    mono.setPosition(0, 400, 2000);
    monoRect.set(window.x/2,0,window.x/2,window.y);
  
    light.setup();
    lightMono.setup();

    plane.set(width*5,depth*2);
    plane.setResolution(2, 2);
    plane.rotateRad(HALF_PI, glm::vec3(-1,0,0));
}

//--------------------------------------------------------------
void ofApp::update(){

    chair.clear();

    set3dColor();
    
    for(int i=0;i<plateNum;i++){plate[i].clear();}

    plate[0].fbSetSize(width-1, fHeight, bHeight, thickness, depth);//secondPlate
    plate[1].setSize(thickness, lHeight, depth);//left
    plate[2].setSize(width, backrestHeight, thickness);//backrest
    plate[3].setSize(thickness, rHeight, depth);//right
    plate[4].setSize(width-1, thickness, depth);//seat
    
    pos[0]=glm::vec3(0,0,0);
    pos[1]=glm::vec3(-width/2+thickness/2,lHeight/2,0);
    pos[2]=glm::vec3(0,backrestHeight/2,-depth/2-thickness/2);
    pos[3]=glm::vec3(width/2-thickness/2,rHeight/2,0);
    pos[4]=glm::vec3(0,sHeight,0);
    
    for(int i=0;i<plateNum;i++){
        setMeshBox(pos[i], i);
    }
    
    if(flash){
        float divit = 0.95;
        fNum = fNum*divit;
        if(fNum<1)flash=!flash;
        }else{
            fNum=0;
        }
    
    camX = cam.getX();
    camY = cam.getY();
    camZ = cam.getZ();
    
    plane.set(width*5,depth*2);
    plane.setPosition(0, -1, depth/2);

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(250);
    ofSetColor(200,fNum);
    ofDrawRectangle(0, 0, window.x/2, window.y);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
        light.enable();
        cam.begin(camRect);
//            ofSetColor(255);
        chairMt.begin();//material_begin
            if(face){
                chair.draw();
            }else if(face==0){
                chair.drawWireframe();
            }
        chairMt.end();
    
        planeMt.begin();
            plane.draw();
        planeMt.end();
    
            dist(width,backrestHeight,depth,sHeight);
        cam.end();
        light.disable();
    
    lightMono.enable();
        ofPushMatrix();
//            ofSetColor(255);
        monoMt.begin();
            mono.begin(monoRect);
            for(int i=0;i<plateNum;i++){
                plate[i].drawFace(pos[i]);
            }
            plane.draw();
            mono.end();
        monoMt.end();
        ofPopMatrix();
    lightMono.disable();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    gui.draw();
    ofSetColor(saveColor);
    ofDrawRectangle(saveRect);
    saveColor = ofColor(255,50);
//    ofDrawRectangle(window.x/2, 0, window.x, window.y);

    
    if(infomation){
        guiC.draw();
        drawInfo(window.x-200, 30);
        ofSetColor(30, 255);
    }
}
void ofApp:: drawInfo(int x,int y){
    ofSetColor(30, 255);
    string info;
    info="info\n";
    info+="frameRate_"+ofToString(ofGetFrameRate())+"\n";
    info+="mouseX_"+ofToString(ofGetMouseX())+"\n";
    info+="mouseY_"+ofToString(ofGetMouseY())+"\n";
    info+="camX_"+ofToString(camX)+"\n";
    info+="camY_"+ofToString(camY)+"\n";
    info+="camZ_"+ofToString(camZ)+"\n";
    info+="saveButtonPos"+ofToString(buttonPos.x)+"/"+ofToString(buttonPos.y)+"\n";

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
void ofApp::guiSetup(){
    ofxGuiSetDefaultHeight(window.y/50);
    ofxGuiSetDefaultWidth(window.x/8);
//    ofxGuiSetTextPadding(4);
    int clr = 45,sClre = 3;
    
    
    gui.setup("parameter");
    gui.setPosition(clr,clr);

    gui.setDefaultBackgroundColor(ofColor(0,0,0,100));
    gui.setDefaultBorderColor(ofColor(255));
//    gui.setHeaderBackgroundColor(ofColor(0,255,255,255));
//    gui.setDefaultFillColor(ofColor(0,255,255,255));
    
    gui.add(width.set("width",300,15,1800));
    width.addListener(this, &ofApp::widthChanged);
    gui.add(depth.set("depth",350,15,900));
    depth.addListener(this, &ofApp::depthChanged);
    
    gui.add(sHeight.set("seatHeight",400,15,900));
    
    sHeight.addListener(this, &ofApp::sHeightChanged);
    gui.add(thickness.set("thickness",11,1,30));
    gui.add(backrestHeight.set("backrest",700,15,1500));
    backrestHeight.addListener(this, &ofApp::backrestHeightChanged);
    gui.add(lHeight.set("leftHeight",400,15,1200));
    lHeight.addListener(this, &ofApp::lHeightChanged);
    gui.add(rHeight.set("rightHeight",400,15,1200));
    rHeight.addListener(this, &ofApp::rHeightChanged);
    gui.add(fHeight.set("frontHeight",15,15,900));
    fHeight.addListener(this, &ofApp::fHeightChanged);
    
    gui.add(bHeight.set("backHeight",sHeight-thickness/2,15,900));
    bHeight.addListener(this, &ofApp::bHeightChanged);
    
    gui.add(saveModel.setup("saveButton_output PLY",window.x/8,window.y/50));
    saveModel.addListener(this, &ofApp::saveButtonPressed);
    buttonPos = saveModel.getPosition();
    saveRect = ofRectangle(buttonPos.x+sClre, buttonPos.y+sClre, window.y/50-sClre*2, window.y/50-sClre*2);
    
    guiC.setup("color");
    guiC.setPosition(window.x/2+clr*2,clr);
    guiC.add(ambient.setup("chair_ambientColor",ofFloatColor(0.5,0.3,0.1),ofFloatColor(0,0),ofFloatColor(1.0,1.0)));
    guiC.add(diffuse.setup("chair_diffuseColor",ofFloatColor(0.5,0.4,0.06),ofFloatColor(0,0),ofFloatColor(1.0,1.0)));
    guiC.add(ambientM.setup("mono_ambientColor",ofFloatColor(0.3,0.3,0.3),ofFloatColor(0,0),ofFloatColor(1.0,1.0)));
    guiC.add(diffuseM.setup("mono_diffuseColor",ofFloatColor(0.55,0.55,0.55),ofFloatColor(0,0),ofFloatColor(1.0,1.0)));
    guiC.add(ambientP.setup("plane_ambientColor",ofFloatColor(0.74,0.7,0.6),ofFloatColor(0,0),ofFloatColor(1.0,1.0)));
    guiC.add(diffuseP.setup("plane_diffuseColor",ofFloatColor(0.01,0.01,0.01),ofFloatColor(0,0),ofFloatColor(1.0,1.0)));
    
    
    guiC.add(lightPos.setup("light_Pos",ofVec2f(window.x*.5, window.y*.5), ofVec2f(0, 0), ofVec2f(window.x, window.y)));
}

void ofApp::set3dColor(){
    light.setPosition(ofPoint(lightPos->x,1000,lightPos->y));
    light.setAmbientColor(ofFloatColor(1.0));
    light.setDiffuseColor(ofFloatColor(1.0));
    
    lightMono.setPosition(ofPoint(lightPos->x,1000,lightPos->y));
    lightMono.setAmbientColor(ofFloatColor(1.0));
    lightMono.setDiffuseColor(ofFloatColor(1.0));

    chairMt.setAmbientColor(ambient);
    chairMt.setDiffuseColor(diffuse);
    
    planeMt.setAmbientColor(ambientP);
    planeMt.setDiffuseColor(diffuseP);

    monoMt.setAmbientColor(ambientM);
    monoMt.setDiffuseColor(diffuseM);
}
//--------------------------------------------------------------
void ofApp::dist(int w,int h,int d ,int s){
    int space = 30;
    
    ofPolyline x,y,z,seat;
    ofSetColor(100);
    ofSetLineWidth(2);
    
    x.addVertex(glm::vec3(-w/2,0,d/2));
    x.addVertex(glm::vec3(-w/2,0,d/2+space));
    x.addVertex(glm::vec3(w/2,0,d/2+space));
    x.addVertex(glm::vec3(w/2,0,d/2));
    x.draw();
    
    y.addVertex(glm::vec3(w/2,h,-d/2));
    y.addVertex(glm::vec3(w/2+space,h,-d/2));
    y.addVertex(glm::vec3(w/2+space,0,-d/2));
    y.addVertex(glm::vec3(w/2,0,-d/2));
    y.draw();
    
    z.addVertex(glm::vec3(w/2,0,d/2));
    z.addVertex(glm::vec3(w/2+space,0,d/2));
    z.addVertex(glm::vec3(w/2+space,0,-d/2));
    z.addVertex(glm::vec3(w/2,0,-d/2));
    z.draw();
    
    seat.addVertex(glm::vec3(w/2,0,d/2));
    seat.addVertex(glm::vec3(w/2+space,0,d/2));
    seat.addVertex(glm::vec3(w/2+space,s,d/2));
    seat.addVertex(glm::vec3(w/2,s,d/2));
    seat.draw();
    
//    ofPushMatrix();
//    ofTranslate(-window.x/2, 0);
        ofDrawBitmapString(ofToString(w), glm::vec3(0,0,d/2+space*2));
        ofDrawBitmapString(ofToString(h), glm::vec3(w/2+space*2,h/2,-d/2));
        ofDrawBitmapString(ofToString(d), glm::vec3(w/2+space*2,0,0));
        ofDrawBitmapString(ofToString(s), glm::vec3(w/2+space*2,s/2,d/2));
//    ofPopMatrix();
}

//--------------------------------------------------------------

void ofApp::widthChanged(int &width){
    w = width/divitNumL;
    width = w*divitNumL;
}
void ofApp::depthChanged(int &depth){
    d = depth/divitNumM;
    depth = d*divitNumM;
}

void ofApp::sHeightChanged(int &sHeight){
    if(sHeight>backrestHeight)backrestHeight=sHeight;
    if(sHeight<fHeight)fHeight = sHeight;
    if(sHeight<bHeight)bHeight = sHeight;
    if(sHeight>lHeight&&sHeight>rHeight){
        lHeight=sHeight;
        rHeight=sHeight;
    }
    sh = sHeight/divitNumS;
    sHeight = sh*divitNumS;
}

void ofApp::backrestHeightChanged(int &backrestHeight){
    if( backrestHeight<sHeight)backrestHeight = sHeight;
        brh = backrestHeight/divitNumM;
        backrestHeight = brh*divitNumM;
}
void ofApp::lHeightChanged(int &lHeight){
    sHeight>lHeight&&sHeight>rHeight ? lHeight=sHeight : lHeight = lHeight;
    if(lHeight<sHeight)lHeight=sHeight;
    lh = lHeight/divitNumS;
    lHeight=lh*divitNumS;
}
void ofApp::rHeightChanged(int &rHeight){
    sHeight>lHeight&&sHeight>rHeight ? rHeight=sHeight : rHeight = rHeight;
    if(rHeight<sHeight)rHeight=sHeight;
    rh = rHeight/divitNumS;
    rHeight=rh*divitNumS;
}
void ofApp::fHeightChanged(int &fHeight){
    sHeight<fHeight ? fHeight = sHeight : fHeight = fHeight;
    fh = fHeight/divitNumS;
    fHeight = fh*divitNumS;
}
void ofApp::bHeightChanged(int &bHeight){
    sHeight<bHeight? bHeight = sHeight : bHeight = bHeight;
    bh = bHeight/divitNumS;
    bHeight = bh*divitNumS;
}

void ofApp::saveButtonPressed(){
    chair.save("3DModels/"+ofGetTimestampString()+".ply");
    fNum = 255;
    flash=!flash;
}

//--------------------------------------------------------------
void ofApp::setMeshBox(glm::vec3 position,int n){
    ofVboMesh mesh;
    mesh = plate[n].getMesh();
    int num = n*8;
    glm::vec3 vertices[8];
    glm::vec3 normals[8];
    ofIndexType indices[36];
    
    for (int i = 0; i < 8; i++) {
        vertices[i] = mesh.getVertices()[i];
        normals[i] = mesh.getNormals()[i];
    }
    for (int i = 0; i < 36; i++) {
        indices[i] = mesh.getIndices()[i];
    }
    for (int i = 0; i < 8; i++) {
        vertices[i].x = vertices[i].x+position.x;
        vertices[i].y = vertices[i].y+position.y;
        vertices[i].z = vertices[i].z+position.z;
    }
    chair.addVertices(vertices,8);
    chair.addNormals(normals,8);
    
    for (int i = 0; i < 36; i++) {
        chair.addIndex(indices[i]+num);
    }
    mesh.clear();
    
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


