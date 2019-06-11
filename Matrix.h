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
		Matrix(char *input_file); // constructor that reads from file
		Matrix(const Matrix &arg); // copy constructor
		friend Matrix elementMult(const Matrix &Matrix1, const Matrix &Matrix2); // element by element mult
		Matrix operator= (const Matrix &arg); // assignment operator
		friend Matrix operator* (const Matrix &Matrix1, const Matrix &Matrix2); // dot product
		friend Matrix operator* (double C, const Matrix &arg); // matrix multiplied by constant
		friend Matrix operator+ (const Matrix &Matrix1, const Matrix &Matrix2); // matrix addition
		friend Matrix operator- (const Matrix &Matrix1, const Matrix &Matrix2); // matrix subtraction
		void printMatrix(void);
		~Matrix(); // Destructor
	private:
		int nRows;
		int nCols;
		double ** A; //pointer to pointer to multidim array
};

}

#endif /* MATRIX_H_ */
