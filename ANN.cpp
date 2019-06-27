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

	this-> activationMatrices = new KR_Matrix::Matrix [nHiddenLayers];
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

	this-> activationMatrices = new KR_Matrix::Matrix [nHiddenLayers];
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

void ANN::readBiasses(std::string *file_names)
{
	for (int i = 0; i < this->nHiddenLayers+1; i++)
	{


	}
}

void ANN::readWeights(std::string *file_names)
{
	std::string temp;

}



KR_Matrix::Matrix ANN::forwardPropagation(KR_Matrix::Matrix inputMatrix)
{
	KR_Matrix::Matrix output(0,0);

	if ((int)inputMatrix.getnRows() != this->nSamples)
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
			this->summations[i] = inputMatrix * this->weights[i];
			this->activationMatrices[i] = ANN::Activate(this->activationFunctions[i], this->summations[i]);
		}
		else if(i == nHiddenLayers)
		{
			// last hidden layer | output layer
			this->summations[i] = inputMatrix * this->weights[i];
			this->activationMatrices[i] = ANN::Activate("linear", this->summations[i]);
		}
		else
		{
			// hiddenlayer[i-1] | hiddenlayer[i]
			this->summations[i] = this->activationMatrices[i-1] * this->weights[i];
			this->activationMatrices[i] = ANN::Activate(this->activationFunctions[i], this->summations[i]);
		}
	}
	output = this->activationMatrices[nHiddenLayers];


	return output;
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
			this->activationMatrices[i] = temp;
		}
		else
		{
			KR_Matrix::Matrix temp (this->nSamples, this->neuronsPerHiddenLayer[i]);
			this->activationMatrices[i] = temp;
		}
	}
}
double ReLU(double z)
{
	if (z  <= 0 )
	{
		return 0;
	}
	else
	{
		return z;
	}
}

double Sigmoid(double z)
{
	double result;
	result = 1/(1+exp(-z));

	if (result > 0.9)
	{
		return 1;
	}
	else if(result < 0.1)
	{
		return 0;
	}

	return result;
}
double Step(double z)
{
	if (z > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}
double Tanh(double z)
{
	double result;
	result = tanh(z);
	if (result > 0.9)
	{
		return 1;
	}
	else if(result < 0.1)
	{
		return 0;
	}
	return result;
}

double leakyReLU(double z, double a)
{
	double result;
	if (z > 0)
	{
		result = z;
	}
	else
	{
		result = a * z;
	}
	return result;
}
KR_Matrix::Matrix ANN::Activate(std::string functionType, KR_Matrix::Matrix arg)
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
	double activatedElement;

	for (std::size_t i = 0; i < arg.getnRows(); i++)
	{
		for (std::size_t j = 0 ;j < arg.getnCols(); j++)
		{
			elementValue = arg.getElement(i,j);
			if (functionType.compare("SIGMOID") == 0)
			{
				activatedElement = Sigmoid(elementValue);
			}
			else if(functionType.compare("STEP") == 0)
			{
				activatedElement = Step(elementValue);
			}
			else if (functionType.compare("TANH") == 0)
			{
				activatedElement = Tanh(elementValue);
			}
			else if (functionType.compare("LEAKYRELU") == 0)
			{
				activatedElement = leakyReLU(elementValue, leakyRate);
			}
			else if (functionType.compare("LINEAR") == 0)
			{
				activatedElement = elementValue;
			}
			else
			{
				// default is relu
				activatedElement = ReLU(elementValue);
			}
			activatedMatrix.setElement(i,j,activatedElement);
		}
	}



	return activatedMatrix;
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
	delete [] this->activationMatrices;
	delete [] this->activationFunctions;
	delete [] this->summations;
	delete [] this->weights;
	delete [] this->biasses;
}
} /* namespace KR_ANN */
