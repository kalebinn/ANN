# Matrix Class
This is the class header file and implementation file that handles matrix operations. Most are them are required for an artificial neural network. This document should tell you how to use the matrix class file if you'd like to use this class in your own works.

## Table of Contents
1. [Constructors](#Constructors/Destructor)
    * [Dimensions](#byDim)
    * [Using a file](#byFile)
    * [Copy Constructor](#CopyConstructor)

## I. Constructors<a name="Constructors"></a>
There are three different ways to construct a matrix using the matrix class. We created our own namespace (KR_Matrix) so this must be used accordingly as well.  

### a. Specifying Dimensions <a name="byDim"></a>
One way to create a matrix is by specifying the dimensions of the matrix:  
`KR_Matrix::Matrix Matrix1 (nRows, nCols);`    
where `nRows` and `nCols` represents the number of rows and number of cols desired, respectively. The constructor will return a matrix of zeros of the specified size.  

**Example:**  

`KR_Matrix::Matrix testMatrix(2,3);`

returns a matrix as such:

![Example](https://i.imgur.com/2r7EIqv.png)    


### b. Reading from file<a name="byFile"></a>
Another method of creating a matrix is by using a file. The constructor takes the matrix file name as the input as such:  

`Matrix(std::string fileName);`  

The file that contains the matrix must be of the following form:
![Example2](https://i.imgur.com/AkupPEP.png)

where M is the number of rows, and N is the number of columns.

**Example:**
![Example](https://i.imgur.com/TywJgiP.png)

When you call the constructor:  

`std::string inputFileName = "testMatrix.txt";`  
`KR_Matrix::Matrix testMatrix2(inputFileName);`  

the return will be the following matrix:  
![Example](https://i.imgur.com/ojhKDhM.png)

### c. Copy Constructor<a name="CopyConstructor"></a>
The third method of declaring a matrix is by creating a copy of a previously declared matrix.  
`Matrix(const Matrix &arg)`
where `&arg` is the matrix you are attempting to copy.

**Example:**

`KR_Matrix::Matrix testMatrix3 (testMatrix2);`
returns the following matrix:
![Example](https://i.imgur.com/FDId2dL.png)  
which is an exact copy of `testMatrix2` (declared above).
