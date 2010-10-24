#pragma once

#include "ofMain.h"
#include "ofxCvBlobTracker.h"
#include "ofxCvTrackedBlob.h"
#include "ofxCvConstants_Track.h"
#include "ofxSimpleGuiToo.h"
#include "ofxFBOTexture.h"
#include "ofxVec2f.h"
#include "Constants.h"
#include "Tools.h"

class Sensing  
{
	
public:
	
	static Sensing * getInstance();
	
	void update();
	void draw();
	
	bool show;
	bool showGrabScreen;
	
	ofxCvBlobTracker  blobTracker;	
	
	void grabColorFromVideo(int x, int y);
	
	void setListener(ofxCvBlobListener * listener);
	bool debug();
	
	int getCellWidth();
	int getCellHeight();
	
	float getRatioX() { return ratioX; }
	float getRatioY() { return ratioY; }
	float getDisplaceX() { return displaceX; }
	float getDisplaceY() { return displaceY; }
	
private:
	
	// singleton stuff
	Sensing();  // Private so that it can  not be called
	Sensing(Sensing const&){};             // copy constructor is private
	Sensing& operator=(Sensing const&){};  // assignment operator is private
	static Sensing* m_pInstance;
		
	bool maskToggle;
	bool debugToggle;
	
	int threshold;
	int blurAmount;
	int area;
	int hueMargin;
	int satMarginLow;
	int satMarginHigh;
	
	int cellWidth;
	int cellHeight;
	int cellMarginX;
	int cellMarginY;
	
	float ratioX;
	float ratioY;
	float displaceX;
	float displaceY;
    
	ofVideoGrabber  vidGrabber;
	ofImage mask;
	
	ofxCvContourFinder  contourFinder;
	ofxFBOTexture outputTexture;
    
	ofxCvColorImage  colorImg;
	ofxCvColorImage		    colorImgHSV;
	ofxCvGrayscaleImage  grayImg;
	ofxCvGrayscaleImage		hueImg;
	ofxCvGrayscaleImage		satImg;
	ofxCvGrayscaleImage     briImg;
	
    
	vector <ofxCvTrackedBlob> getBlobs();
	
	unsigned char * maskPixels;
	unsigned char * grayPixels;
	
	Color trackColor;
	
	ofTexture               trackedTextureRed;          //color texture that we are gonna draw to
};