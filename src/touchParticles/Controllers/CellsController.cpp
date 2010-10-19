#include "CellsController.h"

/* Constructor
 ___________________________________________________________ */

CellsController::CellsController()
{
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

}

/* Draw
 ___________________________________________________________ */

void CellsController::draw()
{
	for(int i = 0; i < cells.size(); i++)
	{
		cells[i]->draw();
	}
}

/* Touch Events
 ___________________________________________________________ */


void CellsController::blobOn(int blobid, vector <ofPoint> pts, ofPoint centroid)
{
	VideoCell * cell = new VideoCell(blobid);
	cell->update(centroid.x, centroid.y); // remember to scale
	cells.push_back(cell);
}

void CellsController::blobMoved(int blobid, vector <ofPoint> pts, ofPoint centroid)
{
	for(int i = 0; i < cells.size(); i++)
	{
		if (cells[i]->getId() == blobid) 
		{
			cells[i]->update(centroid.x, centroid.y);
		}
	 }
}

void CellsController::blobOff(int blobid)
{
	for(int i = 0; i < cells.size(); i++)
	{
		if (cells[i]->getId() == blobid) 
		{
			cells.erase (cells.begin()+i);	
		}
	}
}


