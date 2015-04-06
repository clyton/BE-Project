/*
 * hello.cpp
 *
 *  Created on: 06-Apr-2015
 *      Author: pc
 */

#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;
int main()
{
	Mat img= imread("aloma1.jpg");
	CascadeClassifier mouth("haarcascades/haarcascade_mcs_mouth.xml");
	vector<Rect> rmouth;

	mouth.detectMultiScale(img,rmouth,CV_HAAR_FIND_BIGGEST_OBJECT);
	rectangle(img,rmouth[0],CV_RGB(255,0,0),3);
	cout<<rmouth.size(); cout.flush();
	Mat mouthimg= img(rmouth[0]);

	Mat mouthResized;
try{
	Size s=img.size();
	cv::resize(mouthimg,mouthResized,s);
}
catch(exception &e)
{
cout<<"resize method";
}
	try {
		imshow("img",img);
		imshow("imgMouth",mouthResized);
	} catch (exception & e) {
		cout<<"imread";
	}

	waitKey(0);

	return 1;
}



