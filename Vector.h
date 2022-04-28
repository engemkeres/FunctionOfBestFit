#pragma once
#include <iostream>
#include <vector>
#include <math.h>

// igazából megvalósítható templateként, és akkor ilyen vektorban el tudom tárolni a parancssoron beolvasandó polinom fokszámait [int]-ként

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
	void normalize();	// vektor egységhosszúvá tétele
	void fill(double num);
	void makeCanonicBase(unsigned size);
	void print() const;

	double operator()(unsigned index) const;
	double& operator()(unsigned size);
	Vector operator+(const Vector& other) const;
	Vector operator-(const Vector& other) const;
	double dotProduct(const Vector& other) const; // skaláris szorzás
	// vektoriális szorzás eredménye mátrix, az a mátrix osztályban legyen definiálva
	Vector operator*(double times) const;
	Vector& operator=(const Vector& other);
	void push(double value);
};

