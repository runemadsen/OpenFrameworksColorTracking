#include "testApp.h"

void testApp::setup() 
{
	ofSetFrameRate(60);
	ofBackground( 0, 0, 0 );
	
	sensing = new Sensing(this);
	
	cells = new CellsController();
	cells->load();
}

void testApp::update() 
{	
	sensing->update();
	
	for(int i = 0; i < sensing->blobTracker.blobs.size(); i++)
	{
		// if this ever fucks up, it's because ids arent the same as vector index
		ofxCvTrackedBlob& blob = sensing->blobTracker.blobs[i];
		cells->blobMoved(blob.id, blob.pts, blob.centroid);
	}
	
	cells->update();
}

void testApp::draw() 
{	
	sensing->draw();
	cells->draw();
}

void testApp::keyPressed( int key ) 
{
    if (key =='f' || key=='F') 
	{
		ofToggleFullscreen();
	} 
	else if (key == 't')
	{
		sensing->showGrabScreen = !sensing->showGrabScreen;
	}
	else if (key ==' ')
	{
		sensing->show =! sensing->show;
	}
}

void testApp::mouseMoved( int x, int y ) {}
void testApp::mouseDragged( int x, int y, int button ) {}
void testApp::mousePressed( int x, int y, int button ) 
{
	sensing->grabColorFromVideo(x, y);
}

void testApp::mouseReleased() {}


void testApp::blobOn( int x, int y, int id, int order ) 
{
	ofxCvTrackedBlob blob = sensing->blobTracker.getById(id);
		
	cells->blobOn(blob.id, blob.pts, blob.centroid);	
}

void testApp::blobMoved( int x, int y, int id, int order)
{
	
}
void testApp::blobOff( int x, int y, int id, int order ) 
{	
	cells->blobOff(id);
}



