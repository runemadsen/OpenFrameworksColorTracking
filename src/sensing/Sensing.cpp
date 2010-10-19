#include "Sensing.h"

Sensing::Sensing(ofxCvBlobListener * listener)
{
	disabled = true;
	threshold = 0;
	blurAmount = 0;
	area = 100;
	show = false;
	showGrabScreen = false;
	maskToggle = false;
	vidGrabber.initGrabber( VIDEO_WIDTH, VIDEO_HEIGHT );
	
	trackColor.hue = 165;
	trackColor.sat = 171;
	
	colorImg.allocate( VIDEO_WIDTH, VIDEO_HEIGHT );
	colorImgHSV.allocate(VIDEO_WIDTH, VIDEO_HEIGHT);  
	
	hueImg.allocate(VIDEO_WIDTH, VIDEO_HEIGHT);
    satImg.allocate(VIDEO_WIDTH, VIDEO_HEIGHT);
    briImg.allocate(VIDEO_WIDTH, VIDEO_HEIGHT);
	
	colorTrackedPixelsRed = new unsigned char [VIDEO_WIDTH * VIDEO_HEIGHT]; 
	
	grayImg.allocate( VIDEO_WIDTH, VIDEO_HEIGHT );
	outputTexture.allocate(VIDEO_WIDTH, VIDEO_HEIGHT, GL_RGB);
	
	mask.loadImage("mask.png");
	mask.setImageType(OF_IMAGE_GRAYSCALE);
	maskPixels = mask.getPixels();
	
	colorTrackedPixelsRed = new unsigned char [VIDEO_WIDTH * VIDEO_HEIGHT];
	
    trackedTextureRed.allocate(VIDEO_WIDTH, VIDEO_HEIGHT, GL_LUMINANCE);
	
	gui.addTitle("Input");
	gui.addContent("Input", outputTexture);
	gui.addSlider("Threshold", threshold , 0.0, 255);
	gui.addSlider("Bluring", blurAmount , 0, 40);
	gui.addContent("Difference", grayImg);
	gui.addSlider("Area",area,10,6000);	
	gui.addToggle("Mask", maskToggle);
	gui.addToggle("Disabled", disabled);
	gui.show();
	
	for (int i=0; i<VIDEO_WIDTH*VIDEO_HEIGHT; i++) 
	{
		if (maskPixels[i]!=0){
			maskPixels[i]==1;			
		} 
	}
	
	blobTracker.setListener(listener);
}

void Sensing::update()
{
	vidGrabber.grabFrame();
	
	if( vidGrabber.isFrameNew() ) 
	{
        colorImg = vidGrabber.getPixels();
        colorImg.mirror( false, true );
		
		colorImgHSV = colorImg;                                                 
		colorImgHSV.convertRgbToHsv();                                          
		colorImgHSV.convertToGrayscalePlanarImages(hueImg, satImg, briImg);
		
		// Because of bug
		hueImg.flagImageChanged(); 
		satImg.flagImageChanged();
		briImg.flagImageChanged();
        
		// grayImg should get the red image
		
		unsigned char * huePixels = hueImg.getPixels();                         
		unsigned char * satPixels = satImg.getPixels();                        
		
		for (int i = 0; i < VIDEO_WIDTH * VIDEO_HEIGHT; i++)
		{                                          
			if ((huePixels[i] >= trackColor.hue - 12 && huePixels[i] <= trackColor.hue + 12) &&    
				(satPixels[i] >= trackColor.sat - 24 && satPixels[i] <= trackColor.sat + 200))
			{    
				colorTrackedPixelsRed[i] = 255;                                      
			} 
			else 
			{
				colorTrackedPixelsRed[i] = 0;                                        
			}
		}
		
		grayImg.setFromPixels(colorTrackedPixelsRed, VIDEO_WIDTH, VIDEO_HEIGHT);   
		
        grayImg.blur( blurAmount );
        grayImg.threshold( threshold );
		grayPixels = grayImg.getPixels();
		
		if (maskToggle) 
		{
			for (int i=0; i<VIDEO_WIDTH*VIDEO_HEIGHT; i++) 
			{
				grayPixels[i]=maskPixels[i]&&grayPixels[i]; 
			}
			
			grayImg.setFromPixels(grayPixels, VIDEO_WIDTH,VIDEO_HEIGHT);
		}
        
		//findContures( img, minSize, maxSize, nMax, inner contours yes/no )
        contourFinder.findContours( grayImg, area, 300000, 20, false);
        blobTracker.trackBlobs( contourFinder.blobs );
    }
}

void Sensing::draw()
{	
	if (show) 
	{
		if(showGrabScreen)
		{
			colorImg.draw(0, 0);
		}
		else 
		{
			gui.draw();
			
			outputTexture.begin();
			ofSetColor( 0xffffff );
			colorImg.draw( 0,0 );
			blobTracker.draw(0, 0);
			outputTexture.end();
		}
	}
}

void Sensing::grabColorFromVideo(int x, int y)
{
	if(showGrabScreen)
	{
		unsigned char * huePixels = hueImg.getPixels();  
		unsigned char * satPixels = satImg.getPixels();
		
		x = MIN(x,hueImg.width-1);
		y = MIN(y,hueImg.height-1);
		
		trackColor.hue = huePixels[x+(y*hueImg.width)];  
		trackColor.sat = satPixels[x+(y*satImg.width)]; 
		
		cout << "New Color > Hue: " << trackColor.hue << " Sat: " << trackColor.sat << endl ;
	}
}

vector <ofxCvTrackedBlob> Sensing::getBlobs()
{
	return blobTracker.blobs;
}

