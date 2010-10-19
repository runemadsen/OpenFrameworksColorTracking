#include "VideoCell.h"

/* Constructor
 ___________________________________________________________ */

VideoCell::VideoCell(int id)
{
	_id = id;
}

/* Load
 ___________________________________________________________ */

void VideoCell::load()
{	
	// load videos into Cell model
}

/* Update
 ___________________________________________________________ */

void VideoCell::update(int x, int y)
{	
	_pos.x = x * ( (float) ofGetWidth() / (float) VIDEO_WIDTH );
	_pos.y = y * ( (float) ofGetHeight() / (float) VIDEO_HEIGHT );
}

/* Draw
 ___________________________________________________________ */

void VideoCell::draw()
{
	ofSetColor(255, 0, 0);
	ofRect(_pos.x, _pos.y, 100, 100);
}

int VideoCell::getId()
{
	return _id;
}
