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
	displaceShader.load("shaderGL3/displace");

	// fbo setup
	fbmFbo.allocate(planeSize, planeSize);

	ofFbo fbo;

	fboSettings.width = w;
	fboSettings.height	= h;
	fboSettings.internalformat = GL_RGBA;
	fboSettings.useDepth = true;
	fboSettings.depthStencilAsTexture = true;
	displaceFbo.allocate(fboSettings);

	// planes setup
	plane.set(planeSize, planeSize);
	plane.setPosition(0, 0, 0);
	plane.setResolution(planeRes, planeRes);

	planeToMesh.set(planeSize, planeSize);
	planeToMesh.setPosition(0, 0, 0);
	planeToMesh.setResolution(100, 100);
	planeToMesh.mapTexCoordsFromTexture(fbmFbo.getTextureReference());

	// mesh setup
	mesh = planeToMesh.getMesh();
	mesh.setMode(OF_PRIMITIVE_POINTS);
	mesh.enableColors();
	
	// gui setup
	guiNoises.setup("Noise Settings", "noiseSettings.xml");
	guiVariations.setup("Noise Variation", "variationSettings.xml");
	guiFbm.setup("Fbm Settings", "fbmSettings.xml");
	guiColor.setup("Color Settings", "colorSettings.xml");

	guiNoises.setPosition(50, 0);
	guiFbm.setPosition(50, 240);
	guiVariations.setPosition(50, 380);

	guiNoises.add(gradientNoiseScale.setup("gradient noise scale", .5, 0., 4.));
	guiNoises.add(gradientNoiseAmnt.setup("gradient noise amount", 1., 0., 2.));
	guiNoises.add(simplexNoise.setup("simplex noise", true));
	guiNoises.add(simplexNoiseScale.setup("simplex noise scale", .5, 0., 4.));
	guiNoises.add(voronoiNoise.setup("voronoi noise", true));
	guiNoises.add(voronoiNoiseScale.setup("voronoi noise scale", .5, 0., 4.));
	guiNoises.add(voronoiNoiseAmnt.setup("voronoi noise amount", 1., 0., 2.));

	guiFbm.add(fbmHurst.setup("FBM Hurst", .5, 0., 1.));
	guiFbm.add(fbmFrequency.setup("FBM frequency", 2., 0., 4.));
	guiFbm.add(fbmOctaves.setup("FBM Octaves", 8, 1, 12));
	guiFbm.add(fbmWarp.setup("FBM Warp", 3, 1, 4));

	guiVariations.add(fbmRotation.setup("FBM Rot", 0., 0., 2.));
	guiVariations.add(warpRotation.setup("WARP Rot", 0., 0., 2.));
	guiVariations.add(rate.setup("anim rate", 0., 0., .25));
	guiVariations.add(noiseSeed.setup("noise seed", 1., 1., 2.));
	guiVariations.add(contrast.setup("contrast", 1., 0., 10.));
}

//--------------------------------------------------------------
void ofApp::update(){
	// open fbo
	fbmFbo.begin();
		
		// start shader
		fbmShader.begin();

		// pass uniforms to shader
		fbmShader.setUniform1f("time", ofGetElapsedTimef());
		fbmShader.setUniform1f("planeSize", planeSize);
		fbmShader.setUniform1f("seed", noiseSeed);
		fbmShader.setUniform1f("contrast", contrast);
		fbmShader.setUniform1f("rate", rate);

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
		fbmShader.setUniform1f("warpRotation", warpRotation);

		fbmShader.setUniform4f("c1", ofColor(color_1));
		fbmShader.setUniform4f("c2", ofColor(color_2));
		fbmShader.setUniform4f("c3", ofColor(color_3));
		fbmShader.setUniform4f("c4", ofColor(color_4));

		// matrix transformations
		ofPushMatrix();
			ofTranslate(planeSize / 2., planeSize / 2.);

			// plane draw
			plane.draw();
		
		ofPopMatrix(); 
		
		// end shader
		fbmShader.end();

	// close fbo	
	fbmFbo.end();

	//*******************************************************//

	ofEnableDepthTest();

	// open fbo
	displaceFbo.begin();

	ofClear(0);

		// start shader
		displaceShader.begin();

		displaceShader.setUniform1f("planeSize", planeSize);
		displaceShader.setUniformTexture("tex0", fbmFbo.getTexture(), 0);

		// draw mesh
		ofPushMatrix();
			ofTranslate(w / 2. + 300., h / 2. + 100.);
			ofRotateX(-90.);
			mesh.drawWireframe();
		ofPopMatrix();

		// end shader
		displaceShader.end();

	// close fbo	
	displaceFbo.end();

	ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// draw fbo
	displaceFbo.draw(0., 0., w, h);
	fbmFbo.draw(0., 0., 500., 500.);
		

	// draw gui
	guiNoises.draw();
	guiFbm.draw();
	guiVariations.draw();
	guiColor.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	displaceFbo.begin();
		ofClear(0);
	displaceFbo.end();
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
