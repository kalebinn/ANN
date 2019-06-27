/*
 * ANN.h
 *
 *  Created on: Jun 12, 2019
 *      Author: Kalebin
 */

#ifndef ANN_H_
#define ANN_H_

#include <string>
#include "Matrix.h"

namespace KR_ANN {

class ANN {
	public:
		ANN(int inputSize, int outputSize, int nHiddenLayers, int *neuronsPerHiddenLayer, double learningRate, std::string activationFunction);
		ANN(int inputSize, int outputSize, int nHiddenLayers, int *neuronsPerHiddenLayer, double learningRate, std::string *activationFunction);

		void readWeights(std::string file_name);
		void readBiasses(std::string file_name);
		KR_Matrix::Matrix forwardPropagation(KR_Matrix::Matrix inputMatrix);

		void createSummationMatrix();
		void createActivationMatrix();
		KR_Matrix::Matrix Activate(std::string functionType, KR_Matrix::Matrix arg);

		friend double ReLU (double z);
		friend double Sigmoid (double z);
		friend double Step (double z);
		friend double Tanh(double z);
		friend double leakyReLU(double z, double a);

		void normalDistMatrix(KR_Matrix::Matrix &matrix, double expectation, double stdev);
		void printMembers(void);

		~ANN(); // destructor
	private:
		int nSamples = 0;
		double leakyRate = 0.01;

		// HYPERPARAMETERS //
		int inputSize;
		int outputSize;
		int nHiddenLayers; // number of hidden layers
		int *neuronsPerHiddenLayer; // pointer to neuronsPerHiddenLayer array (of size nHiddenLayers).
		double learningRate;
		std::string activationType;
		std::string *activationFunctions;

		KR_Matrix::Matrix *summations;
		KR_Matrix::Matrix *activationMatrices;

		KR_Matrix::Matrix inputMatrix;
		KR_Matrix::Matrix *weights;
		KR_Matrix::Matrix *biasses;
		KR_Matrix::Matrix outputMatrix ;
};

} /* namespace KR_ANN */

#endif /* ANN_H_ */
