#include<opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	VideoCapture cap("video.avi"); // open the video file

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Frame size : " << dWidth << " x " << dHeight << endl;
	double frnb(cap.get(CV_CAP_PROP_FRAME_COUNT));
	cout << "Frame count:" << frnb << endl;
	char buffer[100];
	namedWindow("screenshot", CV_WINDOW_KEEPRATIO); //create a window called "MyVideo"
													//	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);

	while (1)
	{
		Mat frame;
		double framedist = frnb / 360;
		if (framedist > frnb) break;
		for (double frm = 0.0; frm < frnb; frm = frm + framedist)
		{
			bool bSuccess = cap.read(frame); // read a new frame from video
			if (!bSuccess) //if not success, break loop
			{
				cout << "Cannot read a frame from video stream" << endl;
				break;
			}
			cap.set(CV_CAP_PROP_POS_FRAMES, frm);//read frame no frm from video
			sprintf(buffer, "image%f.jpg", frm);//give the image a name according to the number
			imwrite(buffer, frame);
			imshow("screenshot", frame);

			//			imshow("MyVideo", frame); //show the frame in "MyVideo" window
		}



		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	return 0;

}