#include <iostream>
#include <string>

#include "opencv2\opencv.hpp"

// This code is basixally just to test :  resizing the windows to the size of the actual image in OpenCV
int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "USAGE: file_name image_name" << std::endl;
		return -1;
	}
	
	char* imageName = argv[1]; // storing the address of the 1th string commadline entry in to a pointer 
	cv::Mat image;
	image = cv::imread(imageName, cv::IMREAD_COLOR);

	if (image.empty() == true)
	{
		std::cout << "ERROR: Image could not be read" << std::endl;
		return -2;
	}


	cv::Mat grayImage;
	int winSz_x, winSz_y;

	winSz_x = image.cols;
	winSz_y = image.rows;

	cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY); // similar function as rgb2gray in matlab

	cv::namedWindow("image",cv::WINDOW_NORMAL);
	cv::imshow("image", image);
	cv::resizeWindow("image", winSz_x, winSz_y); // resizing the windows to the size of the actual image

	cv::namedWindow("Grayscaled image", cv::WINDOW_NORMAL);
	cv::imshow("Grayscaled image",grayImage);
	cv::resizeWindow("Grayscaled image", winSz_x, winSz_y); // resizing the windows to the size of the actual image



	cv::waitKey();
	return 0;
}


 


