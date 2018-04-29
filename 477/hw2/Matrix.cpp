#ifndef DENEMEDENEME
#define DENEMEDENEME
#include <algorithm>
#include "Vector3.h"
using namespace std;
/*
DimensionMismatchException::DimensionMismatchException():msg("dimension mismatch exception!"){};

const char* DimensionMismatchException::what(){return msg;}

InvalidIndexException::InvalidIndexException():msg("invalid index exception!"){};

const char* InvalidIndexException::what(){return msg;}
*/
class DimensionMismatchException//Returns error message,message is "dimension mismatch exception!"
{
	public:
	DimensionMismatchException():msg("dimension mismatch exception!"){};
	const char * what(){return msg;};//returns error message
	private:
	const char *msg;
};

class InvalidIndexException//Returns error message,message is "invalid index exception!"
{
	public:
	InvalidIndexException():msg("invalid index exception!"){};
	const char * what(){return msg;};//returns error message
	private:
	const char *msg;
};



template <class T>
class Matrix
{
private:
    T** data; // matrix elements stored here
    int rows; // number of rows
    int cols; // number of columns
public:
    Matrix(int numRows = 0, int numCols = 0); // makes storage allocation but leaves it uninitialized, for 0,0 dont allocate memory
    Matrix(T const* const* inputData, int numRows, int numCols);
    Matrix(T[4][4]);
    Matrix(const Matrix& rhs);
   ~Matrix();

    Matrix& operator=(Matrix rhs);

    // all of the below functions may throw dimension mismatch exception if the given matrix's dimensions does not match with the initial dimensions
    Matrix operator+(const Matrix& rhs) const; // element-wise addition of two matrices
    Matrix operator-(const Matrix& rhs) const; // element-wise subtraction of two matrices
    Matrix operator*(const Matrix& rhs) const; // multiplication of two matrices, dot product
    Vector3 operator*(const Vector3& rhs) const;
    // these two functions may throw invalid index exception, it does this if the values are negative or if they are out of bounds or if they are 0
    T operator()(int r, int c) const; // returns the element value at row r and column c
    T& operator()(int r, int c); // returns reference of the element value at row r and column c

     int getRows() const; // returns the number of rows
     int getCols() const; // returns the number of columns
    void tMatrix(const Vector3& ts);
    void sMatrix(const Vector3& scs);
    void rxMatrix(float angle);
    void ryMatrix(float angle);
    void rzMatrix(float angle);
    void print() const; // prints the matrix with each column element separated by a tab and each row element in a new line print a newline after the last row
};

/* DO NOT MODIFY ANYTHING ABOVE THIS LINE.
   IT WILL BE REPLACED BY THE ORIGINAL INTERFACE,
   AND IF YOU MAKE CHANGES THEY WILL BE LOST.
   INSERT YOUR IMPLEMENTATION BELOW THIS LINE. */


//Your solutions will come to here
template<class T>
Vector3 Matrix<T>::operator*(const Vector3& rhs) const{
	float rhs2[4]={rhs[0],rhs[1],rhs[2],1};
	float temp[4]={0,0,0,0};
	int i,j,k;	
	for(i=0;i<4;i++)
	{
		for(k=0;k<4;k++)
		{
				temp[i]+=data[i][k]*rhs2[k];	
		}				
	}
	Vector3 result(temp[0],temp[1],temp[2]);
	return result;
}


template <class T>
void Matrix<T>::tMatrix(const Vector3& ts){
	data[0][0] = 1;
    data[0][1] = 0;
    data[0][2] = 0;
    data[0][3] = ts[0];

    data[1][0] = 0;
    data[1][1] = 1;
    data[1][2] = 0;
    data[1][3] = ts[1];

    data[2][0] = 0;
    data[2][1] = 0;
    data[2][2] = 1;
    data[2][3] = ts[2];

    data[3][0] = 0;
    data[3][1] = 0;
    data[3][2] = 0;
    data[3][3] = 1;
}

template <class T>
void Matrix<T>::sMatrix(const Vector3& scs){
	data[0][0] = scs[0];
    data[0][1] = 0;
    data[0][2] = 0;
    data[0][3] = 0;

    data[1][0] = 0;
    data[1][1] = scs[1];
    data[1][2] = 0;
    data[1][3] = 0;

    data[2][0] = 0;
    data[2][1] = 0;
    data[2][2] = scs[2];
    data[2][3] = 0;

    data[3][0] = 0;
    data[3][1] = 0;
    data[3][2] = 0;
    data[3][3] = 1;
}


template <class T>
void Matrix<T>::rxMatrix(float angle){
	float _cos=cos(angle);
	float _sin=sin(angle);
	data[0][0] = 1;
    data[0][1] = 0;
    data[0][2] = 0;
    data[0][3] = 0;

    data[1][0] = 0;
    data[1][1] = _cos;
    data[1][2] = - _sin;
    data[1][3] = 0;

    data[2][0] = 0;
    data[2][1] = _sin;
    data[2][2] = _cos;
    data[2][3] = 0;

    data[3][0] = 0;
    data[3][1] = 0;
    data[3][2] = 0;
    data[3][3] = 1;
}

template <class T>
void Matrix<T>::ryMatrix(float angle){
	float _cos=cos(angle);
	float _sin=sin(angle);
	data[0][0] = _cos;
    data[0][1] = 0;
    data[0][2] = _sin;
    data[0][3] = 0;

    data[1][0] = 0;
    data[1][1] = 1;
    data[1][2] = 0;
    data[1][3] = 0;

    data[2][0] = - _sin;
    data[2][1] = 0;
    data[2][2] = _cos;
    data[2][3] = 0;

    data[3][0] = 0;
    data[3][1] = 0;
    data[3][2] = 0;
    data[3][3] = 1;
}

template <class T>
void Matrix<T>::rzMatrix(float angle){
	float _cos=cos(angle);
	float _sin=sin(angle);
	data[0][0] = _cos;
    data[0][1] = - _sin;
    data[0][2] = 0;
    data[0][3] = 0;

    data[1][0] = _sin;
    data[1][1] = _cos;
    data[1][2] = 0;
    data[1][3] = 0;

    data[2][0] = 0;
    data[2][1] = 0;
    data[2][2] = 1;
    data[2][3] = 0;

    data[3][0] = 0;
    data[3][1] = 0;
    data[3][2] = 0;
    data[3][3] = 1;
}



template <class T>
Matrix<T>::Matrix(int numRows, int numCols) :rows(numRows),cols(numCols)
{

	if (numRows!=0 || numCols!=0){
		cout<<"ozgu"<<endl;
		data=new T*[rows];
		for(int i=0;i<rows;i++)
			data[i]=new T[cols];
		cout<<"alara"<<endl;
	}
	else
		data=NULL;
}
template <class T>
Matrix<T>::Matrix(T const* const* inputData, int numRows, int numCols)
{
	rows=numRows;
	cols=numCols;
	data=new T*[rows];
	for(int i=0;i<rows;i++)
		data[i]=new T[cols];	
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++){
			data[i][j]=inputData[i][j];
		}		
	}
}
template <class T>
Matrix<T>::Matrix(const Matrix& rhs)
{
	cout<<"copy"<<endl;
	if (rhs.data==NULL){
		if(data!=NULL){
			for(int i=0;i<rows;i++)
				delete[] data[i];
			delete[] data;
			rows=rhs.rows;
			cols=rhs.cols;
			data=NULL;
		}
	}
	else{

		if(data!=NULL){
			cout<<"bitti"<<endl;
			for(int i=0;i<rows;i++){
				cout<<i<<endl;
				delete[] data[i];}
			cout<<"bitti 3"<<endl;
			delete[] data;

			rows=rhs.rows;
			cols=rhs.cols;
			data=new T*[rows];
			for(int i=0;i<rows;i++)
				data[i]=new T[cols];	
			for(int i=0;i<rows;i++)
			{
				for(int j=0;j<cols;j++){
					data[i][j]=rhs.data[i][j];
				}		
			}
		}
		else{
			cout<<"bitti 2"<<endl;
			rows=rhs.rows;
			cols=rhs.cols;
			data=new T*[rows];
			for(int i=0;i<rows;i++)
				data[i]=new T[cols];	
			for(int i=0;i<rows;i++)
			{
				for(int j=0;j<cols;j++){
					data[i][j]=rhs.data[i][j];
				}		
			}
		}
	}
	
}
template <class T>
Matrix<T>::~Matrix()
{
	if(data!=NULL)
	{
		for(int i=0;i<rows;i++)
			delete[] data[i];
		delete[] data;
	}
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix rhs)
{	cout<<"s.a"<<endl;
	if(this!=&rhs)
	{	
		
		if(data!=NULL){
			if(rhs.data!=NULL){
				for(int i=0;i<rows;i++)
					delete[] data[i];
				delete[] data;
				this->rows=rhs.rows;
				this->cols=rhs.cols;
				data=new T*[this->rows];
				for(int i=0;i<(this->rows);i++)
					data[i]=new T[this->cols];
				for(int i=0;i<(this->rows);i++)
				{
					for(int j=0;j<(this->cols);j++){
						this->data[i][j]=rhs.data[i][j];
					}		
				}
			}
			else{
				for(int i=0;i<rows;i++)
					delete[] data[i];
				delete[] data;
				this->rows=rhs.rows;
				this->cols=rhs.cols;
				data=NULL;
			}
		}
		else
		{
			if(rhs.data!=NULL){
				this->rows=rhs.rows;
				this->cols=rhs.cols;
				data=new T*[this->rows];
				for(int i=0;i<(this->rows);i++)
					data[i]=new T[this->cols];
				for(int i=0;i<(this->rows);i++)
				{
					for(int j=0;j<(this->cols);j++){
						this->data[i][j]=rhs.data[i][j];
					}		
				}
			}
		}
		cout<<"a.s"<<endl;
	}/*
    using std::swap;
    swap(rows, rhs.rows);
    swap(cols, rhs.cols);
    swap(data, rhs.data);*/
    return *this;
}
template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix& rhs) const
{
	if(rows==rhs.rows && cols==rhs.cols){
		Matrix<T> temp(rows,cols);
		for(int i=0;i<rows;i++)
		{
			for(int j=0;j<cols;j++){
				temp.data[i][j]=data[i][j]+rhs.data[i][j];
			}		
		}
		return temp;
	}
	else
		throw DimensionMismatchException();
}
template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix& rhs) const
{
	if(rows==rhs.rows && cols==rhs.cols){
		Matrix<T> temp(rows,cols);
		for(int i=0;i<rows;i++)
		{
			for(int j=0;j<cols;j++){
				temp.data[i][j]=data[i][j]-rhs.data[i][j];
			}		
		}
		return temp;
	}
	else
		throw DimensionMismatchException();
}
template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix& rhs) const
{
	cout<<"* operator giris"<<endl;
	if(cols==rhs.rows){
		cout<<"esit"<<endl;
		Matrix<T> temp(rows,rhs.cols);
		int i,j,k;	
		for(i=0;i<rows;i++)
		{
			for(j=0;j<rhs.cols;j++)
			{
				temp.data[i][j]=0;
				for(k=0;k<cols;k++)
				{
					temp.data[i][j]+=data[i][k]*rhs.data[k][j];	
				}		
			}		
		}
		cout<<"*operator cikis"<<endl;
		return temp;
	}
	else
		throw DimensionMismatchException();

	
}
template <class T>
T Matrix<T>::operator()(int r, int c) const
{
	if(r<=0 || c<=0 || r>rows || c>cols)
		throw InvalidIndexException();
	else
	 return data[r-1][c-1];
}
template <class T>
T& Matrix<T>::operator()(int r, int c)
{
	if(r<=0 || c<=0 || r>rows || c>cols)
		throw InvalidIndexException();
	else
		return data[r-1][c-1];
}
template <class T>
int Matrix<T>::getRows() const
{
	return rows;
}
template <class T>
int Matrix<T>::getCols() const
{
	return cols;
}
template <class T>
void Matrix<T>::print() const
{
	int i,j;	
	for(int i=0;i<rows;i++)
	{
		for(j=0;j<cols-1;j++)
		{
			cout<<data[i][j]<<'\t';
		}
		cout<<data[i][j]<<endl;		
	}
}
#endif
