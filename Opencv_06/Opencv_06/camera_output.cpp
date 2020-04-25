#include <iostream>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

#define CORNER_MAX 1024
#define PERIOD_MAX 258
#define EDGE	100
#define COUNT 3
int main()
{
	VideoCapture cap(0);
	if (!cap.isOpened())
			return -1;
	Mat gray1, //현재 영상
		gray2; //이전 영상
	
	while (1) {
		Mat color;
		cap >> color;
		cvtColor(color, gray1, COLOR_BGR2GRAY);
		vector<Point2f> points1, points2;
		vector<uchar> isFound;
		vector<float> error;
		int judgement = 0;
		int cornerCount = 0;
		int cornerPeriod = 0;
		/*if (!gray2.empty() && (cornerPeriod <= 0 || cornerCount < CORNER_MAX / 3))
		{
			//코너 특징점 검출
			goodFeaturesToTrack(gray2, points2, CORNER_MAX, 0.01, 6);
			cornerCount = points2.size();
			cornerPeriod = PERIOD_MAX;
		}
		else {
			points2 = points1;
		}*/
		cornerPeriod--;
		if (!gray2.empty()) {
			//옵티컬 플로우 검출
			calcOpticalFlowPyrLK(gray2, gray1, points2, points1, isFound,error, Size(5, 5), 3, TermCriteria(COUNT, 20,.3)); 
			cornerCount = points2.size();
			//옵티컬 플로우가 부정확하게 계산된 코너점들 제거
			int nuCornerCount = 0;
			for (int i = 0; i < cornerCount; i++)
			{
				if (isFound[i] && error[i] < 500)
				{
				points1[nuCornerCount] = points1[i];
				points2[nuCornerCount] = points2[i];
				nuCornerCount++;
				}
			} cornerCount =	nuCornerCount;
		}
		
		static Rect rect(color.cols/2,color.rows/2,EDGE,EDGE);

		int rectPointCount = 0;//사각형 내부의 포인트 개수
		double moveX = 0;//x축 방향 움직임
		double moveY = 0;//y축 방향 움직임
		for (int i = 0; i < cornerCount; i++)
		{
			//points1[i]가 rect 내부에 있다면
			if ( rect.contains(points1[i]))
			{
				moveX += points1[i].x - points2[i].x;
				moveY += points1[i].y - points2[i].y;
				rectPointCount++;
			}
		}

		//사각형을 moveX, moveY에 따라 움직인다.
		if (rectPointCount != 0)
		{
			rect.x += moveX / rectPointCount;
			rect.y += moveY / rectPointCount;
		}
		rectangle(color, rect, Scalar(0, 255, 0), 2);
		//찾아낸 코너점들을 화면에 출력
		for (int i = 0; i < cornerCount; i++)
		{
			circle(color, points1[i], 2, Scalar(0, 0, 255));
			line(color, points1[i], points2[i], Scalar(255, 255, 0), 2);
		}
		
		//.... [리스트 3]의 구현
		imshow("color", color);
		if ('q' == waitKey(1))
			break;
		if (!gray2.empty())
			gray2.release();
		gray2 = gray1.clone();
	}
	cap.release();
	return 0;
}