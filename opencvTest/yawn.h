/*
 * yawn.h
 *
 *  Created on: 10-Mar-2015
 *      Author: pc
 */

#ifndef YAWN_H_
#define YAWN_H_


#include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"

#define BINARY_THRESH 160
#define CONTOUR_AREA_THRESH 300

int getMaxArea(cv::Mat &mouth_roi);


#endif /* YAWN_H_ */
