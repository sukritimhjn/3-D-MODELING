#include <opencv2/core/core.hpp>
#include <opencv2/flann/miniflann.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"

#include<math.h>
#include<vector>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <iostream>

#define PI 3.1415
#define perc 1000000

using namespace std;
using namespace cv;

int video_to_picture();
void contour_final(cv::Mat src);
cv::Mat contour_final_thresholding();
void read_multiple_images();
std::vector < std::vector <float> > getCoords_x_y_z(cv::Mat a, float theta);

int main()
{
//	video_to_picture();
//	read_multiple_images();
	vector<float> result_x;
	vector<float> result_y;
	vector<float> result_z;
	double theta = 0.0;

	cv::String folder = "C:\\Users\\sony\\Documents\\Visual Studio 2015\\Projects\\test\\picture_contoured_sphere\\*.jpg";
	vector<cv::String> filenames;
	cout << "me";
	glob(folder, filenames);

	for (size_t i = 0; i < filenames.size(); i++)
	{

		Mat src = cv::imread(filenames[i]);
		vector<vector<float>> result = getCoords_x_y_z(src, theta);

		for (int i = 0; i < result[0].size(); i++)
		{
			result_x.push_back(result[0][i]);
		}
		for (int i = 0; i < result[1].size(); i++)
		{
			result_y.push_back(result[1][i]);
		}
		for (int i = 0; i < result[2].size(); i++)
		{
			result_z.push_back(result[2][i]);
		}
		theta = theta + 10.0;
	}
    cout<<"generating txt \n";
	//coordinates to text file
	std::ofstream output;
	output.open("circle_resx_2.txt");
	output.setf(std::ios_base::fixed);
	for (int p = 0; p < result_x.size(); p= p+2) {
		output << result_x[p] << " , ";
	}
	output.close();

	output.open("circle_resy_2.txt");
	output.setf(std::ios_base::fixed);
	for (int p = 0; p < result_x.size(); p=p+2) {
		output << result_y[p] << " , ";
	}
	output.close();
	output.open("circle_resz_2.txt");
	output.setf(std::ios_base::fixed);
	for (int p = 0; p < result_x.size(); p=p+2) {
		output << result_z[p] << " , ";
	}
	output.close();

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//video to pictures
int video_to_picture()
{
	VideoCapture cap("video.avi"); // open the video file

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	double frnb(cap.get(CV_CAP_PROP_FRAME_COUNT));
	char buffer[100];

	int counter = 0;
	while (counter <360)
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
			counter++;
		}

	}
	return 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------
//contour_final
//RNG rng(12345);

void contour_final(cv::Mat src)
{
//	cout << "i entered contour \n";
    
	Mat src_gray;
	int thresh = 26;
	int max_thresh = 255;
	RNG rng(12345);

	/// Convert image to gray and blur it
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(4, 4));
	

	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using canny
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Draw contours
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	}
	vector<int> compression_params; //vector that stores the compression parameters of the image

	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); //specify the compression technique

	compression_params.push_back(98); //specify the compression quality



	bool bSuccess = imwrite("C://Users//sony//Documents//Visual Studio 2015//Projects//test//final//t_contour_new_sphere1.jpg", drawing, compression_params); 
  
	if (!bSuccess)
	{
		cout << "ERROR : Failed to save the image" << endl;

	}
	return;
}


//-----------------------------------------------------------------------------------------------------------------------------------------------
//contour_final_thresholding

cv::Mat contour_final_thresholding()
{
        cv::Mat src_gray;
        cv::Mat src = imread("C://Users//sony//Documents//Visual Studio 2015//Projects//test//final//t_contour_new_sphere1.jpg",CV_LOAD_IMAGE_UNCHANGED);
	    //cvtColor(src, src_gray, CV_BGR2GRAY);
	    //blur(src_gray,src_gray, Size(4,4));

    //char d;
	//cin >> d;
	//cout << "i am in c_final_thresholding \n";

	int threshold_value = 26;
	int threshold_type = 1;
	int const max_value = 255;
	int const max_type = 4;
	int const max_BINARY_value = 255;
	cv::Mat dst;

	threshold(src, dst, threshold_value, max_BINARY_value, threshold_type);
	vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    compression_params.push_back(98);
    bool bSuccess = imwrite("C://Users//sony//Documents//Visual Studio 2015//Projects//test//final//final_contour_saved_0_atthreshold26_sphere.jpg", dst, compression_params);
	if (!bSuccess)
    {
    cout << "ERROR : Failed to save the image 2" << endl;}
    cv::Mat dst1 = imread("C://Users//sony//Documents//Visual Studio 2015//Projects//test//final//final_contour_saved_0_atthreshold26_sphere.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    
//    char e;
//	cout << "I exit c_f_t \n";
//	cin >> e;

	return(dst1);
}



//---------------------------------------------------------------------------------------------------------------------------------------
//read_multiple_images
void read_multiple_images()
{
//	char r, m;
//	cin >> r;
//	cout << "i am in read_m \n";
	cv::String folder = "C:\\Users\\sony\\Documents\\Visual Studio 2015\\Projects\\test\\read_sphere\\*.jpg";
	vector<cv::String> filenames;

	glob(folder, filenames);

	for (size_t i = 0; i < filenames.size(); i++)
	{
		Mat src = cv::imread(filenames[i]);

		if (!src.data)
		{
			cout << "image [" << i << "] cannot be loaded " << endl;
			break;
		}
		//cout << "hello";
		contour_final(src);
		cv::Mat srcb = contour_final_thresholding();

		vector<int> compression_params; //vector that stores the compression parameters of the image

		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); //specify the compression technique

		compression_params.push_back(98); //specify the compression quality

		bool Success = imwrite("C:\\Users\\sony\\Documents\\Visual Studio 2015\\Projects\\test\\picture_contoured_sphere\\" + std::to_string(i) + ".jpg", srcb, compression_params);
	}
//	cin >> m;
//	cout << "exit read_m";
	return;
}

//-------------------------------------------------------------------------------------------------------------------------------------------
//getcoordx_y_z(Mat a, float theta)

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
			x = j - ((a.cols - 1) / 2.0); 
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
}
