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
				_cells[j]->update(blobs[i]);
				
				break;
			}
		}
	}
}

void CellsController::resetOrder()
{
	vector <SortObject> objects;
	
	for(int i = 0; i < _cells.size(); i++)
	{
		SortObject o;
		o.centroid = _cells[i]->getCentroid();
		o.id = _cells[i]->getId();
		objects.push_back(o);
	}
	
	if(objects.size() != GRID_SIZE)
	{
		cout << "You are trying to order the grid, but there are " << objects.size() << " blobs detected" << endl;
	}
	
	// sort by y
	std::sort(objects.begin(), objects.end(), CellsController::ysorter());
	
	// sort by x
	std::sort(objects.begin(), objects.begin() + 2, CellsController::xsorter());
	std::sort(objects.begin() + 3, objects.begin() + 5, CellsController::xsorter());
	std::sort(objects.begin() + 6, objects.begin() + 8, CellsController::xsorter());
	
	for(int i = 0; i < objects.size(); i++)
	{
		for(int j = 0; j < _cells.size(); j++)
		{
			if(objects[i].id == _cells[j]->getId())
			{
				_cells[j]->setOrder(i + 1);
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


