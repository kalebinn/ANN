/*
 * Matrix.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: Kalebin
 */
#include <iostream>
#include "Matrix.h"

namespace KR_Matrix {

Matrix::Matrix(int rows, int cols)
{
	// TODO: write the constructor
	nRows = rows;
	nCols = cols;
	// allocate memory for nRows
	A = new double *[nRows];
	for (int i = 0; i < nRows; i++)
	{
		// each pointer element in nRow, will point to
		A[i] = new double [nCols];
	}

	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			A[i][j] = 0;
		}
	}
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

void Matrix::printMatrix()
{
	// TODO: prints out the matrix;

	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			std::cout << A[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
Matrix::~Matrix()
{
	// deallocate all memory used
	for (int i = 0; i < nRows; i++)
	{
		delete [] A[i];
	}
	delete [] A;
}
} /* namespace KR_Matrix */

