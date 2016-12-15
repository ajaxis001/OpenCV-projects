/* tryingCommandlineParser.cpp : Defines the entry point for the console application.
	Program to understand the basics of the opencv commandline parser

	Ref: http://docs.opencv.org/trunk/d0/d2e/classcv_1_1CommandLineParser.html
*/

#include "stdafx.h"
#include <iostream>

#include "opencv2\opencv.hpp"

int main(int argc, char* argv[])
{
	/*
	Keys syntax
	  The keys parameter is a string containing several blocks, each one is enclosed in curley braces and describes one argument.
	  Each argument contains three parts separated by the | symbol:

	  1.argument names is a space-separated list of option synonyms (to mark argument as positional, prefix it with the @ symbol)
	  2.default value will be used if the argument was not provided (can be empty)
	  3.help message (can be empty)
	*/

	const cv::String keys =
		"{help h usage ? |      | print this message}"
		"{@image1        |      | image1 for comaparing}"
		"{@image2        |<none>| image2 for comparing"
		"{path           |.     | path to file}"
		"{N              |100   | some integer param}"
		"{ts timestamp   |      | use time stamp}"
		;

	// creating a commandline parser object
	cv::CommandLineParser parser(argc, argv, keys);
	parser.about("Commandline Parser test 1.0"); // Gets printed at application call before the above argument table

	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}

	int N = parser.get<int>("N");
	cv::String path = parser.get<cv::String>("path");

	bool use_time_stamp = parser.has("timestamp");

	cv::String img1 = parser.get<cv::String>(0);
	cv::String img2 = parser.get<cv::String>(1);

	if (parser.check() == true)
	{
		parser.printErrors();
		return 0;
	}

	return 0;
}