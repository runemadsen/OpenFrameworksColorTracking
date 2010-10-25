#include "Sensing.h"

/* Singleton stuff
 ___________________________________________________________ */

Sensing * Sensing::m_pInstance = NULL;

Sensing * Sensing::getInstance()
{
	if (!m_pInstance)   // Only allow one instance of class to be generated.
		m_pInstance = new Sensing;
	
	return m_pInstance;
}

/* Constructor
 ___________________________________________________________ */

Sensing::Sensing()
{
	threshold = 0;
	blurAmount = 0;
	area = 100;
	hueMargin = 15;
	satMarginLow = 50;
	satMarginHigh = 170;
	
	cellWidth = 100;
	cellHeight = 100;
	cellMarginX = 0;
	cellMarginY = 0;
	
	ratioX = 2.54;
	ratioY = 2.59;
	displaceX = 10;
	displaceY = -15;
	
	show = false;
	showGrabScreen = false;
	maskToggle = false;
	debugToggle = false;
	
	trackColor.hue = 80;
	trackColor.sat = 135;
	
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
	gui.addSlider("Hue Margin", hueMargin , 0, 200);
	gui.addSlider("Sat Margin Low", satMarginLow , 0, 200);
	gui.addSlider("Sat Margin High", satMarginHigh , 0, 500);
	gui.addToggle("Mask", maskToggle);
	gui.addToggle("Debug", debugToggle);
	gui.addSlider("Cell Width", cellWidth , 50, 500);
	gui.addSlider("Cell Height", cellHeight , 50, 500);
	
	gui.addSlider("ratioX", ratioX , 0.5, 6.0);
	gui.addSlider("ratioY", ratioY , 0.5, 6.0);
	gui.addSlider("Displace Origin X", displaceX , -800, 800);
	gui.addSlider("Displace Origin Y", displaceY , -800, 800);
	gui.show();
	
	for (int i=0; i<VIDEO_WIDTH*VIDEO_HEIGHT; i++) 
	{
		if (maskPixels[i]!=0){
			maskPixels[i]==1;			
		} 
	}
	
	vidGrabber.setDeviceID(6);
	vidGrabber.initGrabber(VIDEO_WIDTH, VIDEO_HEIGHT );
}

/* Set listener
 ___________________________________________________________ */

void Sensing::setListener(ofxCvBlobListener * listener)
{
	blobTracker.setListener(listener);
}

/* Update
 ___________________________________________________________ */

void Sensing::update()
{
	vidGrabber.grabFrame();
	
	if( vidGrabber.isFrameNew() ) 
	{
        colorImg = vidGrabber.getPixels();
        colorImg.mirror(false, false );
		
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

/* Draw
 ___________________________________________________________ */

void Sensing::draw()
{	
	if (show) 
	{
		if(showGrabScreen)
		{
			ofSetColor(255, 255, 255);
			colorImg.draw(0, 0);
		}
		else 
		{
			gui.draw();
			
			outputTexture.begin();
			ofSetColor( 0xffffff );
			colorImg.draw(0, 0);
			blobTracker.draw(0, 0);
			outputTexture.end();
		}
	}
}

/* Grab color fro video
 ___________________________________________________________ */

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

/* Getter / Setter
 ___________________________________________________________ */

vector <ofxCvTrackedBlob> Sensing::getBlobs()
{
	return blobTracker.blobs;
}

bool Sensing::debug()
{
	return debugToggle;
}

int Sensing::getCellWidth()
{
	return cellWidth;
}

int Sensing::getCellHeight()
{
	return cellHeight;
}

void Sensing::calibrateVar(string variable, float addNum)
{
	
	if(variable == "x")				displaceX += addNum;
	else if(variable == "y")		displaceY += addNum;
	else if(variable == "ratiox")	ratioX += addNum;
	else if(variable == "ratioy")	ratioY += addNum;
	else if(variable == "cellwidth")	cellWidth += addNum;
	else if(variable == "cellheight")	cellHeight += addNum;
}

