#pragma once
#include <iostream>
#include <vector>
#include <math.h>


class Vector
{
private:
	unsigned size;
	std::vector<double> data;
public:
	Vector(unsigned size = 0);
	Vector(const Vector& other);
	~Vector();


	unsigned getSize() const;
	void setSize(unsigned size);
	void empty();
	double length() const;	// vektor hossza
	void normalize();	// vektor egys�ghossz�v� t�tele
	void fill(double num);

	void print() const;

	double operator()(unsigned index) const;
	double& operator()(unsigned size);
	Vector operator+(const Vector& other) const;
	Vector operator-(const Vector& other) const;
	double dotProduct(const Vector& other) const; // skal�ris szorz�s
	// vektori�lis szorz�s eredm�nye m�trix, az a m�trix oszt�lyban legyen defini�lva
	Vector operator*(double times) const;
	Vector& operator=(const Vector& other);

};

