#pragma once

#include "ofMain.h"
#include "Constants.h"

class VideoCell
{
public:
	
	VideoCell(int id);
	
	void load();
	void update(int x, int y);
	void draw();
	
	int getId();
	
private:
	
	int _id;
	ofPoint _pos;
};