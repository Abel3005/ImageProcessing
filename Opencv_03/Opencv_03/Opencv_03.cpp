#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main()
{
	Mat src = imread("lena.bmp", CV_8UC1);
	Mat dst = Mat::zeros(src.size(), CV_8UC1);
	// 5x5 Gaussian Smoothing filter, 표준편차()는 표준(standard) 시그마값을 사용
	GaussianBlur(src, dst, Size(5, 5), 0.0, 0.0);
	//GaussianBlur(src, dst, Size(0,0), 1.0, 5.0);
	imshow("Original", src); //"Original"영상을 화면에 출력
	imshow("Result", dst); //결과영상 화면에 출력
	waitKey(0); //키 입력을 기다린다.
	src.release(); //동적으로 할당된 메모리를 해제한다.
	dst.release(); //동적으로 할당된 메모리를 해제한다.

}