#include <iostream>
#include <raspicam/raspicam_cv.h>
#include <unistd.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void detectAndDisplay(Mat& frame);

String face_cascade_name = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml";
CascadeClassifier face_cascade;

int main(int argc, char *argv[])
{
	raspicam::RaspiCam_Cv Camera;
	Mat image, frame;

    if(!face_cascade.load(face_cascade_name))
    {
        printf("ERROR\n");
        return -1;
    }

	Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
	Camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	Camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	if(!Camera.open())
	{
		cerr << "ERROR OPENING THE CAMERA\n" <<endl;
		return -1;
	}
	
	while(1)
	{
		Camera.grab();
		Camera.retrieve(frame);

        if(frame.empty())
            break;
        detectAndDisplay(frame);
        if(waitKey(20) == 27)
            break;
    }

	Camera.release();

    return 0;
}

void detectAndDisplay(Mat& frame)
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));

    for(size_t i = 0; i < faces.size(); i++)
    {
        Point center(faces[i].x + faces[i].width/2, faces[i].y +faces[i].height/2);
        ellipse(frame, center, Size(faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
    }

    imwrite("/home/pi/capture/capture.jpg", frame);
    sleep(0.1);
}

