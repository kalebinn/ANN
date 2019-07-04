/*
 * ANN.cpp
 *
 *  Created on: Jun 12, 2019
 *      Author: Kalebin
 */

#include "ANN.h"

#include <assert.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <locale>
#include "Matrix.h"

namespace KR_ANN {

ANN::ANN (int nFeatures, int outputSize, int nHiddenLayers, int *neuronsPerHiddenLayer, double learningRate, std::string activationFunction)
{

	this-> nFeatures = nFeatures;
	this-> outputSize = outputSize;

	KR_Matrix::Matrix input(1,nFeatures);
	this->inputMatrix = input;
	KR_Matrix::Matrix output(1,outputSize);
	this->outputMatrix = output;

	this-> nHiddenLayers = nHiddenLayers;
	this-> learningRate = learningRate;
	//this-> activationType = activationFunction;

	this-> activationMatrices = new KR_Matrix::Matrix [nHiddenLayers+1];
	this-> summations = new KR_Matrix::Matrix [nHiddenLayers+1];

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
			KR_Matrix::Matrix weight_temp(nFeatures, neuronsPerHiddenLayer[i]);
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

ANN::ANN (int nFeatures, int outputSize, int nHiddenLayers, int *neuronsPerHiddenLayer, double learningRate, std::string *activationFunction)
{
	this-> nFeatures = nFeatures;
	this-> outputSize = outputSize;

	KR_Matrix::Matrix input(1,nFeatures);
	this->inputMatrix = input;
	KR_Matrix::Matrix output(1,outputSize);
	this->outputMatrix = output;

	this-> nHiddenLayers = nHiddenLayers;
	this-> learningRate = learningRate;

	this-> activationMatrices = new KR_Matrix::Matrix [nHiddenLayers+1];
	this-> summations = new KR_Matrix::Matrix [nHiddenLayers+1];

	this-> activationFunctions = new std::string [nHiddenLayers+1];
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
			KR_Matrix::Matrix weight_temp(nFeatures, neuronsPerHiddenLayer[i]);
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

KR_Matrix::Matrix ANN::forwardPropagation(KR_Matrix::Matrix inputMatrix, std::string *weights, std::string *baises)
{
	std::string summationsFile = "Summations.txt";
	std::string activationsFile = "Activations.txt";
	std::string outputFile = "output.txt";

	// if the number of samples is greater than nSamples, create new Summations and Activation Matrices
	if ((int)inputMatrix.getnRows() != this->nSamples)
	{
		this->nSamples = inputMatrix.getnRows();
		createSummationsandActivations();

	}
	// the output matrix is of size nSample by outputSize
	KR_Matrix::Matrix output(this->nSamples,this->outputSize);

	std::cout << "First hidden layer:" << std::endl;
	this->summations[0] = (inputMatrix * this->weights[0]) + this->biasses[0];
	std::cout << "Summation" << std::endl;
	this->summations[0].printMatrix();
	this->activationMatrices[0] = ANN::Activate(this->activationFunctions[0], this->summations[0]);
	std::cout << "Activations" << std::endl;
	this->activationMatrices[0].printMatrix();

	for (int i = 1 ; i < nHiddenLayers+1; i++)
	{
		if(i == nHiddenLayers)
		{
			// last hidden layer | output layer
			this->summations[i] = (this->activationMatrices[i-1] * this->weights[i]) + this->biasses[i];
			this->summations[i].printMatrix(summationsFile);
			std::cout << "Summation" << std::endl;
			this->activationMatrices[i] = ANN::Activate("linear", this->summations[i]);
		}
		else
		{
			// hiddenlayer[i-1] | hiddenlayer[i]
			this->summations[i] = (this->activationMatrices[i-1] * this->weights[i]) + this->biasses[i];
			this->summations[i].printMatrix("Summations.txt");
			std::cout << "Summation" << std::endl;
			this->summations[i].printMatrix();
			this->activationMatrices[i] = ANN::Activate(this->activationFunctions[i], this->summations[i]);
			std::cout << "Activation" << std::endl;
			this->activationMatrices[i].printMatrix();
		}
	}

	output = this->activationMatrices[nHiddenLayers];
	output.printMatrix();
	return output;
}

void ANN::createSummationsandActivations()
{
	for (int i = 0; i < this->nHiddenLayers; i++)
	{
		KR_Matrix::Matrix temp (this->nSamples, this->neuronsPerHiddenLayer[i]);
		this->summations[i] = temp;
		this->activationMatrices[i] = temp;
	}

	KR_Matrix::Matrix temp (this->nSamples, this->outputSize);
	this->summations[this->nHiddenLayers] = temp;
	this->activationMatrices[this->nHiddenLayers] = temp;
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
	else
	{
		return result;
	}
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
				std::cout << "WARNING: Unsupported activation function type - Using ReLU " << std::endl;
				std::cout << "SUGGESTION: Supported activations - LeakyReLU, ReLU, Sigmoid, Step, Tanh" << std::endl << std::endl;
				activatedElement = ReLU(elementValue);
			}
			activatedMatrix.setElement(i,j,activatedElement);
		}
	}



	return activatedMatrix;
}

int  ANN::readBiasses(std::string *biasFileNames)
{
	/*
	for (int i = 0; i < this->nHiddenLayers + 1; i++)
	{
		try
		{
			KR_Matrix::Matrix temp(biasFileNames[i]);
			if (temp.getnRows() != 1 || this->biasses[i].getnCols() != temp.getnCols())
			{
				throw 66; // decimal representation of UNICODE for letter "B"
			}
			this->biasses[i] = temp;
		}
		catch(int x)
		{
			std::cout << "ERROR #" << x <<": CHECK BIAS FILE NUMBER " << i+1 << std::endl;
			std::cout << "PROPER DIMENSIONS ARE " << 1 << " BY " << this->biasses[i].getnCols() << std::endl;
			return x;
		}
	}
	*/

	return 0;
}
int ANN::readBias(std::string file_name)
{
	std::ifstream biasFile (file_name, std::ios::in);
	int nMatrices;
	biasFile >> nMatrices;

	// check if biasFile has proper number of matrices
	try
	{
		if (nMatrices != nHiddenLayers + 1)
		{
				throw 42; // error number for mismatched matrix amounts
		}
	}
	catch (int errNum)
	{
		std::cout << "FATAL ERROR: " << errNum << " - number of matrices in " << file_name
				<< " does not match number of hidden layers + output layer" << std::endl;
		return errNum; // do not proceed with reading the file
	}

	// read in matrices if good

	double elementVal = 0;
	int tempRows = 0;
	int tempCols = 0;
	for (int i = 0; i < nMatrices; i++)
	{
		biasFile >> tempRows >> tempCols; // read in nRows and nCols

		KR_Matrix::Matrix temp(tempRows, tempCols); // create matrix
		try // check if dimensions are ok
		{
			if (this->biasses[i].getnRows() != temp.getnRows() || this->biasses[i].getnCols() != temp.getnCols())
			{
				throw 66;  //decimal representation of UNICODE for "B" (BIAS ERROR)
			}
		}
		catch(int errNum)
		{
			if (i < nHiddenLayers)
			{
				std::cout << "FATAL ERROR: " << errNum << " Error in bias matrix dimensions for hidden layer #"<< i + 1 << std::endl;
			}
			else
			{
				std::cout << "FATAL ERROR: " << errNum << " Error in bias matrix dimensions for output layer" << std::endl;
			}
			std::cout << "SUGGESTION: proper dimensions should be "
									<< this->biasses[i].getnRows() << " by "
									<<  this->biasses[i].getnCols() << std::endl;
			temp.~Matrix(); // manually destroy matrix
			return errNum; // do not proceed
		}

		// fill the bias matrix
		for (int j = 0; j < tempRows; j++)
		{
			for (int k = 0; k < tempCols; k++)
			{
				biasFile >> elementVal;
				this->biasses[i].setElement(j,k,elementVal);
			}
		}
	}
	return 0;
}

void ANN::readWeights(std::string *weightFileNames)
{
	for (int i = 0; i < this->nHiddenLayers + 1; i++)
	{
		//std::cout << "i = " << i << "\tfile name = " << weightFileNames[i]<< std::endl;
		KR_Matrix::Matrix temp(weightFileNames[i]);
		assert(this->weights[i].getnRows() == temp.getnRows() && this->weights[i].getnCols() == temp.getnCols());
		this->weights[i] = temp;
	}
}

int ANN::readWeights(std::string fileName)
{
	std::ifstream weightFile (fileName, std::ios::in);
	int nMatrices;
	weightFile >> nMatrices;

	// check if weightFile has proper number of matrices
	try
	{
		if (nMatrices != nHiddenLayers + 1)
		{
				throw 42; // error number for mismatched matrix amounts
		}
	}
	catch (int errNum)
	{
		std::cout << "FATAL ERROR: " << errNum << " - number of matrices in " << fileName
				<< " does not match number of hidden layers + output layer" << std::endl;
		std::cout << "SUGGESTION: Neural Network has " << this->nHiddenLayers << " Hidden layers"
				<< "and 1 output layer. Try " << this->nHiddenLayers+1 << " Weight Matrices."<< std::endl;
		return errNum; // do not proceed with reading the file
	}
	// read in matrices if good

	double elementVal = 0;
	int tempRows = 0;
	int tempCols = 0;
	for (int i = 0; i < nMatrices; i++)
	{
		weightFile >> tempRows >> tempCols;
		KR_Matrix::Matrix temp(tempRows, tempCols);
		try // check if dimensions are ok
		{
			if (this->weights[i].getnRows() != temp.getnRows() || this->weights[i].getnCols() != temp.getnCols())
			{
				throw 66;  //decimal representation of UNICODE for "B" (BIAS ERROR)
			}
		}
		catch(int errNum)
		{
			if (i < nHiddenLayers)
			{
				std::cout << "FATAL ERROR: " << errNum << " Error in bias matrix dimensions for hidden layer #"<< i + 1 << std::endl;
			}
			else
			{
				std::cout << "FATAL ERROR: " << errNum << " Error in bias matrix dimensions for output layer" << std::endl;
			}
			std::cout << "SUGGESTION: proper dimensions should be "
									<< this->weights[i].getnRows() << " by "
									<<  this->weights[i].getnCols() << std::endl;
			temp.~Matrix(); // manually destroy matrix
			return errNum; // do not proceed
		}

		// fill the weight matrix array
		for (int j = 0; j < tempRows; j++)
		{
			for (int k = 0; k < tempCols; k++)
			{
				weightFile >> elementVal;
				this->weights[i].setElement(j,k,elementVal);
			}
		}

	}
	return 0;

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

	std::cout << "Number of Features = " << this->nFeatures << std::endl;
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
