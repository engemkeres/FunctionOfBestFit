#include <iostream>
#include <string>
#include "Matrix.h"

std::vector<unsigned> storeExponents(const std::vector<std::string>& arguments) {
	for(int i=2; i<arguments.size();i++)
		for(unsigned j=0;i<arguments.at(i).size();j++)
			if((arguments.at(i)).at(j) < '0' || (arguments.at(i)).at(j) > '9')
				throw std::runtime_error("Faulty arguments, exponents must be non-negative, whole numbers!");
	std::vector<unsigned> function;
	for (int i = 2; i < arguments.size(); i++) {
		function.push_back( (unsigned)std::stoi( arguments.at(i) ) );
	}
	return function;
}

std::vector<std::string> argsToString(int argc,const char* const argv[]) {
	std::vector<std::string> arguments; 
	for (int i = 0; i < argc; i++)
		arguments.push_back(argv[i]);
	return arguments;
}

// hibás user inputra számítani kell, ezért mégse exceptionként kéne kezelni
int main(int argc, char* argv[]) {
	std::vector<unsigned> function;
	std::vector<std::string> arguments = argsToString(argc, argv);
	if (arguments.size() < 3) {
		std::cout << "Try again with at least two whole, non negative numbers!\nIf you don't want to try again, just press enter." << std::endl;//recovery - új argumentumok esetleges hozzáadás/kicserélése
		std::string temp;
		if (std::cin.peek() != '\n') {
			std::cin >> temp;
			function.push_back(std::stoi(temp)); // hibakezelés, ha nem számokat kapott
		}
	}
	function = storeExponents(arguments);
	Matrix mat(arguments.at(1));	// nem jó fájl hibakezelés: 1. argumentum kicserélése a megadottra
	Vector resultCoefficients = mat.SolveLeastSquaresProblem(function);
	resultCoefficients.printEquation(function);
	return 0;
}

