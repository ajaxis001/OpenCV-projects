/* Scan_ImagesLookupTablesTimeMeasurement.cpp : Defines the entry point for the console application.
Reference: http://docs.opencv.org/3.0-beta/doc/tutorials/core/how_to_scan_images/how_to_scan_images.html
We’ll seek answers for the following questions:
1.How to go through each and every pixel of an image?
2.How is OpenCV matrix values stored?
3.How to measure the performance of our algorithm?
4.What are lookup tables and why use them?

*/

#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <string>

#include "opencv2\opencv.hpp"

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "USAGE : file_name image_name color_space_reduction_param  color_map" << std::endl;
		return -1;
 	}

	// Reading in the image
	cv::Mat I,J;

	if (argc == 4 && !strcmp(argv[3], "G")) // if color_map commandline param = "G" read image as grayscale else read as color image
		I = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
	else
		I = cv::imread(argv[1], cv::IMREAD_COLOR);
		
	if (I.empty() == true)
	{
		std::cout << "ERROR : Cannot load image " << std::endl;
		return -2;
	}

	// TODO-------------------------------------------------------------
	// Calculating the lookup table - color space reduction is basically a quantization operation on the color values and argv[2] gives the distance between two qntzn levels q_delta
	int  divideWidth = 0;  // this is the q_delta
	std::stringstream s;  // creating a stringstream object
	s << argv[2];
	s >> divideWidth;
	if (!s || !divideWidth) // check if both the input  and default q_delta values are zero
	{
		std::cout << "ERROR : Invalid number entered for dividing." << std::endl;
		return -3;
	}

	uchar table[256];
	for (int i = 0; i < 256; ++i)
	{
		table[i] = static_cast<uchar> (divideWidth * (i/divideWidth)); 
		// here (i/divideWidth) is calculated first and the decimal point is rounded off because it is a uchar datatype and then we multiply it with divideWidth again
		// This means that if i = 233 and divideWidth = 10, 
		// then  1st. (233/10)= 23.3 -> 23
		// then  2nd. 10 * 23 = 230
	}

	const int times(100);
	double t0;

	t0 = static_cast<double> (cv::getTickCount()); // gives the number of cpu clock ticks in 1 sec

	for (int i = 0; i < times; ++i)
	{
		cv::Mat clone_i = I.clone(); // Creating a datacopy of I(the image data)
	}
	



    return 0;
}



