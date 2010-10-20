#include "testApp.h"

void testApp::setup() 
{
	ofSetFrameRate(60);
	ofBackground( 0, 0, 0 );

	Sensing::getInstance()->setListener(this);
	
	cells = new CellsController();
}

void testApp::update() 
{	
	Sensing::getInstance()->update();
	
	cells->update(Sensing::getInstance()->blobTracker.blobs);
}

void testApp::draw() 
{	
	cells->draw();
	
	Sensing::getInstance()->draw();
	
	if(Sensing::getInstance()->debug())
	{
		string fpsStr = "frame rate: "+ofToString(ofGetFrameRate(), 2);
		
		ofSetColor(255, 255, 255);
		
		ofDrawBitmapString(fpsStr, 10, 10);
	}
}

void testApp::keyPressed( int key ) 
{
    if (key =='f' || key=='F') 
	{
		ofToggleFullscreen();
	} 
	else if (key == 'a')
	{
		cells->assignBlobsToCells();
	}
	else if (key == 't')
	{
		Sensing::getInstance()->showGrabScreen = !Sensing::getInstance()->showGrabScreen;
	}
	else if (key ==' ')
	{
		Sensing::getInstance()->show =! Sensing::getInstance()->show;
	}
}

void testApp::mouseMoved( int x, int y ) {}
void testApp::mouseDragged( int x, int y, int button ) {}
void testApp::mousePressed( int x, int y, int button ) 
{
	Sensing::getInstance()->grabColorFromVideo(x, y);
}

void testApp::mouseReleased() {}


void testApp::blobOn( int x, int y, int id, int order ) 
{		
	cells->blobOn(Sensing::getInstance()->blobTracker.getById(id));	
}

void testApp::blobMoved( int x, int y, int id, int order)
{
	
}

void testApp::blobOff( int x, int y, int id, int order ) 
{	
	cells->blobOff(id);
}



