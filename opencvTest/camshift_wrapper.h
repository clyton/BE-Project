/*
 * camshift_wrapper.h
 *
 *  Created on: 30-Mar-2015
 *      Author: pc
 */



#ifndef __SIMPLE_CAMSHIFT_WRAPPER_H
#define __SIMPLE_CAMSHIFT_WRAPPER_H

#include "opencv/cv.h"
#include <opencv2/core/core.hpp>

using namespace cv;

class Tracker{



public:
	int   nHistBins ;                 // number of histogram bins
	float rangesArr[2];          // histogram range
	int vmin , vmax , smin ; // limits for calculating hue


	// File-level variables
	IplImage * pHSVImg  ;// the input image converted to HSV color mode
	IplImage * pHueImg  ; // the Hue channel of the HSV image
	IplImage * pMask    ; // this image is used for masking pixels
	IplImage * pProbImg ; // the face probability estimates for each pixel
	CvHistogram * pHist ; // histogram of hue in the original face image

	CvRect prevFaceRect;  // location of face in previous frame
	CvBox2D faceBox;      // current face-location estimate


	int nFrames ;

	Tracker();
	~Tracker();



// Main Control functions
	int     createTracker(const IplImage * pImg);
	void    releaseTracker();
	void    startTracking(IplImage * pImg, CvRect * pRect);
	CvBox2D track(IplImage *);

	//helper function
	void updateHueImage(const IplImage * pImg);

	// Parameter settings
	void setVmin(int vmin);
	void setSmin(int smin);

	//Main control functions with c++ Interface
	int 	createTracker(const Mat pImg);
	void	startTracking(Mat pImg, Rect pRect );
	RotatedRect track(Mat pImg);



};


#endif



/* CAMSHIFT_WRAPPER_H_ */
