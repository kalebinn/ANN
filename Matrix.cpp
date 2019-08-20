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

Matrix::Matrix()
{
	nRows = 0;
	nCols = 0;
	A = NULL;
}
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
Matrix::setElement (mat_size_type row, mat_size_type col, mat_value_type val)
{
	try
	{
		if (row >= nRows || col > nCols)
		{
			throw 11;
		}
	}
	catch(int errorNum)
	{
		std::cout << "FATAL ERROR #" << errorNum << " - setElement failed. Check inputs." << std::endl;
		std::cout << "SUGGESTION: the size of this matrix is: " << this->nRows << " by " << this->nCols << std::endl;
	}
	assert(row < this->nRows && col < this->nCols);
	A[row][col] = val;

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

Matrix::mat_value_type Matrix::sumRow(mat_size_type row)
{
	mat_value_type sum = 0;
	for (mat_size_type i = 0; i < this->nCols; i++)
	{
		sum += this->A[row][i];
	}
	return sum;
}
Matrix::mat_value_type Matrix::sumCol (mat_size_type col)
{
	mat_value_type sum = 0;
	for (mat_size_type i = 0; i < this->nRows; i++)
	{
		sum += this->A[i][col];
	}
	return sum;
}


Matrix elementMult(const Matrix &Matrix1, const Matrix &Matrix2)
{
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

Matrix cat(const Matrix &Matrix1, const Matrix &Matrix2, std::string direction)
{
	assert (direction == "horizontal" || direction == "vertical");
	if (direction == "horizontal")
	{
		assert(Matrix1.nRows == Matrix2.nRows);
		// concatenate horizontally
		Matrix::mat_size_type totalCols = Matrix1.nCols + Matrix2.nCols;
		Matrix Output(Matrix1.nRows, totalCols);
		for (Matrix::mat_size_type i = 0; i < Matrix1.nRows; i++)
		{
			for (Matrix::mat_size_type j = 0; j < Matrix1.nCols; j++)
			{
				Output.A[i][j] = Matrix1.A[i][j];
			}
			for (Matrix::mat_size_type j = Matrix1.nCols; j < totalCols; j++)
			{

				Output.A[i][j] = Matrix2.A[i][j-Matrix1.nCols];
			}
		}
		return Output;
	}
	else
	{
		assert(Matrix1.nCols == Matrix2.nCols);
		Matrix::mat_size_type totalRows = Matrix1.nRows + Matrix2.nRows;
		Matrix Output(totalRows,Matrix1.nCols);

		for (Matrix::mat_size_type i = 0; i < Matrix1.nCols; i++)
		{
			for (Matrix::mat_size_type j = 0; j < Matrix1.nRows; j++)
			{
				Output.A[j][i] = Matrix1.A[j][i];
			}
			for (Matrix::mat_size_type j = Matrix1.nRows; j < totalRows; j++)
			{
				Output.A[j][i] = Matrix2.A[j - Matrix1.nRows][i];
			}
		}
		return Output;
	}
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

Matrix operator *(const Matrix &Matrix1, const Matrix &Matrix2)
{
	assert (Matrix1.nCols == Matrix2.nRows);
	Matrix dotProduct (Matrix1.nRows, Matrix2.nCols);

	for (Matrix::mat_size_type i = 0; i < Matrix1.nRows; i++)
	{
		for (Matrix::mat_size_type j = 0; j < Matrix2.nCols; j++)
		{
			for (Matrix::mat_size_type k = 0; k < Matrix1.nCols; k++)
			{
				dotProduct.A[i][j] += (Matrix1.A[i][k] * Matrix2.A[k][j]);
			}
		}
	}

	return dotProduct;
}

Matrix operator *(double C, const Matrix &arg)
{
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
	//assert(Matrix1.nRows == Matrix2.nRows && Matrix1.nCols == Matrix2.nCols);
	//assert(Matrix1.nRows == Matrix2.nRows);
	//assert (Matrix1.nCols == Matrix2.nCols);

	Matrix Output(Matrix1.nRows, Matrix1.nCols);
	if (Matrix1.nRows == Matrix2.nRows && Matrix1.nCols == Matrix2.nCols)
	{
		for (Matrix::mat_size_type i = 0; i < Matrix1.nRows; i++)
		{
			for (Matrix::mat_size_type j = 0; j < Matrix1.nCols; j++)
			{
				Output.A[i][j] = Matrix1.A[i][j] + Matrix2.A[i][j];
			}
		}
	}
	else if(Matrix1.nRows != Matrix2.nRows && Matrix1.nCols == Matrix2.nCols)
	{
		for (Matrix::mat_size_type i = 0; i < Matrix1.nRows; i++)
		{
			for (Matrix::mat_size_type j = 0; j < Matrix1.nCols; j++)
			{
				Output.A[i][j] = Matrix1.A[i][j] + Matrix2.A[0][j];
			}
		}
	}
	else if(Matrix1.nRows == Matrix2.nRows && Matrix1.nCols != Matrix2.nCols)
	{
		for (Matrix::mat_size_type i = 0; i < Matrix1.nRows; i++)
		{
			for (Matrix::mat_size_type j = 0; j < Matrix1.nCols; j++)
			{
				Output.A[i][j] = Matrix1.A[i][j] + Matrix2.A[i][0];
			}
		}
	}
	else{}
	return Output;
}

Matrix operator +(double C, const Matrix &arg)
{
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

void Matrix::printMatrix(std::string file)
{
	std::ofstream outputFile(file, std::ios::out);

	for (Matrix::mat_size_type i = 0; i < nRows; i++)
	{
		for (Matrix::mat_size_type j = 0; j < nCols; j++)
		{
			 outputFile << A[i][j] << "\t";
		}
		outputFile << std::endl;
	}
	outputFile<<std::endl;
}

void Matrix::printMatrix()
{
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

