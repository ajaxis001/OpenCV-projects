#pragma once
#include "opencv2\core\optim.hpp"

namespace funcStuff 
{
	// Declaring Function to initialize the solver for the given function to be optimized
	void solverInit(cv::Ptr<cv::DownhillSolver> solver, cv::Ptr<cv::MinProblemSolver::Function> ptr_F, cv::Mat& x_init_centroid, cv::Mat& step);

	// Declaring Class for the given function to be optimized
	class RosenbrockF :public cv::MinProblemSolver::Function
	{
	public:
		std::vector<unsigned long> co;
		int getDims() const;
		double calc(const double* x) const;
		RosenbrockF(std::vector<unsigned long> coef);
	};

}