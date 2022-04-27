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
	std::vector<double> data;		// STL tároló
public:
	Matrix(unsigned rows=0, unsigned columns=0);
	Matrix(const Matrix& other);
	Matrix(const char* fName);
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

	//void fillFromPointVector(const PointVector& points, const std::vector<int>& function); // helyettesíteni kéne egy fájlból olvasó konstruktorral függvénnyel, amivel a Point osztály elhagyhatom
	
	void fillFromArray(unsigned rows, unsigned columns, double* dataArray);
	
	
	//Vektorokkal dolgozó, de mátrixra hívandó függvények
	//Matrix extractRow(unsigned rowindex) const; - nem fog kelleni valószínûleg
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
	// transzponálás ( mátrix sor-oszlop csere)
	void transpose();	
	// inverz számolás
	Matrix UpperTriangleInverse();	

};
