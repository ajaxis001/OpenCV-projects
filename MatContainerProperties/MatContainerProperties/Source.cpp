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

	// Creating Mat objects explicitly
	// 1.Mat() constructor
	cv::Mat M(2, 2, CV_8UC3, cv::Scalar(0, 255, 255));
	std::cout << " 1.Mat() constructor ->  M = " << M <<std::endl;

	//2.Use C/C++ arrays and initialize via constructor
	int sz[3] = {2,2,2};
	cv::Mat L(3, sz, CV_8UC1, cv::Scalar::all(0));
	std::cout << " 2.Use C/C++ arrays and initialize via constructor ->  L = " << L << std::endl;

	std::cin.get();

	return 0;
}

