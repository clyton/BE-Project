/*
 * facedet.h
 *
 *  Created on: 30-Mar-2015
 *      Author: pc
 */

#ifndef FACEDET_H_
#define FACEDET_H_



int      initFaceDet(const char * haarCascadePath);
void     closeFaceDet();
CvRect * detectFace(IplImage * pImg);
int detectFaces(IplImage * pImg,CvSeq** pRects);

#endif /* FACEDET_H_ */
