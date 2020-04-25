#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main()
{
	Mat src = imread("lena.bmp", CV_8UC1);
	Mat dst = Mat::zeros(src.size(), CV_8UC1);
	// 5x5 Gaussian Smoothing filter, ǥ������()�� ǥ��(standard) �ñ׸����� ���
	GaussianBlur(src, dst, Size(5, 5), 0.0, 0.0);
	//GaussianBlur(src, dst, Size(0,0), 1.0, 5.0);
	imshow("Original", src); //"Original"������ ȭ�鿡 ���
	imshow("Result", dst); //������� ȭ�鿡 ���
	waitKey(0); //Ű �Է��� ��ٸ���.
	src.release(); //�������� �Ҵ�� �޸𸮸� �����Ѵ�.
	dst.release(); //�������� �Ҵ�� �޸𸮸� �����Ѵ�.

}