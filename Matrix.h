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
	std::vector<double> data;		// STL tároló
public:
	Matrix(unsigned rows=0, unsigned columns=0);
	Matrix(const Matrix& other);
	~Matrix();

	unsigned getRows() const;
	unsigned getColumns() const;

	void makeIdentity(unsigned size);	// identitásmátrix létrehozása
	void setSize(unsigned rows=0, unsigned columns=0); // méret, és ezzel az STL tároló által foglalandó memória beállítása
	void empty();					// mátrix kiürítése
	void fillFromPointVector(const PointVector& points, const std::vector<int>& function); // mátrix feltöltése az egyenletrendszernek megfelelõ módon

	void print() const;


	double operator()(unsigned row, unsigned column) const;
	double& operator()(unsigned row, unsigned columns);
	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;
	Matrix operator*(double times) const;

	void transpose();		// transzponálás ( mátrix sor-oszlop csere)
	void inverse();			// inverz számolás

	double determinant() const;		// determináns számolás

};
