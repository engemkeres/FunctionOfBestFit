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
	explicit Matrix(const char* fName);
	~Matrix();

	//unsigned getRows() const;
	//unsigned getColumns() const;
	unsigned getSize() const;
	// identitásmátrix létrehozása
	void makeIdentity(unsigned size);
	// méret, és ezzel az STL tároló által foglalandó memória beállítása
	void setSize(unsigned rows=0, unsigned columns=0);
	// mátrix kiürítése
	//void empty();
	// mátrix feltöltése az egyenletrendszernek megfelelõ módon

	//void fillFromPointVector(const PointVector& points, const std::vector<int>& function); // helyettesíteni kéne egy fájlból olvasó konstruktorral függvénnyel, amivel a Point osztály elhagyhatom
	
	//void fillFromArray(unsigned rows, unsigned columns, const double* dataArray);
	
	//Vektorokkal dolgozó, de mátrixra hívandó függvények
	//Matrix extractRow(unsigned rowindex) const; - nem fog kelleni valószínûleg
	void pushVector(const Vector& other);
	Vector extractColumn(unsigned columnindex) const;
	//void vectorToMatrix(const Vector& other);
	
	void print() const;

	double operator()(unsigned row, unsigned column) const;
	double& operator()(unsigned row, unsigned columns);
	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;
	Vector operator*(const Vector& other) const;
	Matrix operator*(double times) const;
	Matrix& operator=(const Matrix& other);
	void outerProduct(const Vector& other);
	// transzponálás ( mátrix sor-oszlop csere)
	void transpose();	
	// inverz számolás
	Matrix makeLeastSquaresMatrix(std::vector<unsigned> function) const;	// koordináta-mátrixra hívandó meg, ami a fájlból lett felépítve: A mátrixot adja vissza
	Matrix HouseholderOrthogonalize() const; // Q mátrixot adja vissza, melybõl a meghívó mátrix (A) segítségével R megkapható
	Vector SolveLeastSquaresProblem(std::vector<unsigned> function) const;
	Vector SolveUpperTriangle(const Vector& other) const;
	//Matrix invertUpperTriangleSquare() const;
};
