#include "CellsController.h"

/* Constructor
 ___________________________________________________________ */

CellsController::CellsController()
{
	updateRatio();
}

/* Load
 ___________________________________________________________ */

void CellsController::load()
{	

}

/* Update
 ___________________________________________________________ */

void CellsController::update(vector <ofxCvTrackedBlob> blobs)
{	
	updateRatio();
	
	for(int i = 0; i < blobs.size(); i++)
	{
		for(int j = 0; j < _cells.size(); j++)
		{
			if (blobs[i].id == _cells[j]->getId()) 
			{
				_cells[j]->setOrder(i);
				_cells[j]->update(blobs[i]);
				
				break;
			}
		}
	}
}

void CellsController::updateRatio()
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
	VideoCell * cell = new VideoCell(blob);
	cell->load();
	_cells.push_back(cell);
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


