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

void VideoCell::draw()
{
	float x = _centroid.x * Sensing::getInstance()->getRatioX();
	float y = _centroid.y * Sensing::getInstance()->getRatioY();
	
	x += Sensing::getInstance()->getDisplaceX();
	y += Sensing::getInstance()->getDisplaceY();
	
	// draw video (remember to bind before (done in cellscontroller))
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, &_texCoords[0]);
	ofQuad3D(x, y, 0, x + Sensing::getInstance()->getCellWidth(), y, 0, x + Sensing::getInstance()->getCellWidth(), y + Sensing::getInstance()->getCellHeight(), 0, x, y + Sensing::getInstance()->getCellHeight(), 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void VideoCell::drawDebug()
{
	float x = _centroid.x * Sensing::getInstance()->getRatioX();
	float y = _centroid.y * Sensing::getInstance()->getRatioY();
	
	x += Sensing::getInstance()->getDisplaceX();
	y += Sensing::getInstance()->getDisplaceY();
	
	ofSetColor(_color.r, _color.g, _color.b);
	ofRect(x, y, 10, 10);
	
	ofSetColor(255, 255, 255);
	
	string message = "Id: " + ofToString(_id, 0) + " Order: " + ofToString(_order, 0);
	
	ofDrawBitmapString(message, x, y);
}

/* Other Getter / Setters
 ___________________________________________________________ */

int VideoCell::getId()
{
	return _id;
}

ofPoint VideoCell::getCentroid()
{
	return _centroid;
}

void VideoCell::setOrder(int order)
{
	_order = order;
	
	// use order to set position in video texture
	
	int col = _order % NUM_COLS;
	int row = order / NUM_ROWS;
	
	int cellWidth = VIDEO_WIDTH / NUM_ROWS;
	int cellHeight = VIDEO_HEIGHT / NUM_COLS;
	
	setTextureRect(row * cellWidth, col * cellHeight, cellWidth , cellHeight);
}

void VideoCell::setTextureRect(float x, float y, int w, int h)
{
	_texCoords[0] = x;
	_texCoords[1] = y;
	
	_texCoords[2] = x + w;
	_texCoords[3] = y;
	
	_texCoords[4] = x + w;
	_texCoords[5] = y + h;
	
	_texCoords[6] = x;
	_texCoords[7] = y + h;
};
