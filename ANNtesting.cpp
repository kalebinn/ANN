/*
 * ANNtesting.cpp
 *
 *  Created on: Jun 19, 2019
 *      Author: Kalebin
 */

// this file is used to test the Artificial Neural network.

#include <iostream>
#include <string>

#include "ANN.h"
int main()
{
	int NPL[6] = {1,2,3,4,5,7};
	int numberOfHiddenLayers = 5;
	int inputsize = 2;
	int outputsize = 1;
	double learning = 0.1;
	std::string actF = "ReLU";
	std::string actFs[5] = {"ReLU","Sigmoid","ReLU","TanH","Sigmoid"};

	KR_ANN::ANN Network1(inputsize, outputsize,numberOfHiddenLayers, NPL, learning, actFs);
	Network1.printMembers();
	return 0;
}
