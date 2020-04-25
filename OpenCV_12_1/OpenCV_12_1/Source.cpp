#include <opencv2/opencv.hpp>

void main()
{
	//���� �����͸� �����Ѵ�.
	float trainData[32] = { 5, 10, 34, 29, 99, 63, 82, 36, 165, 140, 169, 84, 190, 118, 198, 153, 30, 163, 19, 58, 98, 89, 138, 153, 54, 140, 76, 50, 81, 170, 210, 201 };
	float trainClass[16] = { 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1 };
	CvMat dataMat = cvMat(16, 2, CV_32FC1, trainData);
	CvMat classMat = cvMat(16, 1, CV_32SC1, trainClass);

		//�з���� ���õ� ����
	CvBoost boost;
	CvBoostParams param(CvBoost::REAL, 5, 0, 3, false, 0);
	param.split_criteria = CvBoost::DEFAULT;

	//�з��⿡ ���� �����͸� �־� �н��Ѵ�.
	boost.train(&dataMat, CV_ROW_SAMPLE, &classMat);

	//�׽�Ʈ ����� ������ ����
	IplImage *img = cvCreateImage(cvSize(256, 256), IPL_DEPTH_8U, 3);

	//������ ��� ���� ���� �׽�Ʈ�Ѵ�.
	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			float test[2] = { x, y };
			CvMat testMat = cvMat(1, 2, CV_32FC1, test);
			float result = boost.predict(&testMat, 0);//�н��� �з��⸦ �̿��� �з�
			if (result > 0)
				cvSet2D(img, y, x, CV_RGB(100, 0, 0));
			else
				cvSet2D(img, y, x, CV_RGB(0, 100, 0));

		}
	}

	//�Ʒ� ���ÿ� ���� ����� �����ش�
	for (int i = 0; i < 16; i++)
	{
		int x = trainData[i * 2];
		int y = trainData[i * 2 + 1];
		float test[2] = { x, y };
		CvMat testMat = cvMat(1, 2, CV_32FC1, test);
		float result = boost.predict(&testMat, 0);//�н��� �з��⸦ �̿��� �з�
		if (result > 0)
			cvCircle(img, cvPoint(x, y), 2, CV_RGB(255, 0, 0)); 
		else
			cvCircle(img, cvPoint(x, y), 2, CV_RGB(0, 255, 0));
	}

	cvShowImage("image", img);
	cvWaitKey(0); 
}