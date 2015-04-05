/*
 * capture.h
 *
 *  Created on: 30-Mar-2015
 *      Author: pc
 */

#ifndef CAPTURE_H_
#define CAPTURE_H_


int  initCapture(bool isUseCam = true,int CAM_ID = 0);
void closeCapture();
IplImage * nextVideoFrame();


#endif /* CAPTURE_H_ */
