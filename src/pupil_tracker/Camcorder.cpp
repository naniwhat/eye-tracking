//
//  Camcorder.cpp
//  OPENCV_HOTSHOTS
//
//  Created by Zhiping Jiang on 14-7-18.
//
//

#include <jzp_lib/jzplib_all.h>

#include <boost/lexical_cast.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/thread.hpp"

using namespace boost::posix_time;
// Code for capture thread
void captureFunc(Mat *frame, VideoCapture *capture){
    //loop infinitely
    for(;;){
		//capture from webcame to Mat frame
		captureImage((*capture), (*frame));
	}
}

//main
int main (int argc, char *argv[])
{
	//vars
	time_duration td, td1;
	ptime nextFrameTimestamp, currentFrameTimestamp, initialLoopTimestamp, finalLoopTimestamp;
	int delayFound = 0;
	int totalDelay= 0;
    
	// initialize capture on default source
	VideoCapture capture(0);
    
	// set framerate to record and capture at
	int framerate = 15;
    
	// Get the properties from the camera
	double width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	double height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    
	// print camera frame size
	cout << "Camera properties\n";
	cout << "width = " << width << endl <<"height = "<< height << endl;
    
	// Create a matrix to keep the retrieved frame
	Mat frame;
    
	// Create the video writer
	VideoWriter video("/Users/ZhipingJiang/capture.avi",CV_FOURCC('M','P','4','V'), framerate, cvSize((int)width,(int)height) );
    
	// initialize initial timestamps
	nextFrameTimestamp = microsec_clock::local_time();
	currentFrameTimestamp = nextFrameTimestamp;
	td = (currentFrameTimestamp - nextFrameTimestamp);
    
	// start thread to begin capture and populate Mat frame
	boost::thread captureThread(captureFunc,&frame,&capture);
    
	// loop infinitely
	for(;;)
	{
        
		// wait for X microseconds until 1second/framerate time has passed after previous frame write
		while(td.total_microseconds() < 1000000/framerate){
            //determine current elapsed time
			currentFrameTimestamp = microsec_clock::local_time();
			td = (currentFrameTimestamp - nextFrameTimestamp);
		}
        
		//	 determine time at start of write
		initialLoopTimestamp = microsec_clock::local_time();
        
		// Save frame to video
		video << frame;
        imshow("image",frame);
        waitKey(1);
		//write previous and current frame timestamp to console
		cout << nextFrameTimestamp << " " << currentFrameTimestamp << " ";
        
		// add 1second/framerate time for next loop pause
		nextFrameTimestamp = nextFrameTimestamp + microsec(1000000/framerate);
        
		// reset time_duration so while loop engages
		td = (currentFrameTimestamp - nextFrameTimestamp);
        
		//determine and print out delay in ms, should be less than 1000/FPS
		//occasionally, if delay is larger than said value, correction will occur
		//if delay is consistently larger than said value, then CPU is not powerful
		// enough to capture/decompress/record/compress that fast.
		finalLoopTimestamp = microsec_clock::local_time();
		td1 = (finalLoopTimestamp - initialLoopTimestamp);
		delayFound = td1.total_milliseconds();
		cout << delayFound << endl;
        
		//output will be in following format
		//[TIMESTAMP OF PREVIOUS FRAME] [TIMESTAMP OF NEW FRAME] [TIME DELAY OF WRITING]
        
	}
    
	// Exit
	return 0;
}