#pragma once

#include "ofMain.h"
#include "Constants.h"
#include "ofxCvTrackedBlob.h"
#include "ofQuad.h"
#include "Sensing.h"

#define MOVE_MARGIN 0.5

class VideoCell
{
public:
	
	VideoCell(ofxCvTrackedBlob & model);
	
	void update(ofxCvTrackedBlob & model);
	void draw(float ratioX, float ratioY);
	void drawDebug(float ratioX, float ratioY);
	
	int getId();
	void setOrder(int order);
	
	ofPoint getCentroid();
	
private:
	
	int _id;
	int _order;
	ofColor _color;
	
	float _texCoords[8];
	
	// blob
	ofRectangle _boundingRect;
	ofPoint	_centroid;
	
	void setTextureRect(float x, float y, int w, int h);
};