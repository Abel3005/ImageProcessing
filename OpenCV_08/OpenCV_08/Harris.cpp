#include <opencv2/opencv.hpp>
#include <iostream>
//#include <highgui.h>
#define CORNER_MAX 1024
using namespace cv;
using namespace std;
void main()
{
	//코너 검출을 위한 영상 준비
	Mat oriImage = imread("lena.bmp", IMREAD_GRAYSCALE);
	Mat color = Mat::zeros(oriImage.size(), CV_8UC1);
	vector<Point2f> points;
	goodFeaturesToTrack(oriImage, points, CORNER_MAX, 0.01, 6);
	cvtColor(oriImage, color, COLOR_GRAY2BGR);
	int cornerCount = CORNER_MAX;
	for (int i = 0; i < cornerCount; i++)
	{
		circle(color, points[i], 2, Scalar(0, 0, 255));
	}
	imshow("oriImage", oriImage);
	imshow("cornerImage", color);
	oriImage.release();
	color.release();
	waitKey();
}