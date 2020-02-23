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

	// shader setup
	fbmShader.load("shaderGL3/fbm");

	// fbo setup
	Fbmfbo.allocate(planeSize, planeSize);

	//plane setup
	plane.set(planeSize, planeSize);
	plane.setPosition(0, 0, 0);
	plane.setResolution(2, 2);

	// gui setup
	guiNoises.setup("Noise Settings", "noiseSettings.xml");
	guiVariations.setup("Noise Variation", "variationSettings.xml");
	guiFbm.setup("Fbm Settings", "fbmSettings.xml");
	guiColor.setup("Color Settings", "colorSettings.xml");

	guiNoises.setPosition(1700, 0);
	guiFbm.setPosition(1700, 240);
	guiVariations.setPosition(1700, 380);
	guiColor.setPosition(1900, 0);

	guiNoises.add(gradientNoise.setup("gradient noise", true));
	guiNoises.add(gradientNoiseScale.setup("gradient noise scale", .5, 0., 12.));
	guiNoises.add(gradientNoiseAmnt.setup("gradient noise amount", 1., 0., 4.));
	guiNoises.add(simplexNoise.setup("simplex noise", true));
	guiNoises.add(simplexNoiseScale.setup("simplex noise scale", .5, 0., 12.));
	guiNoises.add(simplexNoiseAmnt.setup("simplex noise amount", 1., 0., 4.));
	guiNoises.add(voronoiNoise.setup("voronoi noise", true));
	guiNoises.add(voronoiNoiseScale.setup("voronoi noise scale", .5, 0., 12.));
	guiNoises.add(voronoiNoiseAmnt.setup("voronoi noise amount", 1., 0., 4.));

	guiFbm.add(fbmHurst.setup("FBM Hurst", .5, 0., 1.));
	guiFbm.add(fbmFrequency.setup("FBM frequency", 2., 0., 4.));
	guiFbm.add(fbmOctaves.setup("FBM Octaves", 8, 1, 12));
	guiFbm.add(fbmWarp.setup("FBM Warp", 3, 1, 4));

	guiVariations.add(fbmRotation.setup("FBM Rot", 0., 0., 2.));
	guiVariations.add(rateFbm.setup("anim rate FBM", 0., 0., .25));
	guiVariations.add(noiseSeed.setup("noise seed", 1., 1., 2.));
	guiVariations.add(contrast.setup("contrast", 1., 0., 15.));

	guiColor.add(color_1.setup("color_1", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	guiColor.add(color_2.setup("color_2", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	guiColor.add(color_3.setup("color_3", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	guiColor.add(color_4.setup("color_4", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
}

//--------------------------------------------------------------
void ofApp::update(){
	// open FBM fbo
	Fbmfbo.begin();

		// start FBM shader
		fbmShader.begin();

		// pass uniforms to shader
		fbmShader.setUniform1f("time", ofGetElapsedTimef());
		fbmShader.setUniform1f("planeSize", planeSize);
		fbmShader.setUniform1f("seed", noiseSeed);
		fbmShader.setUniform1f("contrast", contrast);
		fbmShader.setUniform1f("rateFbm", rateFbm);

		fbmShader.setUniform1f("gradientNoise", gradientNoise);
		fbmShader.setUniform1f("gradientScale", gradientNoiseScale);
		fbmShader.setUniform1f("gradientAmnt", gradientNoiseAmnt);
		fbmShader.setUniform1f("simplexNoise", simplexNoise);
		fbmShader.setUniform1f("simplexScale", simplexNoiseScale);
		fbmShader.setUniform1f("simplexAmnt", simplexNoiseAmnt);
		fbmShader.setUniform1f("voronoiNoise", voronoiNoise);
		fbmShader.setUniform1f("voronoiScale", voronoiNoiseScale);
		fbmShader.setUniform1f("voronoiAmnt", voronoiNoiseAmnt);

		fbmShader.setUniform1f("fbmHurst", fbmHurst);
		fbmShader.setUniform1f("fbmFrequency", fbmFrequency);
		fbmShader.setUniform1i("fbmOctaves", fbmOctaves);
		fbmShader.setUniform1i("fbmWarp", fbmWarp);
		fbmShader.setUniform1f("fbmRotation", fbmRotation);

		fbmShader.setUniform4f("c1", ofColor(color_1));
		fbmShader.setUniform4f("c2", ofColor(color_2));
		fbmShader.setUniform4f("c3", ofColor(color_3));
		fbmShader.setUniform4f("c4", ofColor(color_4));

		// matrix transformations
		ofPushMatrix();
			ofTranslate(planeSize / 2., planeSize / 2.);
			plane.draw(); // plane draw
		ofPopMatrix();

		// end FBM shader
		fbmShader.end();

	// close FBM fbo
	Fbmfbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// draw FBM fbo
	Fbmfbo.draw( 50., 50., 1200., 1200.);

	// draw gui
	guiNoises.draw();
	guiFbm.draw();
	guiVariations.draw();
	guiColor.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') {
		Fbmfbo.readToPixels(pix);
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
