#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	// global setup
	ofBackground(0);
	ofSetVerticalSync(true);

	// set variables
	w = ofGetWidth();
	h = ofGetHeight();
	planeSize = 1000;
	planeRes = 2;

	// shader setup
	fbmShader.load("shaderGL3/fbm");

	//plane setup
	plane.set(planeSize, planeSize);
	plane.setPosition(0, 0, 0);
	plane.setResolution(planeRes, planeRes);

	// fbo setup
	fbo.allocate(w, h);

	// gui setup
	gui.setup("Parameters", "settings.xml");
	gui.add(noiseSeed.setup("noise seed", 1., 1., 20.));
	gui.add(valueNoiseScale.setup("value noise scale", .2, 0., 2.));
	gui.add(valueNoiseAmnt.setup("value noise amount", 1.2, 0., 2.));
	gui.add(gradientNoiseScale.setup("gradient noise scale", .5, 0., 2.));
	gui.add(gradientNoiseAmnt.setup("gradient noise amount", 1., 0., 2.));
	gui.add(simplexNoiseScale.setup("simplex noise scale", .5, 0., 2.));
	gui.add(simplexNoiseAmnt.setup("simplex noise amount", 1., 0., 2.));
}

//--------------------------------------------------------------
void ofApp::update(){
	// open fbo
	fbo.begin();
		
		// start shader
		fbmShader.begin();

		// pass uniforms to shader
		fbmShader.setUniform1f("time", ofGetElapsedTimef());
		fbmShader.setUniform1f("planeSize", planeSize);
		fbmShader.setUniform1f("seed", noiseSeed);
		fbmShader.setUniform1f("valueScale", valueNoiseScale);
		fbmShader.setUniform1f("valueAmnt", valueNoiseAmnt);
		fbmShader.setUniform1f("gradientScale", gradientNoiseScale);
		fbmShader.setUniform1f("gradientAmnt", gradientNoiseAmnt);
		fbmShader.setUniform1f("simplexScale", simplexNoiseScale);
		fbmShader.setUniform1f("simplexAmnt", simplexNoiseAmnt);

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
