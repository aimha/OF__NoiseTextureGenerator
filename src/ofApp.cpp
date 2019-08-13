#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	// global setup
	ofBackground(0);
	ofSetVerticalSync(true);

	// set variables
	w = ofGetWidth();
	h = ofGetHeight();

	// shader setup
	fbmShader.load("shaderGL3/fbm");

	//plane setup
	plane.set(800, 800);
	plane.setPosition(0, 0, 0);
	plane.setResolution(400, 400);

	// fbo setup
	fbo.allocate(w, h);

	// gui setup
	gui.setup("Parameters", "settings.xml");
	//gui.add(renameMe.setup("renameMe", 0., 0., 100.));
}

//--------------------------------------------------------------
void ofApp::update(){
	// open fbo
	fbo.begin();
		
		// start shader
		fbmShader.begin();

		// pass uniforms to shader
		fbmShader.setUniform1f("time", ofGetElapsedTimef());

		// matrix transformations
		ofPushMatrix();
		ofTranslate(w / 2., h / 2.);

		// plane draw
		plane.draw();
		
		// end shader
		fbmShader.end();

	// close fbo
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// draw fbo
	fbo.draw(0, 0, w, h);

	// draw gui
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
