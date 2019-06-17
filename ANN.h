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
		ANN();
	private:
		// HYPERPARAMETERS //
		int inputSize;
		int outputSize;
		int nLayers;
		int *neuronsPerLayer;
		double learningRate;
		std::string activationFunction;

};

} /* namespace KR_ANN */

#endif /* ANN_H_ */
