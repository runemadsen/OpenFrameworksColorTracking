#pragma once

#include "ofMain.h"
#include "ofxCvBlobTracker.h"
#include "ofxCvTrackedBlob.h"
#include "ofxCvConstants_Track.h"
#include "ofxSimpleGuiToo.h"
#include "ofxFBOTexture.h"
#include "ofxVec2f.h"
#include "Constants.h"

class color
{
public:
	
	float hue, sat;
	
	ofxVec2f pos;
};

class Sensing  
{
	
public:
	
	Sensing(ofxCvBlobListener * listener);
	
	void update();
	void draw();
	
	bool show;
	bool disabled;
	bool showGrabScreen;
	
	ofxCvBlobTracker  blobTracker;	
	
	void grabColorFromVideo(int x, int y);
	
private:
	
	
	bool maskToggle;
	
	int threshold;
	int blurAmount;
	int area;
    
	ofVideoGrabber  vidGrabber;
	ofImage mask;
    
	ofxCvColorImage  colorImg;
    ofxCvGrayscaleImage  grayImg;
    ofxCvContourFinder  contourFinder;
    
	vector <ofxCvTrackedBlob> getBlobs();
	
	ofxFBOTexture outputTexture;
	
	unsigned char * maskPixels;
	unsigned char * grayPixels;
	
	ofxCvColorImage		    colorImgHSV;
	
	ofxCvGrayscaleImage		hueImg;
	ofxCvGrayscaleImage		satImg;
	ofxCvGrayscaleImage     briImg;
	
	color                   trackColor;
	
	unsigned char *         colorTrackedPixelsRed;      //just some raw images which we are gonna put pixels into
	ofTexture               trackedTextureRed;          //color texture that we are gonna draw to
};