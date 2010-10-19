#include "Sensing.h"

Sensing::Sensing(ofxCvBlobListener * listener)
{
	threshold = 0;
	blurAmount = 0;
	area = 100;
	hueMargin = 12;
	satMarginLow = 24;
	satMarginHigh = 200;
	
	disabled = true;
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
	
	grayPixels = new unsigned char [VIDEO_WIDTH * VIDEO_HEIGHT]; 
	
	grayImg.allocate( VIDEO_WIDTH, VIDEO_HEIGHT );
	outputTexture.allocate(VIDEO_WIDTH, VIDEO_HEIGHT, GL_RGB);
	
	mask.loadImage("mask.png");
	mask.setImageType(OF_IMAGE_GRAYSCALE);
	maskPixels = mask.getPixels();
	
    trackedTextureRed.allocate(VIDEO_WIDTH, VIDEO_HEIGHT, GL_LUMINANCE);
	
	gui.addTitle("Input");
	gui.addContent("Input", outputTexture);
	gui.addSlider("Threshold", threshold , 0.0, 255);
	gui.addSlider("Bluring", blurAmount , 0, 40);
	gui.addContent("Difference", grayImg);
	gui.addSlider("Area",area,10,6000);	
	gui.addSlider("Hue Margin", hueMargin , 0, 40);
	gui.addSlider("Sat Margin Low", satMarginLow , 0, 40);
	gui.addSlider("Sat Margin High", satMarginHigh , 0, 500);
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
			if ((huePixels[i] >= trackColor.hue - hueMargin && huePixels[i] <= trackColor.hue + hueMargin) &&    
				(satPixels[i] >= trackColor.sat - satMarginLow && satPixels[i] <= trackColor.sat + satMarginHigh))
			{    
				grayPixels[i] = 255;                                      
			} 
			else 
			{
				grayPixels[i] = 0;                                        
			}
		}
		
		if (maskToggle) 
		{
			for (int i=0; i<VIDEO_WIDTH*VIDEO_HEIGHT; i++) 
			{
				grayPixels[i]=maskPixels[i]&&grayPixels[i]; 
			}
		}
		
		grayImg.setFromPixels(grayPixels, VIDEO_WIDTH,VIDEO_HEIGHT);
		
		grayImg.blur( blurAmount );
        grayImg.threshold( threshold );
        
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

