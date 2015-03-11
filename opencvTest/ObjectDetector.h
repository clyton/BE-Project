/*
 * ObjectDetector.h
 *
 *  Created on: 01-Mar-2015
 *      Author: pc
 */

#ifndef OBJECTDETECTOR_H_
#define OBJECTDETECTOR_H_



#include <vector>
#include <opencv2/imgproc/imgproc.hpp>

class ObjectDetector
{
 public:
  virtual int detect(cv::Mat image, std::vector<cv::Rect>& objects, cv::Rect ROI = cv::Rect()) = 0;

};

#endif /* OBJECTDETECTOR_H_ */
