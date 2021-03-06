//
//  jzplib_detections.h
//  OPENCV_HOTSHOTS
//
//  Created by Zhiping Jiang on 14-7-18.
//
//

#ifndef __OPENCV_HOTSHOTS__jzplib_detections__
#define __OPENCV_HOTSHOTS__jzplib_detections__

#include <iostream>
#include <opencv2/opencv.hpp>
#include "jzplib_img.h"
#include "jzplib_draw.h"
#include "jzplib_bwOps.h"
#include "jzplib_math.h"
#include "skinColorDetection.h"
#include "GraphUtils.h"

using namespace std;
using namespace cv;


Rect haarPatternDetection(CascadeClassifier classifier, Mat image, int imageWidthforDetection, Rect parentRect);

Point findMassCenter_BinaryBiggestBlob(const Mat& image);
Point findEyeCenterByColorSegmentation(const Mat& image, float coordinateWeight= 0.4, int kmeansIterations = 3, int kmeansRepeats= 3, int blurSize= 5);

Mat calculateImageSymmetryScore(const Mat& image );

#endif /* defined(__OPENCV_HOTSHOTS__jzplib_detections__) */
