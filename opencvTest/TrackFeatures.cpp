/*
 * TrackFeatures.cpp
 *
 *  Created on: 04-Apr-2015
 *      Author: pc
 */
#include "yawn.h"
#include "HaarCascadeObjectDetector.h"
#include "camshift_wrapper.h"

#include<iostream>
#include<stdio.h>

using namespace cv;
using namespace std;



//global variables //

const string DISPLAY_WINDOW = "SAFE DRIVE";
string face_cascade = "haarcascades/haarcascade_frontalface_alt.xml";
string eye_cascade = "haarcascades/haarcascade_eye_tree_eyeglasses.xml";
string mouth_cascade = "haarcascades/haarcascade_mcs_mouth.xml";
string nose_cascade = "haarcascades/haarcascade_mcs_nose.xml";


HaarCascadeObjectDetector faceDetector(face_cascade);
HaarCascadeObjectDetector eyeDetector(eye_cascade);
HaarCascadeObjectDetector mouthDetector(mouth_cascade);
HaarCascadeObjectDetector noseDetector(nose_cascade);

Tracker faceTracker;
Tracker l_eyeTracker;
Tracker r_eyeTracker;
Tracker mouthTracker;
Mat videoFrame,grayFrame;
Rect faceRect,l_eyeRect,r_eyeRect,mouthRect,noseRect;
VideoCapture cap;


void exitProgram(int code)
{
		cout<<"\n Exiting ..."; cout.flush();
        // Release resources allocated in this file
        cv::destroyAllWindows();
        cap.release();
        // Release resources allocated in other project files
        faceTracker.releaseTracker();
        l_eyeTracker.releaseTracker();
        r_eyeTracker.releaseTracker();
        mouthTracker.releaseTracker();
        exit(code);

 }

int initAll()
{
	int web_cam=0;


	cap.open(web_cam);

	if(!cap.isOpened())
	{
		//wait
		cout<<"Web Cam initialisation failed.";
		return 0;
	}

	//read the next video frame
	cap>>videoFrame;

	if(videoFrame.empty())
	{
		cout<<"End Of Frame!!";
		return 0;

	}
	cvtColor(videoFrame, grayFrame , CV_BGR2GRAY);

	//create Trackers
	if(	!(	faceTracker.createTracker(videoFrame) 	&
			l_eyeTracker.createTracker(videoFrame)	&
			r_eyeTracker.createTracker(videoFrame)	&
			mouthTracker.createTracker(videoFrame)
		  )
	  ){
		return 0;
	}

	namedWindow(DISPLAY_WINDOW);
	cout<<"initall succeeded";
return 1;
}

bool detectFeatures()
{
	Mat face_roi,mouth_roi;
	Mat lower_face;
	bool det_fet = false;
	vector<Rect> roi;
	Point2i * faceRectOffset=0; //top left Point of faceRect for eyeRect offset
	Point2i * lowerFaceOffset=0; //top left point of lower_face for mouthRect offset

	det_fet = faceDetector.detect(grayFrame, roi);


	if( det_fet ) //face detected
	{
		faceRect=roi[0];
		faceRectOffset=new Point2i(faceRect.x,faceRect.y);
		face_roi=grayFrame(faceRect);
		roi.clear();


	//if face detected and two eyes detected inside faceRect



	eyeDetector.setOptions(CV_HAAR_SCALE_IMAGE);
	det_fet = 	det_fet 						  &&
				(eyeDetector.detect(face_roi,roi));//&
				//(roi.size()==2);
	det_fet = det_fet && (roi.size()==2);

		l_eyeRect=roi[0] + *faceRectOffset;
		r_eyeRect=roi[1] + *faceRectOffset;
		roi.clear();



	noseDetector.setOptions(CV_HAAR_SCALE_IMAGE);
	det_fet = det_fet && noseDetector.detect(face_roi,roi);
	noseRect = roi[0]+ *faceRectOffset;
	roi.clear();
	// prepare lower face region to search mouth


	if(mouthRect.x==0)
		{
	cout<<"\ninside face_roi"; cout.flush();
		int mid_row = face_roi.rows*0.70;
		int end_row	=	face_roi.rows-1;

		//extract lower face region
		lower_face = face_roi(Range(mid_row,end_row),Range::all());
		imshow("lowface",lower_face);
		lowerFaceOffset=new Point2i(faceRect.x,faceRect.y+mid_row);



	//if face ,2 eyes and mouth detected in lower face region

	det_fet = det_fet && mouthDetector.detect(lower_face,roi);
	mouthRect=roi[0]+ *lowerFaceOffset;
	}
	}
/*det_fet = det_fet &&  l_eyeRect.x < mouthRect.x &&
					  mouthRect.x < r_eyeRect.x+r_eyeRect.width;*/
	cout<<"\n feat detection over ? " <<det_fet ; cout.flush();
return det_fet;
}

void capNextFrame()
{
	cap >> videoFrame;
	if(videoFrame.empty()){ exitProgram(-1);}
	cvtColor(videoFrame, grayFrame, CV_BGR2GRAY);
	equalizeHist(grayFrame, grayFrame);
}

void displayFeatures(Mat &frame , Rect fetRect , Scalar color=CV_RGB(255,0,0))
{


	if(fetRect.area()!=0)
		{
			int thickness=3;
			cv::rectangle(frame, fetRect, color, thickness);
		}


}


void displayFeatures(vector<RotatedRect> & rrect)
{
	//Scalar color[]={CV_RGB(255,0,0),CV_RGB(0,255,0),CV_RGB(0,255,0),CV_RGB(0,0,255)};
Scalar red=CV_RGB(255,0,0);
	int thickness=3;
	//display the rotated rects as ellipse
	for(size_t i=0;i<rrect.size();i++)
	{

		//Scalar c=color[i];
		ellipse(videoFrame,rrect[i],red,thickness);

	}
}

void startTrackers()
{
	faceTracker.startTracking(videoFrame,faceRect);
	l_eyeTracker.startTracking(videoFrame,l_eyeRect);
	r_eyeTracker.startTracking(videoFrame,r_eyeRect);
	mouthTracker.startTracking(videoFrame,mouthRect);

}


vector<RotatedRect>  trackFeatures(){
	vector<RotatedRect> ftrackingRects(4); //feature tracking rects

	RotatedRect rfaceRect=faceTracker.track(videoFrame);
	RotatedRect rl_eyeRect=l_eyeTracker.track(videoFrame);
	RotatedRect rr_eyefaceRect=r_eyeTracker.track(videoFrame);
	RotatedRect rmouthRect=mouthTracker.track(videoFrame);

	ftrackingRects.push_back(rfaceRect);
	ftrackingRects.push_back(rl_eyeRect);
	ftrackingRects.push_back(rr_eyefaceRect);
	ftrackingRects.push_back(rmouthRect);


	return ftrackingRects;
}

int main()
{
	vector<RotatedRect> ftrackingRects; //feature tracking rects
double mouth_height;


	if(!initAll())
	{
		cout<<"Exiting Program";
		exitProgram(-1);
	}
	bool fet_det=false, fet_track=false;
	while(true)
	{


		if(true)
		{

			fet_det	=	detectFeatures();

			if(fet_det && !fet_track) //all features detected
					{
						cout<<"\n feature detected. Starting Tracking";
						startTrackers();
					}

			if(fet_det)
			{

				double l_eyeCenter=l_eyeRect.x+l_eyeRect.width*0.5;
				double r_eyeCenter=r_eyeRect.x+r_eyeRect.width*0.5;
				double mouth_y = noseRect.y+noseRect.height+10;
				mouthRect.x=l_eyeCenter;
				mouthRect.y=mouth_y;

				mouthRect.width=norm(r_eyeCenter-l_eyeCenter);
				mouth_height=500;

			}

			displayFeatures(videoFrame,faceRect,CV_RGB(255,0,0));
			displayFeatures(videoFrame,l_eyeRect,CV_RGB(0,255,0));
			displayFeatures(videoFrame,r_eyeRect,CV_RGB(0,255,0));
			displayFeatures(videoFrame,mouthRect,CV_RGB(0,0,255));
			displayFeatures(videoFrame,noseRect,CV_RGB(0,0,0));



			faceRect.height  = faceRect.width=0;
			l_eyeRect.height = l_eyeRect.width=0;
			r_eyeRect.height = r_eyeRect.width=0;
			//mouthRect.height = mouthRect.width=0;


		}

		imshow(DISPLAY_WINDOW,videoFrame);


		capNextFrame();

		if(!fet_det & false)
		{
			try{
			ftrackingRects=trackFeatures();

			displayFeatures(ftrackingRects);
			fet_track=true;
			}catch(exception &e)
			{
				cout<<e.what();
				fet_det=false;
				fet_track=false;
			}

		}



		int key=waitKey(100);
		if(key==27)	break;


	}
	exitProgram(1);
return 1;
}
