#include <iostream>
#include <raspicam/raspicam_cv.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <unistd.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	raspicam::RaspiCam_Cv Camera;
	Mat image;

	Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
	Camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	Camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	if(!Camera.open())
	{
		cerr << "ERROR" <<endl;
		return -1;
	}
	
	while(1)
	{
		Camera.grab();
		Camera.retrieve(image);
		
	    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);

		imwrite("/home/pi/capture/capture.jpg", image);
		sleep(0.1);

		if(waitKey(20) == 27)
			break;
	}

	Camera.release();
}
