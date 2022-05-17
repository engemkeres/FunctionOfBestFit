#include <iostream>
#include <string>
#include "Matrix.h"

/// \brief foksz�mok elt�rol�sa adatvektorba
/// @param argc: parancssori argumentumok sz�ma (0.: program neve, 1.: adatf�jl neve, 2...n.: foksz�mok
/// @param argv: parancssoron �rkezett stringekre mutat� pointerek t�mbje
/// @returns std::vector: foksz�mok t�mbje
std::vector<double> storeExponents(int argc, char* argv[]) { 
	std::vector<double> function;
	try {
		if (argc < 3)
			throw std::invalid_argument("You must enter at least 1 number as exponent!");
	}
	catch (std::invalid_argument& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
	try {
		for (int i = 2; i < argc; i++)
			function.push_back((double)std::stod(argv[i]));		// ha az stod hib�t dob, mivel nem alak�that� sz�mm� a string tartalma,
																// akkor ezt a hib�t k�l�n elkapom, hogy ne a saj�t hiba�zenet�t irassam ki a felhaszn�l�nak
	}
	catch (std::invalid_argument& e) {
		std::cerr << "Error: invalid exponents, all exponents must be numbers, separated only by spaces!";
		std::exit(-1);
	}
	return function;
}

void welcome() {
	std::cout <<	"Welcome!\nTo get started, launch the program the following way:\n"
					"Type in the name of the program (FunctionOfBestFit) followed by your coordinate-file's name,\n"
					"then list the exponents of the polinom you want to fit to the dataset separated by spaces.\n"
					"The file must be .txt format, filled the following way:\n"
					"x y\nx y\nx y and so on...\n"
					"The file musn't contain empty lines or other characters.\n"
					"The listed exponents must be numbers."<< std::endl;
}

/// \brief F�f�ggv�ny, csak az algoritmus elind�t�s�ra. Elt�rolja a foksz�mokat, megh�vja a kisz�mol� f�ggv�nyt, majd ki�rja az eredm�nyt
/// 
/// @param argc: parancssori argumentumok sz�ma (0: program neve, 1: adatf�jl neve, 2...n: foksz�mok
/// @param argv: parancssoron �rkezett stringekre mutat� pointerek t�mbje
/// 
int main(int argc, char* argv[]) {
	if (argc < 2)
		welcome();
	std::vector<double> function;		// foksz�mokat t�rol� adatvektor
	try {
		function = storeExponents(argc, argv);									// parancssoron �rkezett kitev�k elt�rol�sa
		Matrix mat(argv[1]);													// 2D koordin�tam�trix beolvas�sa f�jlb�l
		Vector resultCoefficients = mat.SolveLeastSquaresProblem(function);		// illesztend� f�ggv�ny egy�tthat�inak kisz�mol�sa
		resultCoefficients.printEquation(function);
	}
	catch (...) {
		std::cerr << "Unexpected error, terminating program" << std::endl;
		std::exit(-1);
	}
	return 0;
}