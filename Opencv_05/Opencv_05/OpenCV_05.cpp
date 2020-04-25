#include <iostream>
#include <opencv2\opencv.hpp>
#define COUNT 3

using namespace std;
using namespace cv;
int main()
{
	Mat image1 = imread("image1.jpg");
	Mat image2 = imread("image2.jpg");
	Mat gray1 = Mat::zeros(image1.size(), CV_8UC1);
	Mat gray2 = Mat::zeros(image1.size(), CV_8UC1);
	//컬러 영상을 통해 그레이 이미지를 얻는다.
	cvtColor(image1, gray1, COLOR_RGB2GRAY);
	cvtColor(image2, gray2, COLOR_RGB2GRAY);
	vector<Point2f> points1, points2;
	vector<uchar> isFound;
	vector<float> error;
	//옵티컬 플로우를 구할 시작 포인트
	points1.push_back(Point2f(223, 86));
	points1.push_back(Point2f(212, 69));
	points1.push_back(Point2f(67, 291));
	//옵티컬 플로우 수행
	calcOpticalFlowPyrLK(gray1, gray2, points1, points2, isFound, error, Size(5, 5), 3, TermCriteria(COUNT , 20, .3));
	for (int i = 0; i < COUNT; i++)
	{
		if (isFound[i])
		{
			//결과 영상 출력
			circle(image1, points1[i], 2, Scalar(255, 255, 0));
			line(image1, points1[i], points2[i], Scalar(255, 255,
			0), 2);
			circle(image2, points2[i], 2, Scalar(255, 255, 0));
		}
		else
		{
			circle(image1, points1[i], 2, Scalar(255, 255, 0));
		}
	}
	imshow("image1", image1);
	imshow("image2", image2);
	waitKey();
	printf("%d", image1.cols);
	getchar();
	getchar();
	return 0;
}