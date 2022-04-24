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


}

int main(int argc, char** argv) { //F
	testMatrix(testPointVector());
}