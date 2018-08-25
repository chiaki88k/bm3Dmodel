#pragma once

#include "ofMain.h"
#include "plateMaterial.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"

const int plateNum =5;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void drawInfo(int x,int y);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    ofEasyCam cam;
    ofLight light;
    
    ofPlanePrimitive plane;
    vector<ofVboMesh> mesh;
    
    plateMaterial plate[plateNum];

//gui
    ofxPanel gui;
    ofxFloatSlider  width,depth,sHeight,
                    backrestHeight,lHeight,rHeight,
                    fHeight,bHeight,thickness;
    ofxFloatColorSlider ambient,diffuse;
    ofxVec2Slider lightPos;

    float spHeight;
    bool  infomation=1,face=1;;
    
};

/*
 0=secondPlate
 1=left
 2=backRest
 3=right
 4=seat
 */
