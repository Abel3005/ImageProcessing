#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
void ExtractByHsv(Mat hsv, Mat bin);
void HoughTransform(Mat mbin, Mat dst);

int main() {

	Mat source = imread("00003.jpg", IMREAD_COLOR);
	Mat hsv, temp, dst;
	Mat channel[3];
	cvtColor(source, hsv, COLOR_RGB2HSV); 
	cvtColor(source, temp, COLOR_RGB2GRAY);

		
	split(hsv, channel); 
	imshow("source", source);
	imshow("hue", channel[0]);
	imshow("sat", channel[1]);
	imshow("val", channel[2]);
	ExtractByHsv(hsv, temp);
	HoughTransform(temp,source);
	imshow("result", temp);
	waitKey(0);
}
void ExtractByHsv(Mat hsv, Mat bin) {
	const int width = hsv.cols;
	const int height = hsv.rows;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Vec3b val = hsv.at<Vec3b>(y, x);

			if (((10 <= val[0])&& (val[0] <=50) 
				&&( 110 <= val[1]) && (val[1] <= 255) 
				&& ( 130 < val[2]) && (val[2] <= 255))
				/*||((10 <= val[0]) && (val[0] <= 30)
					&& (10 <= val[1]) && (val[1] <= 45)
					&& (97 < val[2]) && (val[2] <= 150))*/
				) 
			{
				bin.at<unsigned char>(y, x) = 255;
				

			}
			else {
			bin.at<unsigned char>(y, x) = 0;
			
			}
		}
	}
}
void HoughTransform(Mat mbin, Mat dst)
{
	Mat bin = mbin.clone();
	vector<Vec2f> lines;
	HoughLines(bin, lines,  1, CV_PI / 180,30);
	/*for(int i =0; i<1; i++){
		float rho = lines[i][0], theta = lines[i][1];
			Point pt1, pt2;
			
			double a = cos(theta), b = sin(theta);
			double x0 = a * rho, y0 = b * rho;
			pt1.x = cvRound(x0 + 1000 * (-b));
			pt1.y = cvRound(y0 + 1000 * (a));
			pt2.x = cvRound(x0 - 1000 * (-b));
			pt2.y = cvRound(y0 - 1000 * (a));
			line(dst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
	}*/
	int theta1 = 0, theta2 = 0;
	for (size_t i = 0; i < lines.size(); i++)
	{
		if ((theta1 == 1) && (theta2 == 1)) {
			break;
		}
		float rho = lines[i][0], theta = lines[i][1];
		if (theta < 3.141592 / 2) {
			if (theta1 == 1) {
				continue;
			}
			theta1 = 1;
		}
		else if(theta > (3.141592/2)){
			if (theta2 == 1) {
				continue;
			}
			theta2 = 1;
		}
		
		
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);

		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
	}
}
/*void HoughTransform(Mat mbin, Mat dst)
{
	Mat bin = mbin.clone();
	Mat lines;
	HoughLines(bin, lines, HOUGH_STANDARD, 1, CV_PI / 180, 100);
	for (int i = 0; i < MIN(lines.total(), 100); i++)
	{
		float* line = (float*)lines.data;
		//그리기 위한 임시라인
		float rho = line[0];
		float theta = line[1];
		//극좌표를 직교좌표로 바꿔준다.
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;//직선이 지나는
		//무한히 긴 라인을 그리기 위한 작업
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		cv::line(dst, pt1, pt2, Scalar(0, 0, 255));
	}
}*/