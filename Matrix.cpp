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

Matrix::Matrix(mat_size_type rows, mat_size_type cols)
{
	// constructor
	nRows = rows;
	nCols = cols;
	// allocate memory for nRows
	A = new mat_value_type *[nRows];
	for (mat_size_type i = 0; i < nRows; i++)
	{
		// each pointer element in nRow, will point to a new column
		A[i] = new mat_value_type [nCols];
		for (mat_size_type j = 0; j < nCols; j++)
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

	A = new mat_value_type *[nRows];
	for (mat_size_type i = 0; i < nRows; i++)
	{
		// each pointer element in nRow, will point to a new column
		A[i] = new mat_value_type [nCols];
		for (mat_size_type j = 0; j < nCols; j++)
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
	A = new mat_value_type *[nRows];
	for (mat_size_type i = 0; i < nRows; i++)
	{
		// each pointer element in nRow, will point to another column
		A[i] = new mat_value_type [nCols]; // allocate memory for nCols
		for (mat_size_type j = 0; j < nCols; j++)
		{
			A[i][j] = arg.A[i][j]; // populate matrix
		}
	}

}
Matrix Matrix::Transpose(void)
{
	//Matrix Output(0,0);
	Matrix Output (this->nCols, this->nRows);

	for (mat_size_type i = 0 ; i < this->nRows; i++)
	{
		for (mat_size_type j = 0; j < this->nCols; j++)
		{
			Output.A[j][i] = this->A[i][j];
		}
	}

	return Output;
}

void
Matrix::setELement (mat_size_type row, mat_size_type col, mat_value_type val)
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

Matrix::mat_size_type Matrix::getnRows(void)
{
	return this->nRows;
}

Matrix::mat_size_type Matrix::getnCols(void)
{
	return this->nCols;
}


Matrix::mat_value_type Matrix::getElement(mat_size_type row, mat_size_type col)
{
	assert(row < this->nRows);
	assert(col < this->nCols);
	mat_value_type element;

	if (row < nRows && col < nCols)
	{
		element = A[row][col];
	}
	else
	{
		std::cout << "check inputs" << std::endl;
	}

	return element;
}

Matrix elementMult(const Matrix &Matrix1, const Matrix &Matrix2)
{
	// TODO: element wise multiplication of two matrices

	assert(Matrix1.nRows == Matrix2.nRows);
	assert (Matrix1.nCols == Matrix2.nCols);

	Matrix Output(Matrix1.nRows, Matrix1.nCols);

	for (Matrix::mat_size_type i = 0; i < Matrix1.nRows; i++)
	{
		for (Matrix::mat_size_type j = 0; j < Matrix1.nCols; j++)
		{
			Output.A[i][j] = Matrix1.A[i][j] * Matrix2.A[i][j];
		}
	}
	return Output;
}

Matrix Matrix::operator = (const Matrix &arg)
{
	for (Matrix::mat_size_type i = 0; i < this->nRows; i++)
	{
		delete [] this->A[i];
	}
	delete [] this->A;

	this->nRows = arg.nRows;
	this->nCols = arg.nCols;

	A = new mat_value_type *[this->nRows];
	for (mat_size_type i = 0; i < this->nRows; i++)
	{
		// each pointer element in nRow, will point to a new column
		A[i] = new mat_value_type [this->nCols];
		for (mat_size_type j = 0; j < this->nCols; j++)
		{
			A[i][j] = arg.A[i][j]; // populate each element with 0
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
		for (Matrix::mat_size_type i = 0; i < nRows && is_equal == true; i++)
		{
			for (Matrix::mat_size_type j = 0; j < nCols && is_equal == true; j++)
			{
				if (A[i][j] != arg.A[i][j])
				{
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
	return is_equal;
}

double operator *(const Matrix &Matrix1, const Matrix &Matrix2)
{
	// TODO: Apply dot product
	assert(Matrix1.nRows == Matrix2.nRows);
	assert (Matrix1.nCols == Matrix2.nCols);

	double dotProduct = 0;
	for (Matrix::mat_size_type i = 0; i < Matrix1.nRows; i++)
	{
		for (Matrix::mat_size_type j = 0; j < Matrix1.nCols; j++)
		{
			dotProduct += (Matrix1.A[i][j] * Matrix2.A[i][j]);
		}
	}

	return dotProduct;
}

Matrix operator *(double C, const Matrix &arg)
{
	// TODO: Apply product with a constant
	Matrix Output(arg.nRows,arg.nCols);

	for (Matrix::mat_size_type i = 0; i < arg.nRows; i++)
	{
		for (Matrix::mat_size_type j = 0; j < arg.nCols; j++)
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

	for (Matrix::mat_size_type i = 0; i < Matrix1.nRows; i++)
	{
		for (Matrix::mat_size_type j = 0; j < Matrix1.nCols; j++)
		{
			Output.A[i][j] = Matrix1.A[i][j] + Matrix2.A[i][j];
		}
	}
	return Output;
}

Matrix operator +(double C, const Matrix &arg)
{
	// TODO: Apply product with a constant
	Matrix Output(arg.nRows,arg.nCols);

	for (Matrix::mat_size_type i = 0; i < arg.nRows; i++)
	{
		for (Matrix::mat_size_type j = 0; j < arg.nCols; j++)
		{
			Output.A[i][j] = C + arg.A[i][j];
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

		for (Matrix::mat_size_type i = 0; i < Matrix1.nRows; i++)
		{
			for (Matrix::mat_size_type j = 0; j < Matrix1.nCols; j++)
			{
				Output.A[i][j] = Matrix1.A[i][j] - Matrix2.A[i][j];
			}
		}
		return Output;

	return Output;
}

Matrix operator -(double C, const Matrix &arg)
{
	// TODO: Apply product with a constant
	Matrix Output(arg.nRows,arg.nCols);

	for (Matrix::mat_size_type i = 0; i < arg.nRows; i++)
	{
		for (Matrix::mat_size_type j = 0; j < arg.nCols; j++)
		{
			Output.A[i][j] = C - arg.A[i][j];
		}
	}

	return Output;
}

void Matrix::printMatrix()
{
	// TODO: prints out the matrix;

	for (Matrix::mat_size_type i = 0; i < nRows; i++)
	{
		for (Matrix::mat_size_type j = 0; j < nCols; j++)
		{
			std::cout << A[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout<<std::endl;
}
Matrix::~Matrix()
{
	// deallocate all memory used
	for (Matrix::mat_size_type i = 0; i < nRows; i++)
	{
		delete [] A[i];
	}
	delete [] A;

}
} /* namespace KR_Matrix */

