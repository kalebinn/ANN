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
	int NPL[5] = {1,2,3,4,5};
	int numberOfHiddenLayers = 5;
	int inputsize = 2;
	int outputsize = 1;
	double learning = 0.1;
	std::string actF = "ReLU";

	KR_ANN::ANN Network1(inputsize, outputsize,numberOfHiddenLayers, NPL, learning, actF);
	Network1.printMembers();
	return 0;
}
