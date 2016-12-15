// MatContainerPropsAndConsoleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <string>
#include <iostream>

#include "opencv2\opencv.hpp"

int main(int argc, char** argv)
{

	if (argc < 2)
	{
		std::cout << "USAGE : program_name image_name" << std::endl;
		return -1;
	}

	// Mat Object class-> (Mat header: size of matrix, address of storage, method of storing etc) and (Pointer to matrix containing pixel values)
	cv::Mat A;   // creates only header parts of the Mat datatype 

	A = imread(argv[1], cv::IMREAD_COLOR); // her we know the method used to allocate the matrix

	if (A.empty() == true)
	{
		std::cout << "ERROR : Cant load image " << std::endl;
		return -2;
	}

	//TODO------------------------------------------------------------------------------

	cv::Mat C;
	// Below: Copy operators only copy matrix headers and pointer to data, not the data
	cv::Mat B(A); // Using the copy constructor
	C = A;        // Using the assignment operator

				  //Region of Interest(ROI): We can access specific subsections of the above matrix 
	cv::Mat D(A, cv::Rect(10, 10, 50, 50)); // Rect(start_x,start_y, width, height)

											// Plotting all the images
	cv::namedWindow("figure-A", cv::WINDOW_NORMAL);
	cv::imshow("figure-A", A);

	cv::namedWindow("figure-D(ROI)", cv::WINDOW_NORMAL);
	cv::imshow("figure-D(ROI)", D);
	cv::waitKey();

	//Below : Copying matrix data   
	cv::Mat E = A.clone();
	cv::Mat F;
	F.copyTo(F);

	// CREATING MAT OBJECTS EXPLICITLY
	// 1.Mat() constructor
	cv::Mat M(2, 2, CV_8UC2, cv::Scalar( 0, 255));
	std::cout << " 1.Mat() constructor ->  M = " << cv::format(M, cv::Formatter::FMT_MATLAB) << std::endl << std::endl;

	// 2.Use C/C++ arrays and initialize via constructor
	int sz[3] = { 2,2,2 };
	cv::Mat L(3, sz, CV_8UC(1), cv::Scalar::all(0)); // creating a 2x2x2 3D array
	// std::cout << " 2.Use C/C++ arrays and initialize via constructor ->  L = " << cv::format(L, cv::Formatter::FMT_MATLAB) << std::endl << std::endl;
	// NOTE: the above commented line doesnt work because opencv doesnt have a method to cout 3D matrixes 
	// For more info visit : http://stackoverflow.com/questions/27891008/opencv-3-0-printing-mat?newreg=bf634e0967b14a6094d228f1fedc6043

	// 3.Using create()+++
	F.create(4,4,CV_8UC(1));
	std::cout << " 3.Using create() ->  F = " << cv::format(F, cv::Formatter::FMT_MATLAB) << std::endl << std::endl;

	// 4.Matlab style initializers
	cv::Mat R = cv::Mat::eye(4,4,CV_64F);
	cv::Mat Z = cv::Mat::zeros(4, 4, CV_32F);
	cv::Mat O = cv::Mat::ones(4, 4, CV_8UC1);

	std::cout << " 4.Matlab style initializers -> eye R   = " << cv::format(R, cv::Formatter::FMT_MATLAB) << std::endl << std::endl;
	std::cout << "   Matlab style initializers -> zeros Z = " << cv::format(Z, cv::Formatter::FMT_MATLAB) << std::endl << std::endl;
	std::cout << "   Matlab style initializers -> ones O  = " << cv::format(O, cv::Formatter::FMT_MATLAB) << std::endl << std::endl;


	std::cin.get();

	return 0;
}

