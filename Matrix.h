#pragma once
#include <iostream>
#include <vector>
//#include "Point.h"
#include "Vector.h"
#include <math.h>
#include <fstream>

class Matrix
{
private:
	unsigned rows;
	unsigned columns;
	std::vector<double> data;		// STL t�rol�
public:
	Matrix(unsigned rows=0, unsigned columns=0);
	Matrix(const Matrix& other);
	Matrix(const char* fName);
	~Matrix();

	unsigned getRows() const;
	unsigned getColumns() const;
	// identit�sm�trix l�trehoz�sa
	void makeIdentity(unsigned size);
	// m�ret, �s ezzel az STL t�rol� �ltal foglaland� mem�ria be�ll�t�sa
	void setSize(unsigned rows=0, unsigned columns=0);
	// m�trix ki�r�t�se
	void empty();
	// m�trix felt�lt�se az egyenletrendszernek megfelel� m�don

	//void fillFromPointVector(const PointVector& points, const std::vector<int>& function); // helyettes�teni k�ne egy f�jlb�l olvas� konstruktorral f�ggv�nnyel, amivel a Point oszt�ly elhagyhatom
	
	void fillFromArray(unsigned rows, unsigned columns, double* dataArray);
	
	
	//Vektorokkal dolgoz�, de m�trixra h�vand� f�ggv�nyek
	//Matrix extractRow(unsigned rowindex) const; - nem fog kelleni val�sz�n�leg
	Matrix& pushVector(const Vector& other);
	Vector extractColumn(unsigned columnindex) const;
	
	void print() const;


	double operator()(unsigned row, unsigned column) const;
	double& operator()(unsigned row, unsigned columns);
	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;
	Vector operator*(const Vector& other) const;
	Matrix operator*(double times) const;
	Matrix& operator=(const Matrix& other);
	// transzpon�l�s ( m�trix sor-oszlop csere)
	void transpose();	
	// inverz sz�mol�s
	Matrix UpperTriangleInverse();	

};
