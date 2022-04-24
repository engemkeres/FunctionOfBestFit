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
	// identitásmátrix létrehozása
	void makeIdentity(unsigned size);
	// méret, és ezzel az STL tároló által foglalandó memória beállítása
	void setSize(unsigned rows=0, unsigned columns=0);
	// mátrix kiürítése
	void empty();
	// mátrix feltöltése az egyenletrendszernek megfelelõ módon
	void fillFromPointVector(const PointVector& points, const std::vector<int>& function);


	void print() const;


	double operator()(unsigned row, unsigned column) const;
	double& operator()(unsigned row, unsigned columns);
	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;
	Matrix operator*(double times) const;
	Matrix& operator=(const Matrix& other);
	// transzponálás ( mátrix sor-oszlop csere)
	void transpose();	
	// inverz számolás
	Matrix inverse();			
	// determináns számolás
	double determinant() const;		

};
