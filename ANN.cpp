/*
 * ANN.cpp
 *
 *  Created on: Jun 12, 2019
 *      Author: Kalebin
 */

#include "ANN.h"

#include <assert.h>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <locale>
#include "Matrix.h"

namespace KR_ANN {

ANN::ANN (int inputSize, int outputSize, int nHiddenLayers, int *neuronsPerHiddenLayer, double learningRate, std::string activationFunction)
{
	this-> inputSize = inputSize;
	this-> outputSize = outputSize;

	KR_Matrix::Matrix input(1,inputSize);
	this->inputMatrix = input;
	KR_Matrix::Matrix output(1,outputSize);
	this->outputMatrix = output;

	this-> nHiddenLayers = nHiddenLayers;
	this-> learningRate = learningRate;
	//this-> activationType = activationFunction;

	this-> activationResults = new KR_Matrix::Matrix [nHiddenLayers];
	this-> summations = new KR_Matrix::Matrix [nHiddenLayers];

	this-> activationFunctions = new std::string [nHiddenLayers + 1];
	this-> neuronsPerHiddenLayer = new int [nHiddenLayers + 1];


	for (int i = 0; i < nHiddenLayers; i++)
	{
		this-> neuronsPerHiddenLayer[i] = neuronsPerHiddenLayer[i];
		this-> activationFunctions[i] = activationFunction;
	}
	this->weights = new KR_Matrix::Matrix [nHiddenLayers+1];
	this->biasses = new KR_Matrix::Matrix [nHiddenLayers+1];


	// initialize the weights as a normal distribution with mu = 0, sigma^2 = 0.01;
	double expectation = 0;
	double standardDev = 0.01;
	for (int i = 0; i < nHiddenLayers+1; i++)
	{
		if (i == 0)
		{
			KR_Matrix::Matrix weight_temp(inputSize, neuronsPerHiddenLayer[i]);
			this->weights[i] = weight_temp;
			KR_Matrix::Matrix bias_temp(1, neuronsPerHiddenLayer[i]);
			this->biasses[i] = bias_temp;
		}
		else if (i == nHiddenLayers)
		{
			KR_Matrix::Matrix weight_temp(neuronsPerHiddenLayer[i-1],outputSize);
			this->weights[i] = weight_temp;
			KR_Matrix::Matrix bias_temp(1, outputSize);
			this->biasses[i] = bias_temp;
		}
		else
		{
			KR_Matrix::Matrix weight_temp(neuronsPerHiddenLayer[i-1],neuronsPerHiddenLayer[i]);
			this->weights[i] = weight_temp;
			KR_Matrix::Matrix bias_temp(1, neuronsPerHiddenLayer[i]);
			this->biasses[i] = bias_temp;
		}
		normalDistMatrix(this->weights[i],expectation,standardDev);
		normalDistMatrix(this->biasses[i],expectation,standardDev);
	}
}

ANN::ANN (int inputSize, int outputSize, int nHiddenLayers, int *neuronsPerHiddenLayer, double learningRate, std::string *activationFunction)
{
	this-> inputSize = inputSize;
	this-> outputSize = outputSize;

	KR_Matrix::Matrix input(1,inputSize);
	this->inputMatrix = input;
	KR_Matrix::Matrix output(1,outputSize);
	this->outputMatrix = output;

	this-> nHiddenLayers = nHiddenLayers;
	this-> learningRate = learningRate;

	this-> activationResults = new KR_Matrix::Matrix [nHiddenLayers];
	this-> summations = new KR_Matrix::Matrix [nHiddenLayers];

	this-> activationFunctions = new std::string [nHiddenLayers];
	this-> neuronsPerHiddenLayer = new int [nHiddenLayers];
	for (int i = 0; i < nHiddenLayers; i++)
	{
		this-> neuronsPerHiddenLayer[i] = neuronsPerHiddenLayer[i];
		this-> activationFunctions[i] = activationFunction[i];
	}

	this->weights = new KR_Matrix::Matrix [nHiddenLayers+1];
	this->biasses = new KR_Matrix::Matrix [nHiddenLayers+1];

	// initialize the weights as a normal distribution with mu = 0, sigma^2 = 0.01;
	double expectation = 0;
	double standardDev = 0.01;
	for (int i = 0; i < nHiddenLayers+1; i++)
	{
		if (i == 0)
		{
			KR_Matrix::Matrix weight_temp(inputSize, neuronsPerHiddenLayer[i]);
			this->weights[i] = weight_temp;
			KR_Matrix::Matrix bias_temp(1, neuronsPerHiddenLayer[i]);
			this->biasses[i] = bias_temp;
		}
		else if (i == nHiddenLayers)
		{
			KR_Matrix::Matrix weight_temp(neuronsPerHiddenLayer[i-1],outputSize);
			this->weights[i] = weight_temp;
			KR_Matrix::Matrix bias_temp(1, outputSize);
			this->biasses[i] = bias_temp;
		}
		else
		{
			KR_Matrix::Matrix weight_temp(neuronsPerHiddenLayer[i-1],neuronsPerHiddenLayer[i]);
			this->weights[i] = weight_temp;
			KR_Matrix::Matrix bias_temp(1, neuronsPerHiddenLayer[i]);
			this->biasses[i] = bias_temp;
		}
		normalDistMatrix(this->weights[i],expectation,standardDev);
		normalDistMatrix(this->biasses[i],expectation,standardDev);
	}
}
KR_Matrix::Matrix ANN::forwardPropagation(KR_Matrix::Matrix inputMatrix)
{
	KR_Matrix::Matrix output(0,0);

	if ((int)inputMatrix.getnRows() > this->nSamples)
	{
		this->nSamples = inputMatrix.getnRows();
		createSummationMatrix();
		createActivationMatrix();
	}

	for (int i = 0 ; i < nHiddenLayers+1; i++)
	{
		if (i == 0)
		{
			// input layer | first hidden layer

		}
		else if(i == nHiddenLayers)
		{
			// last hidden layer | output layer
		}
		else
		{
			// hiddenlayer[j-1] | hiddenlayer[j]
		}
	}



	return output;
}

KR_Matrix::Matrix Activate(std::string functionType, KR_Matrix::Matrix arg)
{
	int nRows = arg.getnRows();
	int nCols = arg.getnCols();
	KR_Matrix::Matrix activatedMatrix(nRows, nCols);

	for (std::string::size_type i = 0; i < functionType.length(); i++)
	{
		if (std::islower(functionType[i]))
		{
			functionType[i] = std::toupper(functionType[i]);
		}
	}

	double elementValue;
	if (functionType.compare("RELU") == 0)
	{
		for (unsigned int i = 0; i < arg.getnRows(); i++)
		{
			for (unsigned int j = 0; j < arg.getnCols(); j++)
			{
				elementValue = arg.getElement(i,j);
				if (elementValue  <= 0 )
				{
					activatedMatrix.setElement(i,j,0);
				}
				else
				{
					activatedMatrix.setElement(i,j,elementValue);
				}
			}
		}
	}
	else if (functionType.compare("SIGMOID") == 0)
	{

	}
	else if (functionType.compare("TANH") == 0)
	{

	}
	else
	{
		// default is RELU
	}

	return activatedMatrix;
}

void ANN::createSummationMatrix()
{
	for (int i = 0; i < this->nHiddenLayers+1; i++)
	{
		if (i == nHiddenLayers)
		{
			KR_Matrix::Matrix temp (this->nSamples, this-> outputSize);
			this->summations[i] = temp;
		}
		else
		{
			KR_Matrix::Matrix temp (this->nSamples, this->neuronsPerHiddenLayer[i]);
			this->summations[i] = temp;
		}
	}
}
void  ANN::createActivationMatrix()
{
	for (int i = 0; i < this->nHiddenLayers+1; i++)
	{
		if (i == nHiddenLayers)
		{
			KR_Matrix::Matrix temp (this->nSamples, this-> outputSize);
			this->activationResults[i] = temp;
		}
		else
		{
			KR_Matrix::Matrix temp (this->nSamples, this->neuronsPerHiddenLayer[i]);
			this->activationResults[i] = temp;
		}
	}
}

void ANN::normalDistMatrix(KR_Matrix::Matrix &matrix, double expectation, double stdev)
{
	static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // seed based on time
	srand(seed); // set the seed
	seed = rand(); // make the new seed, a random integer from the seed generated from time

	std::default_random_engine generator (seed); // use the default random engine (enough for our purposes, twister generation not needed)
	std::normal_distribution<double> nDist(expectation, stdev*stdev); // initialize the normal distribution based on stats
	// each element of the matrix gets a number random chosen by a normal distribution
	double value;
	for (unsigned int i = 0; i < matrix.getnRows(); i++)
	{
		for (unsigned int j = 0; j < matrix.getnCols(); j++)
		{
			value = nDist(generator);
			matrix.setElement(i,j, value);
		}
	}
}


void ANN::printMembers(void)
{

	std::cout << "Input size = " << this->inputSize << std::endl;
	std::cout << "Output size = " << this->outputSize << std::endl;
	std::cout << "There are " << this->nHiddenLayers << " Hidden Layers in this Neural Network" << std::endl;
  	for (int i = 0 ; i < this->nHiddenLayers; i++)
	{
		std::cout << "\tHidden Layer #" << i+1 << " has " << this->neuronsPerHiddenLayer[i] << " Neurons."<< std::endl;
		std::cout << "\t\tThis layer uses " << this->activationFunctions[i] << " as the activation function." << std::endl;
	}

  	std::cout << "the weights and biases of each layer are: " << std::endl;
	for (int i = 0 ; i <= this->nHiddenLayers; i++)
	{
		std::cout << "weightMatrix[" << i << "] = " << std::endl << std::endl;
		this->weights[i].printMatrix();
	}

	for (int i = 0 ; i <= this->nHiddenLayers; i++)
	{
		std::cout << "biasMatrix[" << i << "] = " << std::endl << std::endl;
		this->biasses[i].printMatrix();
	}
}

ANN::~ANN()
{
	// deallocate all dynamically allocated member from constructor
	delete [] this->neuronsPerHiddenLayer;
	delete [] this->activationResults;
	delete [] this->activationFunctions;
	delete [] this->summations;
	delete [] this->weights;
	delete [] this->biasses;
}
} /* namespace KR_ANN */
