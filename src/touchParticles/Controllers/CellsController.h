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
	void update(vector <ofxCvTrackedBlob> blobs);
	void draw();

	void blobOn(ofxCvTrackedBlob& blob);
	void blobOff(int blobid);
	
private:
	
	void updateRatio();
	
	vector <VideoCell *> _cells;
	
	float _ratioX;
	float _ratioY;
};