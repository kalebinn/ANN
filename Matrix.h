/*
 * Matrix.h
 *
 *  Created on: Jun 10, 2019
 *      Author: Kalebin
 */

#ifndef MATRIX_H_
#define MATRIX_H_

namespace KR_Matrix
{

class Matrix
{
	public:
		Matrix(int rows, int cols); // constructor
		Matrix (char *input_file);
		Matrix dotProduct(Matrix arg);
		Matrix elementMult(Matrix arg);
		Matrix operator= (Matrix arg);
		Matrix operator+ (Matrix arg);
		Matrix operator- (Matrix arg);
	private:
		int nRows;
		int nCols;
		double ** A; //pointer to pointer to multidim array
};

}

#endif /* MATRIX_H_ */
