#include <iostream>
#include "Matrix.h"

// Egyel�re tesztf�jl, k�s�bb itt fog t�rt�nni az egyenletrendszer megold�sa, amely a  f�ggv�ny egy�tthat�it adja meg

PointVector testPointVector() {
	const char* fName = "TesttFile1.txt";
	PointVector p1(fName);
	p1.print();
	return p1;
}

void testMatrix(const PointVector& points) {
	std::vector<int> function;
	function.push_back(0);
	function.push_back(1);
	function.push_back(2);
	function.push_back(10);
	Matrix eno;
	eno.fillFromPointVector(points, function);
	eno.print();
	Matrix m1;
	m1.makeIdentity(5);
	 m1.print();
	Matrix m2;
	m2.makeIdentity(5);
	Matrix m3 = m1 + m2;
	Matrix m4 = m1 - m2;
	Matrix m5 = m1 * m2;
	Matrix m6 = m1 * 3.0;
	m3.print();
	m4.print();
	m5.print();
	m6.print();
	//TODO szorz�s r�szletes tesztel�se
	Matrix m7(4, 4);
	unsigned k = 0;
	for (unsigned i = 0; i < 4; i++)
		for (unsigned j = 0; j < 4; j++, k++)
			m7(i, j) = k;
	m7.print();
	Matrix m9;
	m9.makeIdentity(4);
	Matrix m8 = m7 * m9;
	m8.print();



}

int main(int argc, char** argv) { //F
	testMatrix(testPointVector());
}