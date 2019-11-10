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
		ofxPanel guiColors;

		ofxVec2Slider center;

		ofxFloatSlider noiseSeed;
		ofxFloatSlider valueNoiseScale;
		ofxFloatSlider valueNoiseAmnt;
		ofxFloatSlider gradientNoiseScale;
		ofxFloatSlider gradientNoiseAmnt;
		ofxFloatSlider simplexNoiseScale;
		ofxFloatSlider simplexNoiseAmnt;
		ofxFloatSlider voronoiNoiseScale;
		ofxFloatSlider voronoiNoiseAmnt;
		ofxToggle valueNoise;
		ofxToggle gradientNoise;
		ofxToggle simplexNoise;
		ofxToggle voronoiNoise;

		ofxFloatSlider fbmHurst;
		ofxFloatSlider fbmFrequency;
		ofxIntSlider fbmOctaves;
		ofxIntSlider fbmWarp;
		ofxFloatSlider fbmRotation;

		ofxFloatSlider warpRotation;

		ofxFloatSlider colorsColor1Red;
		ofxFloatSlider colorsColor1Green;
		ofxFloatSlider colorsColor1Blue;
		ofxFloatSlider colorsColor2Red;
		ofxFloatSlider colorsColor2Green;
		ofxFloatSlider colorsColor2Blue;
		ofxFloatSlider colorsColor3Red;
		ofxFloatSlider colorsColor3Green;
		ofxFloatSlider colorsColor3Blue;
		ofxFloatSlider colorsColor4Red;
		ofxFloatSlider colorsColor4Green;
		ofxFloatSlider colorsColor4Blue;

		// PLANE
		ofPlanePrimitive plane;

		// SHADER
		ofShader fbmShader;

		// FBO
		ofFbo fbo;

		// SAVE IMG
		ofPixels pix;

};
