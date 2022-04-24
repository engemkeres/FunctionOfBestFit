#pragma once
#include <iostream>
#include <vector>
#include "Point.h"
#include <math.h>

class Matrix
{
private:
	unsigned rows;
	unsigned columns;
	std::vector<double> data;		// STL t�rol�
public:
	Matrix(unsigned rows=0, unsigned columns=0);
	Matrix(const Matrix& other);
	~Matrix();

	unsigned getRows() const;
	unsigned getColumns() const;

	void makeIdentity(unsigned size);	// identit�sm�trix l�trehoz�sa
	void setSize(unsigned rows=0, unsigned columns=0); // m�ret, �s ezzel az STL t�rol� �ltal foglaland� mem�ria be�ll�t�sa
	void empty();					// m�trix ki�r�t�se
	void fillFromPointVector(const PointVector& points, const std::vector<int>& function); // m�trix felt�lt�se az egyenletrendszernek megfelel� m�don

	void print() const;


	double operator()(unsigned row, unsigned column) const;
	double& operator()(unsigned row, unsigned columns);
	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;
	Matrix operator*(double times) const;

	void transpose();		// transzpon�l�s ( m�trix sor-oszlop csere)
	void inverse();			// inverz sz�mol�s

	double determinant() const;		// determin�ns sz�mol�s

};
