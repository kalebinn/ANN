# Matrix Class
This is the class header file and implementation file that handles matrix operations. Most are them are required for an artificial neural network. This document should tell you how to use the matrix class file if you'd like to use this class in your own works. The class file was created in Eclipse IDE by Kelvin Ma with suggestions and contributions from Ricky Valdez.
If there are any problems or typos please contact kalebinn@gmail.com. Thank you!

## Table of Contents
1. [Namespace and Typedefs](#namespace)
2. [Constructors](#Constructors)
    * [Dimensions](#byDim)
    * [Using a file](#byFile)
    * [Copy Constructor](#CopyConstructor)
3. [Matrix Manipulations](#Manips)
    * [Setting an element](#setElement)
    * [Getting an element](#getElement)
    * [Getting the number of rows](#getnRows)
    * [Getting the number of columns](#getnCols)
    * [Transpose](#Transpose)
4. [Matrix Operations and Overloaded Operators](#matOps)
    * [Concatenations](#cat)
    * [Element by Element multiplication](#elementMult)
    * [Dot Product](#dot)
    * [Assignment](#assign)
    * [Comparator](#is_equal)
    * [Operations with Matrices](#overloadedMatOps)
        * [Matrix Addition](#matAdd)
        * [Matrix Subtraction](#matSub)
    * [Operations with Scalars](#scalarsOp)
        * [Addition](#scalarAdd)
        * [Subtraction](#scalarSub)
        * [Multiplication](#scalarMult)
5. [Utility Functions](#matUtil)
    * [Printing the matrix](#printMatrix)

## I. Namespace and typedefs <a name="namespace"></a>
In accordance with the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html#Namespaces) and [Data Structures and other Objects Using C++](https://www.amazon.com/Data-Structures-Other-Objects-Using/dp/0132129485), a namespace was created: `namespace KR_Matrix`. We also created typedefs in order to add some flexibility in our class (for future projects). They are defined by:

`typedef double mat_value_type;`  

`mat_value_type` is the value type of the *elements* within the matrix. They can be `int`, `double`, or `float` as our class does not currently support any operations with `char` or `std::string` type values.
We also defined a new type for our matrix index values:

`typedef std::size_t mat_size_type;`  

These are the index value types when performating any type of iteration in a matrix.
## II. Constructors<a name="Constructors"></a>
There are three different ways to construct a matrix using the matrix class. We created our own namespace (KR_Matrix) so this must be used accordingly as well.  

### Specifying Dimensions <a name="byDim"></a>
One way to create a matrix is by specifying the dimensions of the matrix:  
`KR_Matrix::Matrix Matrix1 (nRows, nCols);`      
where `nRows` and `nCols` represents the number of rows and number of cols desired, respectively. The constructor will return a matrix of zeros of the specified size.  

**Example:**  

`KR_Matrix::Matrix testMatrix(2,3);`  

returns a matrix as such:

![Example](https://i.imgur.com/2r7EIqv.png)    


### Reading from file<a name="byFile"></a>
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

### Copy Constructor<a name="CopyConstructor"></a>
The third method of declaring a matrix is by creating a copy of a previously declared matrix.  
`Matrix(const Matrix &arg)`
where `&arg` is the matrix you are attempting to copy.

**Example:**

`KR_Matrix::Matrix testMatrix3 (testMatrix2);`  

returns the following matrix:  

![Example](https://i.imgur.com/FDId2dL.png)    

which is an exact copy of `testMatrix2` (declared above).

## III. Matrix Manipulation<a name="Manips"></a>
### Setting an Element <a name="setElement"></a>
Setting an element in a matrix takes in 3 inputs: the row, column, and desired value.
`testMatrix.setElement(row, column, value);`  
the values of row and column indicate the index of the element. As such, they *must* be less than or equal to nRows-1 and nCols-1.  

**Example:**  

![Example](https://i.imgur.com/2r7EIqv.png)  

If you wish to set the (1,2) element of testMatrix to 4:  

`testMatrix.setElement(1,2,4);`    

will return the following matrix:

![setElement Example](https://i.imgur.com/fjwd8F7.png)  

### Getting an Element <a name="getElement"></a>
Getting an element from a matrix takes in 2 inputs: the row and the column.
`testMatrix.setElement(row, column);`  
the values of row and column indicate the index of the element. As such, they *must* be less than or equal to nRows-1 and nCols-1.  

**Example:**  

![Example](https://i.imgur.com/jMyAutY.png)

If you wish to get the element in position (1,1) of the `exampleMatrix`.

`double value;`  
`value = exampleMatrix.getElement(1,1);`  
`std::cout << "The value in position (1,1) is " << value << std::endl;`  

would return the following statement:
`The value in position (1,1) is 5.1`    

### Getting the number of rows <a name="getnRows"></a>
To get the total number of rows that exist in a matrix:
`exampleMatrix.getnRows();`  

**Example:**  

![Example](https://i.imgur.com/jMyAutY.png)   

`int numberOfRows;`  
`numberOfRows = exampleMatrix.getnRows();`  
`std::cout << "There are " << numberOfRows <<" rows in exampleMatrix" << std::endl;`  

will print the following statement:
`There are 2 rows in exampleMatrix`  

### Getting the number of columns <a name="getnCols"></a>
To get the total number of columnss that exist in a matrix:
`exampleMatrix.getnColss();`  

**Example:**  

![Example](https://i.imgur.com/jMyAutY.png)  

`int numberOfColumns;`  
`numberOfColumns = exampleMatrix.getnCols();`  
`std::cout << "There are " << numberOfColumns <<" columns in exampleMatrix" << std::endl;`  

will print the following statement:

`There are 3 columns in exampleMatrix`    

### Transpose<a name="Transpose"></a>
A transpose of a matrix is defined in linear algebra as the flipping of a matrix over its diagonal. i.e. The rows of the original matrix becomes the columns of the new matrix. An example of a matrix transpose is:

![LATransposeEx](https://i.imgur.com/zacM6MW.png)  

where T denotes a transpose operator. To transpose any matrix with Matrix.h, you can simply call the `transpose()` function. It will return the transposition of the original matrix.  

**Example:**    

![ExampleMat](https://i.imgur.com/jMyAutY.png)    

`KR_Matrix::Matrix transposedExample(0,0); // declares the matrix`  
`transposedExample = exampleMatrix.transpose(); // assigns the matrix to the transpose`  

The contents of `transposedExample` is:  

![transposedExample](https://i.imgur.com/k8d2o27.png)


## IV. Matrix Operations<a name="matOps"></a>
### Concatenations<a name="cat"></a>
In order to concatenate two matrices, you need three inputs: two matrices, and the direction of concatenation. Matrices can be concatenated vertically if the number of columns are equal, horizontally if the number of rows are equal, or in either direction if both dimensions are equal. As such, the `cat()` function needs to called as such:  
`cat(const Matrix &matrix1, const Matrix &matrix2, std::string direction);`  

**Example:**  

![ExampleMats](https://i.imgur.com/7hNAR6r.png)

To concatenate these two matrices:

`KR_Matrix Matrix concatenatedMatrix (0,0);`  
`std::string directionOfCat = "vertical";`  
`concatenatedMatrix = cat(exampleMatrix1, exampleMatrix2, directionOfCat);`    

will return the following matrix:

![concatenatedMatrix](https://i.imgur.com/uxD7xfl.png)  

### Element by Element Multiplication <a name="elementMult"></a>
`elementMult(const Matrix &matrix1, const Matrix &matrix2)`  
returns the element-wise multiplication of two matrices.

**Example:**

![ExampleMats](https://i.imgur.com/7hNAR6r.png)   

To call the elementMult function with the example matrices:

`KR_Matrix::Matrix exampleMatrix3;`  
`exampleMatrix3 = elementMult(exampleMatrix1, exampleMatrix2);`    

The contents of exampleMatrix3 is the following:  

![example of elementMult](https://i.imgur.com/nNibue2.png)  

### Dot Product <a name="dot"></a>
The dot product (or scalar product) of two matrices is a scalar number defined by the following:

![dot product defined](https://i.imgur.com/kQn88ff.png)  

The dot product in this matrix class is the overloaded operator (\*).
*Note: This operator is also used for multiplication with a constant scalar value.*

**Example:**  

![ExampleMats](https://i.imgur.com/7hNAR6r.png)  

If we apply the dot product of these matrices:

`double dotProduct = 0;`  
`dotProduct = exampleMatrix1 * exampleMatrix2;`  
`std::cout << "The dot product is " << dotProduct << std::endl;`  

will print the following statement:

`The dot product is 42`  

### Assignment <a name="assign"></a>
The assignment operator is the overloaded operator (`=`). It simply sets one matrix equal to another.

**Example:**  

![Example](https://i.imgur.com/jMyAutY.png)     

`KR_Matrix::Matrix exampleMatrix2 (0,0);`  
`exampleMatrix2 = exampleMatrix;`  

The output the code above will simply make a copy of the exampleMatrix.
### Comparator <a name="is_equal"></a>
The Comparator operator (`==`) returns a **boolean** value stating whether two matrices are equal. Two matrices are equal if and only if their dimensions and all their elements are the same.

**Example:**  

![ExampleMats](https://i.imgur.com/7hNAR6r.png)   

`if (exampleMatrix1 == exampleMatrix2)`  
`{std::cout << "The matrices are equal." << std::endl;}`  
`else`  
`{std::cout << "The matrices are not equal." << std::endl;}`  

The code above will return the following statement:
`The matrices are not equal.`    
### Other Operations with Matrices <a name="overloadedMatOps"></a>
#### Matrix Addition<a name="matAdd"></a>
The matrix addition is handled by the overloaded operator (`+`). This simply performs element by element addition.
**Example:**  

![ExampleMats](https://i.imgur.com/7hNAR6r.png)    

`KR_Matrix::Matrix exampleMatrix3 (0,0);`  
`exampleMatrix3 = exampleMatrix1 + exampleMatrix2;`  

The contents of `exampleMatrix3` would be the following:  

![Matrix Addition example](https://i.imgur.com/f5pCVTV.png)  


#### Matrix Subtraction<a name="matSub"></a>
The matrix subtraction is handled by the overloaded operator (`-`). This simply performs element by element subtraction.
**Example:**  

![ExampleMats](https://i.imgur.com/7hNAR6r.png)  


`KR_Matrix::Matrix exampleMatrix3 (0,0);`  
`exampleMatrix3 = exampleMatrix1 - exampleMatrix2;`  

The contents of `exampleMatrix3` would be the following:  

![Matrix Subtraction example](https://i.imgur.com/ltaSaex.png)  

### Operations with Scalars <a name="scalarsOp"></a>
#### Scalar Addition <a name="scalarsAdd"></a>
Matrix addition with a scalar is handled by the overloaded (`+`). It adds the scalar value across every element of the matrix.
This operation is communitive, i.e. order of the inputs do not affect the output.
**Example:**  

![ExampleMat](https://i.imgur.com/Znu1cUW.png)  

If we use the exampleMatrix1 in the following code:

`KR_Matrix::Matrix exampleMatrix2 (0,0);`  
`double constant = 5;`  
`exampleMatrix2 = exampleMatrix1 + constant;`  

The contents of exampleMatrix2 would be:  

![Scalar addition example output](https://i.imgur.com/X0BHIDl.png)  


#### Scalar Subtraction <a name="scalarsSub"></a>
Matrix subtraction with a scalar is handled by the overloaded (`-`). It subtracts the scalar value from every element of the matrix, or subtracts every element of the matrix from the scalar value, depending on the order used.

**Example:**

![ExampleMat](https://i.imgur.com/Znu1cUW.png)    

If we use the exampleMatrix1 in the following code:  

`KR_Matrix::Matrix exampleMatrix2 (0,0);`  
`double constant = 5;`  
`exampleMatrix2 = exampleMatrix1 - constant;`  
`exampleMatrix3 = constant - exampleMatrix1;`  

`exampleMatrix2` would contain:   

![Scalar subtraction example output1](https://i.imgur.com/T30aiNM.png)  

and `exampleMatrix3` would contain:    
![Scalar subtraction example output2](https://i.imgur.com/DYPQlmO.png)  

#### Scalar Multiplication <a name="scalarsMult"></a>
Matrix subtraction with a scalar is handled by the overloaded (`*`). It subtracts the scalar value from every element of the matrix.

**Example:**

![ExampleMat](https://i.imgur.com/Znu1cUW.png)    

If we use the exampleMatrix1 in the following code:  

`KR_Matrix::Matrix exampleMatrix2 (0,0);`  
`double constant = 5;`  
`exampleMatrix2 = exampleMatrix1 * constant;`  

The contents of `exampleMatrix2` is:  

![Scalar multiplication example output2](https://i.imgur.com/wLu6hSm.png)  

## V. Utility Functions<a name="matUtil"></a>
### Printing the Matrix <a name="printMatrix"></a>
This is a utility function that prints the matrix. It can be used to print out a matrix with proper formatting.

**Example**  
![ExampleMat](https://i.imgur.com/jMyAutY.png)    
  
calling:  

`exampleMatrix.printMatrix();`  

will return:    

`1    2.5     3`    
`4.3  5.1   6.3`
