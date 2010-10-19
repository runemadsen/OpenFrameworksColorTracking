#include "CellsController.h"

/* Constructor
 ___________________________________________________________ */

CellsController::CellsController()
{
	_ratioX = (float) ofGetWidth() / (float) VIDEO_WIDTH;
	_ratioY = (float) ofGetHeight() / (float) VIDEO_HEIGHT;
}

/* Load
 ___________________________________________________________ */

void CellsController::load()
{	

}

/* Update
 ___________________________________________________________ */

void CellsController::update()
{	
	_ratioX = (float) ofGetWidth() / (float) VIDEO_WIDTH;
	_ratioY = (float) ofGetHeight() / (float) VIDEO_HEIGHT;
}

/* Draw
 ___________________________________________________________ */

void CellsController::draw()
{
	for(int i = 0; i < _cells.size(); i++)
	{
		_cells[i]->draw(_ratioX, _ratioY);
	}
}

/* Blob Events
 ___________________________________________________________ */


void CellsController::blobOn(ofxCvTrackedBlob& blob)
{
	VideoCell * cell = new VideoCell(blob.id);
	cell->update(blob.centroid.x, blob.centroid.y);
	_cells.push_back(cell);
}

void CellsController::blobMoved(ofxCvTrackedBlob& blob)
{
	for(int i = 0; i < _cells.size(); i++)
	{
		if (_cells[i]->getId() == blob.id) 
		{
			_cells[i]->update(blob.centroid.x, blob.centroid.y);
		}
	 }
}

void CellsController::blobOff(int blobid)
{
	for(int i = 0; i < _cells.size(); i++)
	{
		if (_cells[i]->getId() == blobid) 
		{
			_cells.erase (_cells.begin()+i);	
		}
	}
}


