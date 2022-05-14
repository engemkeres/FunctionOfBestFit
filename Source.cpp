#include <iostream>
#include <string>
#include "Matrix.h"

std::vector<unsigned> storeExponentiations(int argc, char* argv[]) {
	for (int i = 2; i < argc; i++) {// program neve és a fájl neve itt lényegtelen, ezért a harmadik elemtõl indulunk
		for (unsigned j = 0; j < strlen(argv[i]); j++) {
			if ((argv[i])[j] < '0' || (argv[i])[j] > '9')
				std::exit(32); // TODO hibakezelés, nem fokSZÁM lett megadva
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
 		std::exit(29); //TODO hibakezelés, 0 megadott fokszám argumentum
	Matrix mat(argv[1]); // belül van/lesz kezelve, hogy létezik-e ilyen nevû fájl

	std::vector<unsigned> function = storeExponentiations(argc, argv);
	
	Vector resultCoefficients = mat.SolveLeastSquaresProblem(function);
	resultCoefficients.printEquation(function);

	return 0;
}

