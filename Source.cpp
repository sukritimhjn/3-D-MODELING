
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"

#include<math.h>
#include<iostream>
#include<vector>
#include <fstream>
#define PI 3.1415
#define perc 1000000
#include <iomanip>

using namespace std;
using namespace cv;


int threshold_value = 119;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;
Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";

void Threshold_Demo(int, void*)
{
	///* 0: Binary
	//1: Binary Inverted
	//2: Threshold Truncated
	//3: Threshold to Zero
	//4: Threshold to Zero Inverted
	//
	threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
}


std::vector < std::vector <float> > getCoords_x_y_z(cv::Mat a, float theta) {
	int len = a.rows - 1;
	int wid = a.cols - 1;
	std::vector <float> vx;
	std::vector <float> vy;
	std::vector <float> vz;
	std::vector < std::vector <float> > res;

	float x, y, z;
	float x2, y2, z2;
	float rad_theta = theta * PI / 180.0;

	for (int i = 0; i < a.rows - 1; i++) {
		for (int j = 0; j < a.cols - 1; j++) {
			x = j;
			y = 0;
			z = i;
			if ((int)a.at<uchar>(i, j) <= 20) {
				x2 = x*cos(rad_theta) - y*sin(rad_theta);
				y2 = x*sin(rad_theta) + y*cos(rad_theta);
				z2 = z;
				vx.push_back(floorf(x2 * perc) / perc);
				vy.push_back(floorf(y2 * perc) / perc);
				vz.push_back(floorf(z2 * perc) / perc);
			}
		}
	}
	res.push_back(vx);
	res.push_back(vy);
	res.push_back(vz);

	return res;
}std::cout << b.type() << std::endl;
	std::cout << (int)b.at<uchar>(0, 0);
	std::cout << b.cols;
	cv::Mat x = a.clone();
	for (int i = 0; i < b.rows - 1; i++) {
		for (int j = 0; j < b.cols - 1; j++) {
			if ((int)b.at<uchar>(i, j) >= 240) {
				x.at<uchar>(i, j) = (char)255;
			}
		}
	}
	return x;
}



int main() {

	/*video to pictures
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
	*/


	//write images to a folder

	src = imread("2.JPG", CV_LOAD_IMAGE_UNCHANGED);
	cvtColor(src, src_gray, COLOR_RGB2GRAY);
	Threshold_Demo(0, 0);






	

	return(0);
}