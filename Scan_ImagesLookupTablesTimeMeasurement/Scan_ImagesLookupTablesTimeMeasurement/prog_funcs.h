#pragma once
// Header file for all the programs used in Scan_ImagesLookupTablesTimeMeasurement.cpp
#include "opencv2\opencv.hpp"

cv::Mat& ScanImageAndReduceC(cv::Mat& I, const uchar* table);
cv::Mat& ScanImageAndReduceIterator(cv::Mat& I, const uchar* const table); // const uchar* const - usage: http://stackoverflow.com/questions/890535/what-is-the-difference-between-char-const-and-const-char
cv::Mat& ScanImageAndReduceRandomAccess(cv::Mat& I, const uchar* table);
