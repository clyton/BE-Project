#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


int main( int argc, const char** argv )
{
	vector<Rect> v;

	v.push_back(Rect(10,10,40,40));

	v.push_back(Rect(00,10,40,40));

	cout<<v.size()<<endl;

	v.clear();

	cout<<v.size();

}

