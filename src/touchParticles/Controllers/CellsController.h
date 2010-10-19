#pragma once

#include "ofMain.h"
#include "ofxVec2f.h"
#include "Constants.h"
#include "VideoCell.h"
#include "Tools.h"
#include "ofxCvTrackedBlob.h"

class CellsController
{
public:
	
	CellsController();
	
	void load();
	void update();
	void draw();
	
	void blobMoved(ofxCvTrackedBlob& blob);
	void blobOn(ofxCvTrackedBlob& blob);
	void blobOff(int blobid);
	
private:
	
	vector <VideoCell *> _cells;
	
	float _ratioX;
	float _ratioY;
};