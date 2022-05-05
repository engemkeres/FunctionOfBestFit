#include <iostream>
#include "Matrix.h"

// Egyelõre tesztfájl, késõbb itt fog történni az egyenletrendszer megoldása, amely a  függvény együtthatóit adja meg



void testMatrix2(const char* fName) {
	Matrix m1(fName);
	m1.print();
	Matrix m2;
	double varray[] = { 1,2,3,4,5,6,7,8 };
	m2.fillFromArray(4, 2, varray);
	m2.print();
	Vector v3 = m2.extractColumn(0);
	v3.print();
	m2.pushVector(v3);
	m2.print();
}

void testMatrix3() {
	Matrix m1;
	double varray[] = {-2,4,-1,2,0,1,2,1,3,1}; //0,1 és 0,1,2 fokszámú polinommal
	//double varray[] = { -1,0,0,1,-2,-5,1,4,2,15,-3,-20 }; //0,1,2,3 fokszámú polinommal
	m1.fillFromArray(5, 2, varray);
	m1.print();
	std::vector<unsigned> function;
	function.push_back(0);
	function.push_back(1);
	//function.push_back(2);
	m1.SolveLeastSquaresProblem(function);
}

int main(int argc, char** argv) { //F
	//testMatrix(testPointVector());
	// parancssori argumentumként beolvasott fájlnév:
	//const char* fName = "TesttFile1.txt";
	//testMatrix2(fName);
	testMatrix3();


}

//PointVector testPointVector() {
//	const char* fName = "TesttFile1.txt";
//	PointVector p1(fName);
//	p1.print();
//	return p1;
//}
//
//void testMatrix(const PointVector& points) {
//	std::vector<int> function;
//	function.push_back(0);
//	function.push_back(1);
//	function.push_back(2);
//	function.push_back(10);
//	Matrix eno;
//	eno.fillFromPointVector(points, function);
//	eno.print();
//	Matrix m1;
//	m1.makeIdentity(5);
//	 m1.print();
//	Matrix m2;
//	m2.makeIdentity(5);
//	Matrix m3 = m1 + m2;
//	Matrix m4 = m1 - m2;
//	Matrix m5 = m1 * m2;
//	Matrix m6 = m1 * 3.0;
//	m3.print();
//	m4.print();
//	m5.print();
//	m6.print();
//	//TODO szorzás részletes tesztelése
//	Matrix m7(4, 4);
//	unsigned k = 0;
//	for (unsigned i = 0; i < 4; i++)
//		for (unsigned j = 0; j < 4; j++, k++)
//			m7(i, j) = k;
//	m7.print();
//	Matrix m9;
//	m9.makeIdentity(4);
//	Matrix m8 = m7 * m9;
//	m8.print();
//
//	double convertToMatrix[] =
//		{ 1,2,3,4,5,
//		6,7,8,9,10,
//		11,12,13,14,15,
//		16,17,18,19,20,
//		21,22,23,24,25 };
//	Matrix m10;
//	m10.fillFromArray(5, 5, convertToMatrix);
//	m10.print();
//
//
//}