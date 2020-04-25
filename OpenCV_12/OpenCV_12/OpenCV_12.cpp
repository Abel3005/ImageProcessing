#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


void main()
{
	//샘플 데이터를 생성한다.
	float trainData[32] = { 5, 10, 34, 29, 99, 63, 82, 36, 165, 140, 169, 84, 190, 118, 198, 153, 30, 163, 19, 58, 98, 89, 138, 153, 54, 140, 76, 50, 81, 170, 210, 201 };
	float trainClass[16] = { 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1 };
	Mat dataMat = Mat(16, 2, CV_32FC1, trainData);
	Mat classMat = Mat(16, 1, CV_32SC1, trainClass);

		//분류기와 관련된 설정
	DGBoost boost;
	CvBoostParams param(ml::Boost::REAL, 5, 0, 3, false, 0);
	param.split_criteria = ml::Boost::DEFAULT;

	//분류기에 샘플 데이터를 넣어 학습한다
	boost.train(dataMat.ptr<ml::TrainData>);

	//테스트 결과를 보여줄 영상
	Mat img = Mat((256, 256), CV_32SC1, 3);

	//영상의 모든 점에 대해 테스트한다.
	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			float test[2] = { x, y };
			Mat testMat = Mat(1, 2, CV_32FC1, test);
			float result = boost.predict(testMat);//학습된 분류기를 이용한 분류
			if (result > 0)
				img.at<Scalar>(y, x) = Scalar(100, 0, 0);
			else
				img.at<Scalar>(y, x) = Scalar(0, 100, 0); 

		}
	}

	//훈련 샘플에 대한 결과를 보여준다
	for (int i = 0; i < 16; i++)
	{
		int x = trainData[i * 2];
		int y = trainData[i * 2 + 1];
		float test[2] = { x, y };
		Mat testMat = Mat(1, 2, CV_32FC1, test);
		float result = boost.predict(testMat);//학습된 분류기를 이용한 분류
		if (result > 0)
			circle(img, Point(x, y), 2, CV_RGB(255, 0, 0));
		else
			circle(img, Point(x, y), 2, CV_RGB(0, 255, 0));
	}

	imshow("image", img);
	waitKey(0);
}

class DGBoost : ml::Boost {
	
	


	// Inherited via Boost
	virtual CV_WRAP int getVarCount() const override
	{
		return CV_WRAP int();
	}

	virtual CV_WRAP bool isTrained() const override
	{
		return CV_WRAP bool();
	}

	virtual CV_WRAP bool isClassifier() const override
	{
		return CV_WRAP bool();
	}

	virtual CV_WRAP float predict(InputArray samples, OutputArray results = noArray(), int flags = 0) const override
	{
		return CV_WRAP float();
	}

	virtual CV_WRAP int getMaxCategories() const override
	{
		return CV_WRAP int();
	}

	virtual CV_WRAP void setMaxCategories(int val) override
	{
		return CV_WRAP void();
	}

	virtual CV_WRAP int getMaxDepth() const override
	{
		return CV_WRAP int();
	}

	virtual CV_WRAP void setMaxDepth(int val) override
	{
		return CV_WRAP void();
	}

	virtual CV_WRAP int getMinSampleCount() const override
	{
		return CV_WRAP int();
	}

	virtual CV_WRAP void setMinSampleCount(int val) override
	{
		return CV_WRAP void();
	}

	virtual CV_WRAP int getCVFolds() const override
	{
		return CV_WRAP int();
	}

	virtual CV_WRAP void setCVFolds(int val) override
	{
		return CV_WRAP void();
	}

	virtual CV_WRAP bool getUseSurrogates() const override
	{
		return CV_WRAP bool();
	}

	virtual CV_WRAP void setUseSurrogates(bool val) override
	{
		return CV_WRAP void();
	}

	virtual CV_WRAP bool getUse1SERule() const override
	{
		return CV_WRAP bool();
	}

	virtual CV_WRAP void setUse1SERule(bool val) override
	{
		return CV_WRAP void();
	}

	virtual CV_WRAP bool getTruncatePrunedTree() const override
	{
		return CV_WRAP bool();
	}

	virtual CV_WRAP void setTruncatePrunedTree(bool val) override
	{
		return CV_WRAP void();
	}

	virtual CV_WRAP float getRegressionAccuracy() const override
	{
		return CV_WRAP float();
	}

	virtual CV_WRAP void setRegressionAccuracy(float val) override
	{
		return CV_WRAP void();
	}

	virtual CV_WRAP cv::Mat getPriors() const override
	{
		return CV_WRAP cv::Mat();
	}

	virtual CV_WRAP void setPriors(const cv::Mat & val) override
	{
		return CV_WRAP void();
	}

	virtual const std::vector<int>& getRoots() const override
	{
		// TODO: insert return statement here
	}

	virtual const std::vector<Node>& getNodes() const override
	{
		// TODO: insert return statement here
	}

	virtual const std::vector<Split>& getSplits() const override
	{
		// TODO: insert return statement here
	}

	virtual const std::vector<int>& getSubsets() const override
	{
		// TODO: insert return statement here
	}

	virtual CV_WRAP int getBoostType() const override
	{
		return CV_WRAP int();
	}

	virtual CV_WRAP void setBoostType(int val) override
	{
		return CV_WRAP void();
	}

	virtual CV_WRAP int getWeakCount() const override
	{
		return CV_WRAP int();
	}

	virtual CV_WRAP void setWeakCount(int val) override
	{
		return CV_WRAP void();
	}

	virtual CV_WRAP double getWeightTrimRate() const override
	{
		return CV_WRAP double();
	}

	virtual CV_WRAP void setWeightTrimRate(double val) override
	{
		return CV_WRAP void();
	}

};