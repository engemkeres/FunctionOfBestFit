#include <iostream>
#include <string>
#include "Matrix.h"

std::vector<unsigned> storeExponentiations(int argc, char* argv[]) {
	for (int i = 2; i < argc; i++) {// program neve �s a f�jl neve itt l�nyegtelen, ez�rt a harmadik elemt�l indulunk
		for (unsigned j = 0; j < strlen(argv[i]); j++) {
			if ((argv[i])[j] < '0' || (argv[i])[j] > '9')
				std::exit(32); // TODO hibakezel�s, nem fokSZ�M lett megadva
			std::cout << i - 1 << ". number " << j + 1 << ". letter okay" << std::endl;
		}
	}
	// ha stimmelnek a megadottak
	std::cout << "cool dawg" << std::endl;

	std::vector<unsigned> function;
	for (int i = 2; i < argc; i++) {
		std::string turnToNum(argv[i]);
		function.push_back((unsigned)std::stoi(turnToNum));
	}
	return function;
}

int main(int argc, char* argv[]) {
	
	if (argc < 3)
 		std::exit(29); //TODO hibakezel�s, 0 megadott foksz�m argumentum
	Matrix mat(argv[1]); // bel�l van/lesz kezelve, hogy l�tezik-e ilyen nev� f�jl

	std::vector<unsigned> function = storeExponentiations(argc, argv);
	
	Vector resultCoefficients = mat.SolveLeastSquaresProblem(function);
	resultCoefficients.printEquation(function);

	return 0;
}

