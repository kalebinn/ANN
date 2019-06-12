/*
 * Matrix.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: Kalebin
 */
#include <assert.h>
#include <fstream>
#include <iostream>
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
Matrix Transpose(void)
{
	Matrix Output(0,0);
	return Output;
}

void
Matrix::setELement (int row, int col, double val)
{
	if (row < nRows && col < nCols)
	{
		A[row][col] = val;
	}
	else
	{
		std::cout << "check inputs" << std::endl;
	}
}

Matrix elementMult(const Matrix &Matrix1, const Matrix &Matrix2)
{
	// TODO: element wise multiplication of two matrices

	assert(Matrix1.nRows == Matrix2.nRows);
	assert (Matrix1.nCols == Matrix2.nCols);

	Matrix Output(Matrix1.nRows, Matrix1.nCols);

	for (int i = 0; i < Matrix1.nRows; i++)
	{
		for (int j = 0; j < Matrix1.nCols; j++)
		{
			Output.A[i][j] = Matrix1.A[i][j] * Matrix2.A[i][j];
		}
	}
	return Output;
}

Matrix Matrix::operator = (const Matrix &arg)
{
	// TODO: overloaded operator =, assigns one matrix to another
	//Matrix Output(arg.nRows,arg.nCols);
	this->nRows = arg.nRows;
	this->nCols = arg.nCols;

	for (int i = 0; i < arg.nRows; i++)
	{
		for (int j = 0; j < arg.nCols; j++)
		{
			this->A[i][j] = arg.A[i][j];
		}
	}

	return *this;
}

bool
Matrix::operator== (const Matrix &arg)
{
	bool is_equal = true;
	if (nRows == arg.nRows && nCols == arg.nCols)
	{
		for (int i = 0; i < nRows && is_equal == true; i++)
		{
			for (int j = 0; j < nCols && is_equal == true; j++)
			{
				std::cout << A[i][j] << " vs " << arg.A[i][j] << std::endl;
				if (A[i][j] != arg.A[i][j])
				{
					std::cout << "going in the wrong thing" << std::endl;
					is_equal = false;
				}
				else{}
			}
		}
	}
	else
	{
		is_equal = false;
	}
	std::cout << "diff_found = " << is_equal << std::endl;
	return is_equal;
}

double operator *(const Matrix &Matrix1, const Matrix &Matrix2)
{
	// TODO: Apply dot product
	double dotProduct;


	return dotProduct;
}

Matrix operator *(double C, const Matrix &arg)
{
	// TODO: Apply product with a constant
	Matrix Output(arg.nRows,arg.nCols);

	for (int i = 0; i < arg.nRows; i++)
	{
		for (int j = 0; j < arg.nCols; j++)
		{
			Output.A[i][j] = C * arg.A[i][j];
		}
	}

	return Output;
}

Matrix operator + (const Matrix &Matrix1, const Matrix &Matrix2)
{
	// TODO: overloaded operator +, adds two matrices
	//assert(Matrix1.nRows == Matrix2.nRows && Matrix1.nCols == Matrix2.nCols);
	assert(Matrix1.nRows == Matrix2.nRows);
	assert (Matrix1.nCols == Matrix2.nCols);

	Matrix Output(Matrix1.nRows, Matrix1.nCols);

	for (int i = 0; i < Matrix1.nRows; i++)
	{
		for (int j = 0; j < Matrix1.nCols; j++)
		{
			Output.A[i][j] = Matrix1.A[i][j] + Matrix2.A[i][j];
		}
	}
	return Output;
}

Matrix operator - (const Matrix &Matrix1, const Matrix &Matrix2)
{
	// TODO: overloaded operator -, subtracts two matrices
	assert(Matrix1.nRows == Matrix2.nRows);
	assert (Matrix1.nCols == Matrix2.nCols);

		Matrix Output(Matrix1.nRows, Matrix1.nCols);

		for (int i = 0; i < Matrix1.nRows; i++)
		{
			for (int j = 0; j < Matrix1.nCols; j++)
			{
				Output.A[i][j] = Matrix1.A[i][j] - Matrix2.A[i][j];
			}
		}
		return Output;

	return Output;
}

void Matrix::printMatrix()
{
	// TODO: prints out the matrix;

	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			std::cout << A[i][j] << "\t";
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

