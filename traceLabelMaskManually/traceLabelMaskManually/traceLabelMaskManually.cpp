/* traceLabelMaskManually.cpp : Defines the entry point for the console application.
	
	This Program is used to manually draw the mask for the labels on the pill bottle images
	and save them in a seperate image

Ref: http://answers.opencv.org/question/96817/how-to-create-mask-from-an-image-in-opencv/
*/

#include "stdafx.h"
#include <iostream>

#include "opencv2\opencv.hpp"


cv::Mat Img_src, Img_clone; // Global vars to store the image we work on a copy of it
cv::Mat Img_gray;       // Global var to store a grayscaled image of our image
	
bool mouseDown; // bool var set to true if a mouse button is held down

// A vector of a Vector of points 
// USAGE :  std::vector => http://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c4027/C-Tutorial-A-Beginners-Guide-to-stdvector-Part-1.htm
std::vector<std::vector<cv::Point>> contours; // USAGE : http://stackoverflow.com/questions/33458362/opencv-findcontours-why-do-we-need-a-vectorvectorpoint-to-store-the-cont
											  // e.g.  contours[x][y].x;  xth contours yth values x-coordinate
											  //       contours[x][y].y;  yth contours yth values y-coordinate

// A vector of points
std::vector<cv::Point> pts; 
	
void onMouse(int event, int x, int y, int flags, void* userdata)
{
	cv::Mat img = *((cv::Mat*)userdata); // recasting the void* userdata to a Mat type pointer 
										 // USAGE : http://www.learncpp.com/cpp-tutorial/613-void-pointers/
	
	// checking if the left mouse button is pressed down
	if (event == cv::EVENT_LBUTTONDOWN) 
	{
		mouseDown = true; 
		contours.clear(); // USAGE : vector::clear() => Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
		pts.clear();
	}
	
	// checking if left mouse button is released
	if (event == cv::EVENT_LBUTTONUP) 
	{
		mouseDown = false;
		if (pts.size() > 2) // USAGE : vector::size() => Returns the number of elements in the vector. 
		{
			cv::Mat mask(img.size(), CV_8UC1); // create an Mat var to hold the mask (it is a single channel Mat var)
			mask = 0; // mask is a Mat object with a header and the assignment operator only affects the header and not the data 
			          // so I assume this means that theres nothing in the header and hence is just pointing to some location in memeory 
			contours.push_back(pts); // USAGE : vector::push_back => Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.
			cv::drawContours(mask, contours, 0,cv::Scalar(255),-1); // draw contours and fill them (check function hover help)
			cv::Mat masked(img.size(), CV_8UC3,cv::Scalar(255,255,255)); // create a Mat var to hold the masked image
			Img_src.copyTo(masked, mask); // here, Wherever "mask" is non-zero it copies only those values in "Img_src" to the var "masked" ("Img_src is unaffected")
			Img_src.copyTo(Img_clone);    
			cv::imshow("masked", masked); 
		}
	}

	if (mouseDown)
	{
		if (pts.size() > 2)
			cv::line(img, cv::Point(x, y), pts[pts.size() - 1], cv::Scalar(0, 255, 0));

		pts.push_back(cv::Point(x, y));
		cv::imshow("Create Mask", img);
	}

}


int main(int argc, char* argv[])
{
	// Sanity check 1
	if(argc < 2)
	{
		std::cout << "ERROR : file_name image_name" << std::endl;
		return -1;
	}

	// Reading in the image
	Img_src = cv::imread(argv[1], cv::IMREAD_COLOR);

	// Sanity check 2
	if (Img_src.empty() == true)
	{
		std::cout << "ERROR : Image "<< argv[1]<<" could not be loaded" << std::endl;
		return -2;
	}
	
	// Converting image to grayscale and making a copy
	cv::cvtColor(Img_src, Img_gray, cv::COLOR_BGR2GRAY);
	
	cv::namedWindow("Create Mask", cv::WINDOW_AUTOSIZE);
	Img_clone = Img_src.clone();
	cv::setMouseCallback("Create Mask", onMouse, &Img_clone);
	cv::imshow("Create Mask", Img_src);

	cv::waitKey(0);
	return 0;
}

 