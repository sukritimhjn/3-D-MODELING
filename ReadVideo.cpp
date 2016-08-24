#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(int argc, char**argv[])
{
	//VideoCapture cap("sukvideo.avi");
	VideoCapture cap(0);

	if (!cap.isOpened()) //if not sucess, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	//cap.set(CV_CAP_PROP_POS_MSEC,10);//start the video at 300ms
	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	cout << "Frame size :" << dWidth << "x" << dHeight << endl;

	//double fps = cap.get(CV_CAP_PROP_FPS);//get the frames per seconds of the video
	//cout << "Frames per seconds : " << fps << endl;

	namedWindow("MyVideo_sukvideo", CV_WINDOW_AUTOSIZE);

	while (1)
	{
		Mat frame;

		bool bSuccess = cap.read(frame);//read a new frame from video
		if (!bSuccess)
		{
			cout << "Cannot read the frame from the video stream" << endl;
			break;
		}
       
		imshow("MyVideo_sukvideo", frame);//shows the frame in "MyVideo_sukvideo" window

		if (waitKey(30) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
		}
	return 0;
}
	
