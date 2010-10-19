#pragma once

#include "ofMain.h"
#include "Constants.h"

#define MOVE_MARGIN 0.5

class VideoCell
{
public:
	
	VideoCell(int id);
	
	void load();
	void update(float x, float y);
	void draw(float ratioX, float ratioY);
	
	int getId();
	
private:
	
	int _id;
	ofPoint _pos;
};