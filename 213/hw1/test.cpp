#include <iostream>
#include "matrix.h"

int main()
{
	// matrix<int> definitions
	int i1[3] = { 1, 2, 3 };
	int i2[3] = { 4, 5, 6 };
	int i3[3] = { 7, 8, 9 };
	int i4[2] = { 1, 1 };
	int i5[2] = { 2, 2 };
	int i6[2] = { 3, 3 };
	const int** m1;
	m1 = new const int*[3];
	m1[0] = i1;
	m1[1] = i2;
	m1[2] = i3;
	const int** m2;
	m2 = new const int*[3];
	m2[0] = i4;
	m2[1] = i5;
	m2[2] = i6;
	const int** m3;
	m3 = new const int*[2];
	m3[0] = i6;
	m3[1] = i6;

	// matrix<double> definitions
	double f1[2] = { 1.24, 8.31 };
	double f2[2] = { 4.21, 9.30 };
	double f3[4] = { 0.12, 2.41, 0.14, 0.01};
	double f4[4] = { 0.48, 0.00, 2.41, 5.63 };
	const double** m4;
	m4 = new const double*[2];
	m4[0] = f1;
	m4[1] = f2;
	const double** m5;
	m5 = new const double*[2];
	m5[0] = f3;
	m5[1] = f4;
	
/*
	Matrix<int> x(m1, 3, 3);
	x.print();
	cout << endl;
	Matrix<int> y(m2, 3, 2);
	y.print();
	cout << endl;
	Matrix<int> z(m3, 2, 2);
	z.print();
	cout << endl;
	Matrix<int> temp(3, 2);
	temp = x * y;
	temp.print();
	cout << endl;
	temp = temp + y;
	temp.print();
	cout << endl;
	temp = temp * z;
	Matrix<int> asd(y);
	temp = temp - asd;
	temp.print();
	cout << endl;
	asd = (temp - asd) * z;
	asd.print();
	cout << endl;
	try{temp+z;}
	catch(DimensionMismatchException ex) {cout << ex.what() << endl;}
	try{
		cout << "The value of the element at x[0][0] is: " << x(0,0) << endl;
	}
	catch(InvalidIndexException ex) {cout << ex.what() << endl;}
	cout << endl;
	int& p = asd(2,1);
	cout << p << endl;
	cout << endl;
	cout << "The value of the element at temp[2][1] is: " << temp(2, 1) << endl;
	cout << "Number of rows for temp is: " << temp.getRows() << endl;
	cout << "Number of cols for temp is: " << temp.getCols() << endl;
*/
	

	Matrix<double> x(m4, 2, 2);
	x.print();
	cout << endl;
	Matrix<double> y(m5, 2, 4);
	y.print();
	cout << endl;
	Matrix<double> temp(x);
	Matrix<double> hey(y);
	Matrix<double> asd(2, 4);
	asd = x * y - (y + hey);
	asd.print();
	cout << endl;
	try{x+y;}
	catch(DimensionMismatchException ex) {cout << ex.what() << endl;}
	try{
		cout << "The value of the element at x[0][0] is: " << x(-1,3) << endl;
	}
	catch(InvalidIndexException ex) {cout << ex.what() << endl;}
	cout << endl;

	cout << "The value of the element at asd[1][1] is: " << asd(1, 1) << endl;
	cout << "Number of rows for asd is: " << asd.getRows() << endl;
	cout << "Number of cols for asd is: " << asd.getCols() << endl;


	return 0;
}
