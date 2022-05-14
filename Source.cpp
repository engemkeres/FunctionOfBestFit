#include <iostream>
#include <string>
#include "Matrix.h"

std::vector<unsigned> storeExponents(int argc, char* argv[]) {
	for (int i = 2; i < argc; i++) {// program neve �s a f�jl neve itt l�nyegtelen, ez�rt a harmadik elemt�l indulunk
		for (unsigned j = 0; j < strlen(argv[i]); j++) {
			if ((argv[i])[j] < '0' || (argv[i])[j] > '9')
				throw std::runtime_error("Faulty arguments, exponents must be non-negative, whole numbers!");
		}
	}
	std::vector<unsigned> function;
	for (int i = 2; i < argc; i++) {
		std::string turnToNum(argv[i]);
		function.push_back((unsigned)std::stoi(turnToNum));
	}
	return function;
}

int main(int argc, char* argv[]) {
	if (argc < 3)
		throw std::runtime_error("Function coefficients can't be calculated without exponents!");
	Matrix mat(argv[1]); // bel�l van/lesz kezelve, hogy l�tezik-e ilyen nev� f�jl
	std::vector<unsigned> function = storeExponents(argc, argv);
	Vector resultCoefficients = mat.SolveLeastSquaresProblem(function);
	resultCoefficients.printEquation(function);

	return 0;
}

