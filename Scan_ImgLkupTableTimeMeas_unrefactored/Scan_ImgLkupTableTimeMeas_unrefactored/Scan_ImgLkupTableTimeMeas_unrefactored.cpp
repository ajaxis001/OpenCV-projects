// Scan_ImgLkupTableTimeMeas_unrefactored.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>

#include "opencv2/opencv.hpp"

static void help()
{
	std::cout << "\n--------------------------------------------------------------------------                             " << std::endl
		<< "This program shows how to scan image objects in OpenCV (cv::Mat). As use case                            " << std::endl
		<< " we take an input image and divide the native color palette (255) with the                               " << std::endl
		<< "input. This code shows the C operator[] method, iterators and function for on-the-fly address calculation" << std::endl
		<< "USAGE:                                                                                                   " << std::endl
		<< "./thisProgramName imageNameToUse divideWidth [G]                                                         " << std::endl
		<< "if you add a G parameter the image is processed in gray scale" << std::endl;
}

int main(int argc, char* argv[])
{
	help();

	if (argc < 3)
	{
		std::cout << "ERROR: not enough input parameters" << std::endl;
		return -1;
	}


	cv::Mat I, J;
	if (argc == 4 && strcmp(argv[3], "G"))
	{
		I = cv::imread(argv[1], cv::IMREAD_GRAYSCALE); std::cout << "\n:::Grayscaling done:::\n" << std::endl;
	}
	else
	{
		I = cv::imread(argv[1], cv::IMREAD_COLOR); std::cout << "\n:::Grayscaling notto donezoo:::\n" << std::endl;
	}
	

	if (I.empty())
	{
		std::cout << "ERROR: the image" << argv[1] << "could not be loaded" << std::endl;
		return -2;
	}

	int divideWidth(0);
	std::stringstream s;
	s << argv[2];
	s >> divideWidth;
	if (!s || !divideWidth) // when both are 0
	{
		std::cout << "ERROR: Invalid number entered for dividing" << std::endl;
		return -3;
	}

	uchar table[256];
	for (uint i = 0 ; i <256; ++i)
		table[i] = divideWidth * (i / divideWidth);
	
	const int times(100); 
	double t;

	t = static_cast<double> (cv::getTickCount());

	// 1st Method (efficient) :  C style operator[] (pointer) access -------------------------------------------------------------------------------------------------------------------------

	// We do the same method a 100 times and then average them after we do that
	for (uint i = 0; i < times; ++i) 
	{
		cv::Mat clone_I = I.clone();
		
	// START :: this portion to be refactored into the function -> Mat& ScanImageAndReduceC(Mat& I, const uchar* table)
		CV_Assert(clone_I.depth() != sizeof(uchar));
		int channels = clone_I.channels();
		
		int nRows = clone_I.rows;
		int nCols = clone_I.cols * channels;

		if (clone_I.isContinuous())
		{
			nCols *= nRows;
			nRows = 1;
		}

		uchar* p;
		for (int i = 0; i < nRows ; ++i)
		{
			p = clone_I.ptr<uchar>(i); // *p gives the first element of the i'th row
									  // cout << p ; => gives everything the whole memory block including the   
			// std::cout << "\np = clone_I.ptr<uchar>("<< i <<")" << &(*p) << "\n\n\n" << std::endl;
			for (int j = 0; j < nCols ; ++j)
			{
				//std::cout << "the original ("<< i << ","<< j<<") element : "<< static_cast<int>(p[j]) << std::endl;
				p[j] = table[p[j]];
				//std::cout << "the new (" << i << "," << j << ") element : " << static_cast<int>(table[p[j]]) << std::endl;
			}
		}		
		//END :: refactoring -----------------------------------------------------------------------------------------------
	}

	t = 1000 * ((static_cast<double> (cv::getTickCount()) - t)) / (cv::getTickCount()); // multiplication by 1000 to get value in milliseconds rather than in seconds
	t /= times;

	std::cout << "\n1. (Efficient) Time of reducing with C operator[] (averaged for "
		<< times << " runs ): " << t << "milliseconds." << std::endl;

	// 2nd Method (safe) : The iterator method   -------------------------------------------------------------------------------------------------------------------------
	t = static_cast<double> (cv::getTickCount());

	for (uint i = 0; i < times; ++i)
	{
		cv::Mat clone_I = I.clone();

		// START :: this portion to be refactored into the function -> Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table)
		CV_Assert(clone_I.depth() != sizeof(uchar));

		const int channels = clone_I.channels();

		switch (channels)
		{
		case 1:
			{
			cv::MatIterator_<uchar> it, end;
			}
		}


 
	}

	return 0;
}

