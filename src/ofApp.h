#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxColorPicker.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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

		// general

		float w, h, planeSize, planeRes;

		// GUI
		ofxPanel guiNoises;
		ofxPanel guiVariations;
		ofxPanel guiFbm;
		ofxPanel guiColor;

		ofxFloatSlider noiseSeed;
		ofxFloatSlider contrast;
		ofxFloatSlider rate;
		ofxFloatSlider gradientNoiseScale;
		ofxFloatSlider gradientNoiseAmnt;
		ofxFloatSlider simplexNoiseScale;
		ofxFloatSlider simplexNoiseAmnt;
		ofxFloatSlider voronoiNoiseScale;
		ofxFloatSlider voronoiNoiseAmnt;
		ofxToggle gradientNoise;
		ofxToggle simplexNoise;
		ofxToggle voronoiNoise;

		ofxFloatSlider fbmHurst;
		ofxFloatSlider fbmFrequency;
		ofxIntSlider fbmOctaves;
		ofxIntSlider fbmWarp;
		ofxFloatSlider fbmRotation;

		ofxFloatSlider warpRotation;

		// PLANE
		ofPlanePrimitive plane;
		ofPlanePrimitive planeToMesh;

		// MESH
		ofMesh mesh;

		// MESH
		ofMesh mesh;

		// SHADER
		ofShader fbmShader;
		ofShader displaceShader;

		// FBO
		ofFbo fbmFbo;
		ofFbo displaceFbo;
		ofFbo::Settings fboSettings;

		// SAVE IMG
		ofPixels pix;
};
