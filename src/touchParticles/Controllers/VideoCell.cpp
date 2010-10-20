#include "VideoCell.h"

/* Constructor
 ___________________________________________________________ */

VideoCell::VideoCell(ofxCvTrackedBlob & model)
{
	_id = model.id;
	_boundingRect = model.boundingRect;
	_centroid = model.centroid;
	
	_color.r = ofRandom(0, 255);
	_color.g = ofRandom(0, 255);
	_color.b = ofRandom(0, 255);
}

/* Load
 ___________________________________________________________ */

void VideoCell::load()
{	
	// load videos into Cell model
}

/* Update
 ___________________________________________________________ */

void VideoCell::update(ofxCvTrackedBlob & model)
{	
	if(fabs(_centroid.x - model.centroid.x) > MOVE_MARGIN || fabs(_centroid.y - model.centroid.y) > MOVE_MARGIN)
	{
		_boundingRect = model.boundingRect;
		_centroid = model.centroid;
	}
}

/* Draw
 ___________________________________________________________ */

void VideoCell::draw(float ratioX, float ratioY)
{
	ofSetColor(_color.r, _color.g, _color.b);
	ofRect(_centroid.x * ratioX, _centroid.y * ratioY, 100, 100);
	
	if(DEBUG)
	{		
		ofSetColor(255, 255, 255);
		
		string message = "Id: " + ofToString(_id, 0) + " Order: " + ofToString(_order, 0);
		
		ofDrawBitmapString(message, _centroid.x * ratioX, _centroid.y * ratioY);
	}
}

int VideoCell::getId()
{
	return _id;
}

void VideoCell::setOrder(int order)
{
	_order = order;
}
