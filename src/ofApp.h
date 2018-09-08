#pragma once

#include "ofMain.h"
#include "plateMaterial.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"

const int plateNum =5;
const int divitNumS = 50;
const int divitNumM =150;
const int divitNumL =300;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void drawFrame();
    
        void guiSetup();
        void drawInfo(int x,int y);
        void dist(int w,int h,int d, int s);
        void setMeshBox(glm::vec3 position,int n);
        void set3dColor();
    
        void widthChanged(int &width);
        void depthChanged(int &depth);
        void sHeightChanged(int &sHeight);
        void lHeightChanged(int &lHeight);
        void rHeightChanged(int &rHeight);
        void backrestHeightChanged(int &backrestHeight);
        void fHeightChanged(int &fHeight);
        void bHeightChanged(int &bHeight);
        void saveButtonPressed();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		

    ofEasyCam cam;
    ofCamera mono;
    ofRectangle camRect,monoRect;
    ofLight light,lightMono;
    
    ofPlanePrimitive plane,wall,planeMono;
    ofVboMesh chair;
    ofMaterial chairMt,monoMt,planeMt,wallMt;
    
    plateMaterial plate[plateNum];
    glm::vec3 pos[plateNum];
    
//gui
    ofxPanel gui,guiC;
    ofParameter<int>  width,depth,sHeight,
                    backrestHeight,lHeight,rHeight,
                    fHeight,bHeight,thickness;
    ofxButton saveModel;
        ofPoint buttonPos;
        ofRectangle saveRect;
        ofColor saveColor = ofColor(255,130);
        float fNum = 0;
        bool flash = 0;
    
    ofxFloatColorSlider ambient,diffuse,ambientP,diffuseP,ambientM,diffuseM;
    ofxVec2Slider lightPos;

    int w,d,brh,fh,bh,sh,lh,rh;
    bool  infomation=0,face=1;;
    float camX,camY,camZ;
    glm::vec2 window;
    
};

/*
 0=secondPlate
 1=left
 2=backRest
 3=right
 4=seat
 */
