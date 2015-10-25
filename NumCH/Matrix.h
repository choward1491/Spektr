#ifndef _MATRIX_H_
#define _MATRIX_H_


#include <iostream>
#include <string>
using namespace std;



enum MatrixType{DIAG,TDIAG,SYM,UTRI,LTRI,SPARSE, GEN};

class Matrix
{
public:

	//Matrix constructors
	Matrix() :rows(0), cols(0), type(0), mat(0), T(0){};
	Matrix(int r, int c, int flag, bool transpose);
	Matrix(const Matrix & m);
    Matrix(string matrix);
	~Matrix(){ clear(); }

	//Matrix operators
	double operator()(int r, int c) const;
	double & operator()(int r, int c);

	double operator()(int k) const;
	double & operator()(int k);

	Matrix operator*(const Matrix & m) const;
	Matrix operator+(const Matrix & m) const;
	Matrix operator-(const Matrix & m) const;
	void operator=(const Matrix & m);

	int getRows() const{ return rows; }
	int getCols() const{ return cols; } 
	int getType() const{ return type; }
    bool getTranspose() const{ return T; }
	void transpose(){ T = !T; }

	//Special matrix functionality
	double determinant() const;
	Matrix invert();
    void QR_Decomposition(Matrix &Q, Matrix &R) const;
    void eig( Matrix & eigenvalues, Matrix & eigenvectors) const;
    double mag();
    void normalize();
    void doCopy( const Matrix & M ){
        if( &M != this )
        {
            clear();
            copy(M);
        }
    }
    Matrix squareRoot() const;

	//Extras
	bool isEmpty(){ return mat == 0; }
	void print() const;


private:
	//Variables
	int rows;
	int cols;
	int type;
	bool T; //transpose
	double* mat;
	double tmp;


	//Methods
	void clear();
	void copy( const Matrix & m);
    
};

double sign(double val);
Matrix solve(Matrix & A, Matrix & b, int flag);
Matrix gaussElim(Matrix & A, Matrix & b);
Matrix linspace(double xs, double xe, int N);




#endif