/*
 * Matrix.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: Kalebin
 */

#include "Matrix.h"

namespace KR_Matrix {

Matrix::Matrix(int rows, int cols)
{
	// TODO: write the constructor
}

Matrix::Matrix (char *input_file)
{
	// TODO : constructor that reads array from input file
}

Matrix Matrix::dotProduct(Matrix arg)
{
	// TODO: Apply dot product
	Matrix Output(0,0);

	return Output;
}

Matrix Matrix::elementMult(Matrix arg)
{
	// TODO: element wise multiplication of two matrices
	Matrix Output(0,0);

	return Output;
}

Matrix Matrix::operator = (Matrix arg)
{
	// TODO: overloaded operator =, assigns one matrix to another
	Matrix Output(0,0);

	return Output;
}
Matrix Matrix::operator + (Matrix arg)
{
	// TODO: overloaded operator +, adds two matrices
	Matrix Output(0,0);

	return Output;
}
Matrix Matrix::operator - (Matrix arg)
{
	// TODO: overloaded operator -, subtracts two matrices
	Matrix Output(0,0);

	return Output;
}

} /* namespace KR_Matrix */

