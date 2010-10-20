#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "ofxCvTrackedBlob.h"

#define MOVE_MARGIN 0.5

class VideoCell
{
public:
	
	VideoCell(ofxCvTrackedBlob & model);
	
	void load();
	void update(ofxCvTrackedBlob & model);
	void draw(float ratioX, float ratioY);
	
	int getId();
	void setOrder(int order);
	
	ofPoint getCentroid();
	
private:
	
	int _id;
	int _order;
	ofRectangle _boundingRect;
	ofPoint	_centroid;

	ofColor _color;
};