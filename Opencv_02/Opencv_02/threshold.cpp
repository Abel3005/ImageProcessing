#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#define thresh 100 // 이진화를 위한 임계값
#define maxValue 255 // 이진화를 위한 최대화소 밝기값
void main()
{
	Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
	Mat dst = src.clone(); // 영상처리 후 결과영상

	threshold(src, dst, thresh, maxValue, THRESH_BINARY);

	imshow("Original", src); //"Original"영상을 화면에 출력
	imshow("Result", dst); //결과영상 화면에 출력
	waitKey(0); //키 입력을 기다린다.

	src.release(); //동적으로 할당된 메모리를 해제한다.
	dst.release(); //동적으로 할당된 메모리를 해제한다.
}