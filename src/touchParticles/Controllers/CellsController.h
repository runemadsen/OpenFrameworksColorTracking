#pragma once

#include "ofMain.h"
#include "TouchController.h"
#include "ofxVec2f.h"
#include "Constants.h"
#include "VideoCell.h"

class CellsController
{
public:
	
	CellsController();
	
	void load();
	void update();
	void draw();
	
	void blobMoved(int blobid, vector <ofPoint> pts, ofPoint centroid);
	void blobOn(int blobid, vector <ofPoint> pts, ofPoint centroid);
	void blobOff(int blobid);
	
private:
	
	vector <VideoCell *> cells;
};