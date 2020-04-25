#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
void main()
{
	Mat src8 = imread("lena.bmp", CV_8UC1);
	Mat src32 = Mat(src8.size(), CV_32FC1, 1);
	Mat dct32 = Mat(src8.size(), CV_32FC1, 1);
	Mat inversed32 = Mat(src8.size(), CV_32FC1, 1);
	src8.convertTo(src32, CV_32FC1);
	dct(src32, dct32);
	dct(dct32, inversed32, DCT_INVERSE);
	//화면에 표시하기 위해 8비트 이미지를 다시 만들어준다.
	Mat dct8 = Mat(src8.size(), CV_8UC1, 1);
	Mat inversed8 = Mat(src8.size(), CV_8UC1, 1);
	dct32.convertTo(dct8, CV_8UC1, 0.5);
	inversed32.convertTo(inversed8, CV_8UC1);
	imshow("original", src8);
	imshow("FDCT", dct8);
	imshow("restore", inversed8);
	waitKey(0);
}