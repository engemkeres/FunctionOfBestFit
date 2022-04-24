#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>

class PointVector // érdemes lenne template-tel csinálni, hogy intként és double/floatként is lehessen pontokat tárolni?
{
private:
	unsigned length;				// koordináták darabszáma
	std::vector<double> vector;		// STL tároló
public:
	PointVector();
	PointVector(const char* fname);	// Koordinátákat tároló adathalmaz létrehozása fájlból
	PointVector(const PointVector& other);

	void addPoint(double x, double y); // új koordináta beillesztése
	unsigned getLength() const;
	void setLength(unsigned length);
	void print() const;
	double operator()(unsigned index, char axis) const;

	
	~PointVector();	// vektor kezeli a saját memóriáját, nem kell felszabadítani?

};

