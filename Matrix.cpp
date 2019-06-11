/*
 * Matrix.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: Kalebin
 */
#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>
#include "Matrix.h"

namespace KR_Matrix {

Matrix::Matrix(int rows, int cols)
{
	// constructor
	nRows = rows;
	nCols = cols;
	// allocate memory for nRows
	A = new double *[nRows];
	for (int i = 0; i < nRows; i++)
	{
		// each pointer element in nRow, will point to a new column
		A[i] = new double [nCols];
		for (int j = 0; j < nCols; j++)
		{
			A[i][j] = 0; // populate each element with 0
		}
	}
}

Matrix::Matrix (std::string input_file_name)
{
	// TODO : constructor that reads array from input file
	std::ifstream input_file (input_file_name, std::ios::in);
	nRows = 0;
	nCols = 0;

	input_file >> nRows >> nCols;

	A = new double *[nRows];
	for (int i = 0; i < nRows; i++)
	{
		// each pointer element in nRow, will point to a new column
		A[i] = new double [nCols];
		for (int j = 0; j < nCols; j++)
		{
			input_file >> A[i][j]; // populate each element from input file
		}
	}


}

Matrix::Matrix(const Matrix &arg)
{
	nRows = arg.nRows;
	nCols = arg.nCols;
	// allocate memory for nRows
	A = new double *[nRows];
	for (int i = 0; i < nRows; i++)
	{
		// each pointer element in nRow, will point to another column
		A[i] = new double [nCols]; // allocate memory for nCols
		for (int j = 0; j < nCols; j++)
		{
			A[i][j] = arg.A[i][j]; // populate matrix
		}
	}

}

void
Matrix::setELement (int row, int col, double val)
{

}
Matrix elementMult(const Matrix &Matrix1, const Matrix &Matrix2)
{
	// TODO: element wise multiplication of two matrices
	Matrix Output(0,0);

	return Output;
}

Matrix Matrix::operator = (const Matrix &arg)
{
	// TODO: overloaded operator =, assigns one matrix to another
	Matrix Output(0,0);

	return Output;
}

Matrix operator *(const Matrix &Matrix1, const Matrix &Matrix2)
{
	// TODO: Apply dot product
	Matrix Output(0,0);

	return Output;
}

Matrix operator *(double C, const Matrix &Matrix2)
{
	// TODO: Apply dot product
	Matrix Output(0,0);

	return Output;
}

Matrix operator + (const Matrix &Matrix1, const Matrix &Matrix2)
{
	// TODO: overloaded operator +, adds two matrices
	Matrix Output(0,0);

	return Output;
}

Matrix operator - (const Matrix &Matrix1, const Matrix &Matrix2)
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

