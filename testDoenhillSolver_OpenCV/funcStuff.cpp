#include "stdafx.h"
#include <iostream> 
#include "funcStuff.h"

namespace funcStuff 
{
	// Defining the downhill solver initializer function
	void solverInit(cv::Ptr<cv::DownhillSolver> solver, cv::Ptr<cv::MinProblemSolver::Function> ptr_F, cv::Mat& x_init_centroid, cv::Mat& step)
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

	
	// Declaring all the functions used inside the function class
		int RosenbrockF::getDims() const { return 2; }
		
		double RosenbrockF::calc(const double* x) const
		{
			//std::cout <<"c1,c0 = " << co.at(0) <<" , "<<co.at(1) <<std::endl;
			return (co.at(0)*((x[1] - x[0] * x[0])) * (x[1] - x[0] * x[0])) + ((co.at(1) * (1 - x[0]) *(1 - x[0])));
		}

		RosenbrockF::RosenbrockF(std::vector<unsigned long> coef)
		{
			co = coef;
		}
	


}