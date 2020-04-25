#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#define thresh 100 // ����ȭ�� ���� �Ӱ谪
#define maxValue 255 // ����ȭ�� ���� �ִ�ȭ�� ��Ⱚ
void main()
{
	Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
	Mat dst = src.clone(); // ����ó�� �� �������

	threshold(src, dst, thresh, maxValue, THRESH_BINARY);

	imshow("Original", src); //"Original"������ ȭ�鿡 ���
	imshow("Result", dst); //������� ȭ�鿡 ���
	waitKey(0); //Ű �Է��� ��ٸ���.

	src.release(); //�������� �Ҵ�� �޸𸮸� �����Ѵ�.
	dst.release(); //�������� �Ҵ�� �޸𸮸� �����Ѵ�.
}