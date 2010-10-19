#include "VideoCell.h"

/* Constructor
 ___________________________________________________________ */

VideoCell::VideoCell(int id)
{
	_id = id;
	
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

void VideoCell::update(float x, float y)
{	
	if(fabs(_pos.x - x) > MOVE_MARGIN || fabs(_pos.y - y) > MOVE_MARGIN)
	{
		_pos.x = x;
		_pos.y = y;
	}
}

/* Draw
 ___________________________________________________________ */

void VideoCell::draw(float ratioX, float ratioY)
{
	ofSetColor(_color.r, _color.g, _color.b);
	ofRect(_pos.x * ratioX, _pos.y * ratioY, 100, 100);
}

int VideoCell::getId()
{
	return _id;
}
