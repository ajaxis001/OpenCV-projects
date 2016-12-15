#include "prog_funcs.h"

cv::Mat& ScanImageAndReduceC(cv::Mat& I, const uchar* table)
{
	// accept only char type matrices
	CV_Assert(I.depth() != sizeof(uchar));
	int channels = I.channels();

	int nRows = I.rows;
	int nCols = I.cols * channels;

	if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}

	int i, j;
	uchar* p; // a pointer to an uchar var
	for (i = 0; i < nRows; ++i)
	{
		// p is a uchar pointer to the first element i'th row of the Mat obj
		p = I.ptr<uchar>(i); // ref : http://docs.opencv.org/2.4/modules/core/doc/basic_structures.html#mat-ptr
		for (j = 0; j < nCols; ++j)
		{
			p[j] = table[p[j]]; // accessing the j'th col of the i'th row of the image I
			//  here what happens is p[j] - holds the value at the 
		
		}
	}

}


cv::Mat& ScanImageAndReduceIterator(cv::Mat& I, const uchar* const table)
cv::Mat& ScanImageAndReduceRandomAccess(cv::Mat& I, const uchar* table)
