#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	// global setup
	ofBackground(0);
	ofSetVerticalSync(true);

	// set variables
	w = ofGetWidth();
	h = ofGetHeight();
	planeSize = 1200;
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
	guiNoises.setup("Noise Settings", "noiseSettings.xml");
	guiFbm.setup("Fbm Settings", "fbmSettings.xml");
	guiColors.setup("Colors Settings", "colorsSettings.xml");

	guiFbm.setPosition(0, 200);
	guiColors.setPosition(0, 400);

	guiNoises.add(noiseSeed.setup("noise seed", 1., 0., 2.));
	guiNoises.add(valueNoiseScale.setup("value noise scale", .2, 0., 2.));
	guiNoises.add(valueNoiseAmnt.setup("value noise amount", 1.2, 0., 2.));
	guiNoises.add(gradientNoiseScale.setup("gradient noise scale", .5, 0., 2.));
	guiNoises.add(gradientNoiseAmnt.setup("gradient noise amount", 1., 0., 2.));
	guiNoises.add(simplexNoiseScale.setup("simplex noise scale", .5, 0., 2.));
	guiNoises.add(simplexNoiseAmnt.setup("simplex noise amount", 1., 0., 2.));

	guiFbm.add(fbmHurst.setup("FBM Hurst", .5, 0., 1.));
	guiFbm.add(fbmFrequency.setup("FBM frequency", 2., 0., 4.));

	guiColors.add(colorsColor1Red.setup("COLOR 1 RED", 0., 0., 1.));
	guiColors.add(colorsColor1Green.setup("COLOR 1 GREEN", 0., 0., 1.));
	guiColors.add(colorsColor1Blue.setup("COLOR 1 BLUE", 0., 0., 1.));
	guiColors.add(colorsColor2Red.setup("COLOR 2 RED", 0., 0., 1.));
	guiColors.add(colorsColor2Green.setup("COLOR 2 GREEN", 0., 0., 1.));
	guiColors.add(colorsColor2Blue.setup("COLOR 2 BLUE", 0., 0., 1.));
	guiColors.add(colorsColor3Red.setup("COLOR 3 RED", 0., 0., 1.));
	guiColors.add(colorsColor3Green.setup("COLOR 3 GREEN", 0., 0., 1.));
	guiColors.add(colorsColor3Blue.setup("COLOR 3 BLUE", 0., 0., 1.));
	guiColors.add(colorsColor4Red.setup("COLOR 4 RED", 0., 0., 1.));
	guiColors.add(colorsColor4Green.setup("COLOR 4 GREEN", 0., 0., 1.));
	guiColors.add(colorsColor4Blue.setup("COLOR 4 BLUE", 0., 0., 1.));
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
		
		fbmShader.setUniform1f("fbmHurst", fbmHurst);
		fbmShader.setUniform1f("fbmFrequency", fbmFrequency);

		fbmShader.setUniform1f("colorsColor1Red", colorsColor1Red);
		fbmShader.setUniform1f("colorsColor1Green", colorsColor1Green);
		fbmShader.setUniform1f("colorsColor1Blue", colorsColor1Blue);
		fbmShader.setUniform1f("colorsColor2Red", colorsColor2Red);
		fbmShader.setUniform1f("colorsColor2Green", colorsColor2Green);
		fbmShader.setUniform1f("colorsColor2Blue", colorsColor2Blue);
		fbmShader.setUniform1f("colorsColor3Red", colorsColor3Red);
		fbmShader.setUniform1f("colorsColor3Green", colorsColor3Green);
		fbmShader.setUniform1f("colorsColor3Blue", colorsColor3Blue);
		fbmShader.setUniform1f("colorsColor4Red", colorsColor4Red);
		fbmShader.setUniform1f("colorsColor4Green", colorsColor4Green);
		fbmShader.setUniform1f("colorsColor4Blue", colorsColor4Blue);

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
	guiNoises.draw();
	guiFbm.draw();
	guiColors.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') {
		fbo.readToPixels(pix);
		float timeStamp = ofGetSystemTimeMillis();
		string imgName = ofToString(timeStamp) + "--grad.jpg";
		ofSaveImage(pix, imgName);
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
