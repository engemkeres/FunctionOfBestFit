#pragma once
#include <iostream>
#include <vector>

class Matrix
{
private:
	unsigned rows;
	unsigned columns;
	std::vector<double> data;
public:
	Matrix(unsigned rows=0, unsigned columns=0, bool identity=false);
	Matrix(const Matrix& other);
	~Matrix();

	unsigned getRows() const;
	unsigned getColumns() const;

	bool setSize(unsigned rows=0, unsigned columns=0);
	bool fillFromFile(std::string fName);
	bool empty();


	double operator()(unsigned row, unsigned column) const;
	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;
	template<class T>
	Matrix operator*(const T times) const;

	bool transpose();
	bool inverse();

	double determinant() const;
};

