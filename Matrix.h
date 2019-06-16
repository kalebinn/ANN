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
		typedef double mat_value_type;
		typedef std::size_t mat_size_type;
		Matrix(mat_size_type rows, mat_size_type cols); // constructor
		Matrix(std::string); // constructor that reads from file
		Matrix(const Matrix &arg); // copy constructor
		Matrix Transpose(void); // transpose matrix
		void setELement (mat_size_type row, mat_size_type col, mat_value_type val);
		mat_size_type getnRows(void); // return the numbers of rows
		mat_size_type getnCols(void); // return the number of columns
		mat_value_type getElement(mat_size_type row, mat_size_type col);
		friend Matrix elementMult(const Matrix &Matrix1, const Matrix &Matrix2); // element by element mult
		Matrix operator= (const Matrix &arg); // assignment operator
		bool operator== (const Matrix &arg);
		friend double operator* (const Matrix &Matrix1, const Matrix &Matrix2); // dot (scalar) product
		friend Matrix operator* (double C, const Matrix &arg); // matrix multiplied by constant
		friend Matrix operator* (const Matrix &arg, double C) {return C*arg;};
		friend Matrix operator+ (const Matrix &Matrix1, const Matrix &Matrix2); // matrix addition
		friend Matrix operator+ (double C, const Matrix &arg);
		friend Matrix operator+ (const Matrix &arg ,double C){return C + arg;};
		friend Matrix operator- (const Matrix &Matrix1, const Matrix &Matrix2); // matrix subtraction
		friend Matrix operator- (double C, const Matrix &arg);
		friend Matrix operator- (const Matrix &arg ,double C){return C - arg;};
		void printMatrix(void);
		~Matrix(); // Destructor

	private:
		mat_size_type nRows;
		mat_size_type nCols;
		mat_value_type ** A; //pointer to pointer to multidim array
};

}

#endif /* MATRIX_H_ */
