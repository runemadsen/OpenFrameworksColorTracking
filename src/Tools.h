#pragma once

#include "ofMain.h"

class Color
{
public:
	
	float hue, sat;
	ofxVec2f pos;
};

class SortObject
{
public:
	
	int id;
	ofPoint centroid;
};