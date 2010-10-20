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
	
	struct xsorter
	{
		bool operator()(ofxCvTrackedBlob a, ofxCvTrackedBlob b) const
		{
			if(a.centroid.x < b.centroid.x)
			{
				return true;
			}
			
			return false;
		}
	};
	
	struct ysorter
	{
		bool operator()(ofxCvTrackedBlob a, ofxCvTrackedBlob b) const
		{
			if(a.centroid.y < b.centroid.y)
			{
				return true;
			}
			
			return false;
		}
	};
	
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
	int hueMargin;
	int satMarginLow;
	int satMarginHigh;
    
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