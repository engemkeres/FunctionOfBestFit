#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>

class PointVector // �rdemes lenne template-tel csin�lni, hogy intk�nt �s double/floatk�nt is lehessen pontokat t�rolni?
{
private:
	unsigned length;				// koordin�t�k darabsz�ma
	std::vector<double> vector;		// STL t�rol�
public:
	PointVector();
	PointVector(const char* fname);	// Koordin�t�kat t�rol� adathalmaz l�trehoz�sa f�jlb�l
	PointVector(const PointVector& other);

	void addPoint(double x, double y); // �j koordin�ta beilleszt�se
	unsigned getLength() const;
	void setLength(unsigned length);
	void print() const;
	double operator()(unsigned index, char axis) const;

	
	~PointVector();	// vektor kezeli a saj�t mem�ri�j�t, nem kell felszabad�tani?

};

