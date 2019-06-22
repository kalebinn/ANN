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
		ANN(int inputSize, int outputSize, int nHiddenLayers, int *neuronsPerLayer, double learningRate, std::string activationFunction);
		ANN(int inputSize, int outputSize, int nHiddenLayers, int *neuronsPerLayer, double learningRate, std::string *activationFunction);

		KR_Matrix::Matrix forwardPropagation(KR_Matrix::Matrix inputMatrix, KR_Matrix::Matrix *weightMatrix,
				KR_Matrix::Matrix *biasMatrix, KR_Matrix::Matrix outputMatrix);

		double Activate();

		void normalDistMatrix(KR_Matrix::Matrix &matrix, double expectation, double stdev);
		void printMembers(void);

		~ANN(); // destructor
	private:
		// HYPERPARAMETERS //
		int inputSize;
		int outputSize;
		int nHiddenLayers; // number of hidden layers
		int *neuronsPerLayer; // pointer to neuronsPerLayer array (of size nHiddenLayers).
		double learningRate;
		std::string activationType;
		std::string *activationFunctions;

		KR_Matrix::Matrix *summations;
		KR_Matrix::Matrix *activationResults;

		KR_Matrix::Matrix inputMatrix;
		KR_Matrix::Matrix *weights;
		KR_Matrix::Matrix *biasses;
		KR_Matrix::Matrix outputMatrix ;
};

} /* namespace KR_ANN */

#endif /* ANN_H_ */
