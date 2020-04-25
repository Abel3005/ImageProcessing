#include <iostream>
#include <opencv2\opencv.hpp>
#define COUNT 3

using namespace std;
using namespace cv;
int main()
{
	Mat inImage = imread("lena.bmp", IMREAD_GRAYSCALE);
	Mat dst;
	cvtColor(inImage, dst, COLOR_GRAY2BGR);
	Mat tmp = imread("lena_ref.bmp", IMREAD_GRAYSCALE);
	double minVal;
	Point minLoc;
	Mat result(inImage.rows - tmp.rows + 1, inImage.cols - tmp.cols + 1, CV_8UC1);


	//결과 영상

	matchTemplate(inImage, tmp, result, TM_SQDIFF);
	minMaxLoc(result, &minVal, NULL, &minLoc, NULL);


	rectangle(dst, minLoc, Point(minLoc.x + tmp.rows, minLoc.y + tmp.cols), Scalar(255, 0, 0), 2);

	imshow("result", dst);
	waitKey();
	//결과를 사각형으로 그려준다.
	return 0;

}