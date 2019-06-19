/*
 * ANN.cpp
 *
 *  Created on: Jun 12, 2019
 *      Author: Kalebin
 */

#include "ANN.h"

#include <string>
#include "Matrix.h"

namespace KR_ANN {

ANN::ANN (int inputSize, int outputSize, int nHiddenLayers, int *neuronsPerLayer, double learningRate, std::string activationFunction)
{
	this-> inputSize = inputSize;
	this-> outputSize = outputSize;
	this-> nHiddenLayers = nHiddenLayers;
	//this-> neuronsPerLayer = neuronsPerLayer;
	this-> learningRate = learningRate;
	this-> activationType = activationFunction;

	this-> activationFunctions = NULL;

	this-> neuronsPerLayer = new int [nHiddenLayers];
	this-> activationResults = new KR_Matrix::Matrix [nHiddenLayers];
	this-> summations = new KR_Matrix::Matrix [nHiddenLayers];

	for (int i = 0; i < nHiddenLayers; i++)
	{
		this-> neuronsPerLayer[i] = neuronsPerLayer[i];
	}

	this->weights = new KR_Matrix::Matrix [nHiddenLayers+1];
	this->biasses = new KR_Matrix::Matrix [nHiddenLayers+1];
}

KR_Matrix::Matrix ANN::forwardPropagation(KR_Matrix::Matrix inputMatrix, KR_Matrix::Matrix *weightMatrix,
				KR_Matrix::Matrix *biasMatrix, KR_Matrix::Matrix outputMatrix)
{
	KR_Matrix::Matrix output(0,0);



	return output;
}


} /* namespace KR_ANN */
