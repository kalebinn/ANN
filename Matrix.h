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
		Matrix(std::string input_file_name); // constructor that reads from file
		/* pre condition: file format of the input matrix should be of
		 *
		 * nRows nCols
		 * M[0][0]	M[0][1]  M[0][2] M[0][nCols-1]
		 * ...
		 * M[nRows-1][0] ... M[nRows-1][nCols-1]
		 * */
		Matrix(const Matrix &arg); // copy constructor
		Matrix Transpose(void);
		void setELement (int row, int col, double val);
		friend Matrix elementMult(const Matrix &Matrix1, const Matrix &Matrix2); // element by element mult
		Matrix operator= (const Matrix &arg); // assignment operator
		bool operator== (const Matrix &arg);
		friend double operator* (const Matrix &Matrix1, const Matrix &Matrix2); // dot product
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
