// testDoenhillSolver_OpenCV.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#include "opencv2\core\optim.hpp"

static void solverInit(cv::Ptr<cv::DownhillSolver> solver, cv::Ptr<cv::MinProblemSolver::Function> ptr_F, cv::Mat& x_init_centroid, cv::Mat& step )
{
	solver->setFunction(ptr_F); // points to the function to be minimized
	int ndim = MAX(step.cols, step.rows);
	solver->setInitStep(step);
	cv::Mat settedStep;
	solver->getInitStep(settedStep);
	double result = solver->minimize(x_init_centroid); 	 
	std::cout << "The resulting minimum value is : " << result << std::endl;
	std::cout << "The value of the coeffs are : " << x_init_centroid << std::endl;
	
}

class SphereF:public cv::MinProblemSolver::Function
{
public:
	std::vector<unsigned long> co;
	int getDims() const { return 2; }
	double calc(const double* x) const
	{
		//std::cout <<"c1,c0 = " << co.at(0) <<" , "<<co.at(1) <<std::endl;
		return co.at(0)*(( x[1] - x[0] * x[0])) * (x[1] - x[0] * x[0]) + (co.at(1) * (1 - x[0] * x[0]));
	}

	SphereF(std::vector<unsigned long> coef)
	{
		co = coef;
	}
};

int main()
{
	std::vector<unsigned long> coeffs;
	coeffs.push_back(100);
	coeffs.push_back(1);
	cv::Ptr<cv::DownhillSolver> solver = cv::DownhillSolver::create(); // create a 
	cv::Ptr<cv::MinProblemSolver::Function> ptr_F = cv::makePtr<SphereF>(coeffs);
	cv::Mat x0 = (cv::Mat_<double>(1,2) << -1.2,1.0);
	cv::Mat step = (cv::Mat_<double>(2, 1) << -0.1, -0.1); 
	solverInit(solver, ptr_F, x0, step);
	
	int temp;
	std::cin >> temp;

	return 0;
}

