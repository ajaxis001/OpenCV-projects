// test_cvPointOperation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include "opencv2\opencv.hpp"

int main()
{
	cv::Mat img(100, 100, CV_8U, cv::Scalar(0));
	img.at<uchar>(50, 50) = 255;
	img.at<uchar>(70, 50) = 255;
	img.at<uchar>(58, 30) = 255;

	cv::Mat nonZeroes;
	cv::findNonZero(img, nonZeroes);

	std::vector<cv::Point> coords(nonZeroes.total());

	for (int i = 0; i < nonZeroes.total(); i++)
	{
		coords[i] = nonZeroes.at<cv::Point>(i);
		std::cout << "\n" << "(x = " << nonZeroes.at<cv::Point>(i).x << "), (y = " << nonZeroes.at<cv::Point>(i).y << ")";
	}

	std::cin.get();
	return 0;
}

