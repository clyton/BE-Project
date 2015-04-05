/*
 * HaarCascadeObjectDetector.h
 *
 *  Created on: 01-Mar-2015
 *      Author: pc
 */

#ifndef HAARCASCADEOBJECTDETECTOR_H_
#define HAARCASCADEOBJECTDETECTOR_H_

#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "ObjectDetector.h"

#define DEFAULT_SEARCH_SCALE  1.3
#define DEFAULT_SCALE_FACTOR  1.1
#define DEFAULT_MIN_NEIGHBORS 2
#define DEFAULT_OPTS          CV_HAAR_FIND_BIGGEST_OBJECT
#define DEFAULT_MIN_SIZE      cv::Size(30, 30)

class HaarCascadeObjectDetector : public ObjectDetector
{
 public:
  HaarCascadeObjectDetector(std::string fname,
                            double scale               = DEFAULT_SEARCH_SCALE,
                            double factor              = DEFAULT_SCALE_FACTOR,
                            unsigned int min_neighbors = DEFAULT_MIN_NEIGHBORS,
                            unsigned int opts          = DEFAULT_OPTS,
                            cv::Size min_size          = DEFAULT_MIN_SIZE);

  HaarCascadeObjectDetector(cv::CascadeClassifier cascade,
                            double scale               = DEFAULT_SEARCH_SCALE,
                            double factor              = DEFAULT_SCALE_FACTOR,
                            unsigned int min_neighbors = DEFAULT_MIN_NEIGHBORS,
                            unsigned int opts          = DEFAULT_OPTS,
                            cv::Size min_size          = DEFAULT_MIN_SIZE);

  virtual ~HaarCascadeObjectDetector();

  int detect(cv::Mat image, std::vector<cv::Rect>& objects, cv::Rect ROI = cv::Rect());

  void setImageScale(double scale);
  void setScaleFactor(double factor);
  void setMinNeighbors(unsigned int n);
  void setOptions(unsigned int opts);
  void setMinSize(cv::Size min_size);

 private:
  cv::CascadeClassifier cascade;

  /*OpenCV Cascade search params*/
  double       search_scale;
  double       scale_factor;
  unsigned int min_neighbors;
  unsigned int opts;
  cv::Size     min_size;
};



#endif /* HAARCASCADEOBJECTDETECTOR_H_ */
