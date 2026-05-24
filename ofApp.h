#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

	public:

		// START CONFIG
		int frameRate = 10;

		std::string imageName = "clon-4.jpg";
		float imageScale = 0.1;

		float pixelIntensityThreshold = 25.0;
		float meshDepthLimit = 75.0;
		float vertexDistanceThreshold = 25.0;

		float vertexDisplacementScale = 2.5;
		float timeScale = 10.0;
		// END CONFIG

		int screenWidth = ofGetWidth();
		int screenHeight = ofGetHeight();

		ofImage image;
		ofMesh mesh;
		size_t vertexCount;
		vector<ofVec3f> timeOffsets;

		ofEasyCam camera;
		float cameraStartPosition = -1000.0;
		float cameraEndPosition = 900.0;
		float cameraPosition = cameraStartPosition;
		float cameraSpeed = 1.0;
		std::string cameraDirection = "towards";

		void setup();
		void draw();

};
