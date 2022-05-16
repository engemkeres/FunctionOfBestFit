#include <iostream>
#include <string>
#include "Matrix.h"

/// \brief foksz�mok elt�rol�sa adatvektorba, csak eg�sz, nem negat�v kitev�k �rv�nyesek
/// @param argc: parancssori argumentumok sz�ma (0: program neve, 1: adatf�jl neve, 2...n: foksz�mok
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
			function.push_back((double)std::stod(argv[i]));
	}
	catch (std::invalid_argument& e) {
		std::cerr << "Error: invalid exponents, all exponents must be numbers, separated only by spaces!";
		std::exit(-1);
	}
	return function;
}

void welcome() {
	std::cout <<	"Welcome!\nTo get started, launch the program the following way:\n"
					"Type in the name of the program (FunctionOfBestFit) followed by your coordinate-file's name,\n "
					"then list the exponents of the polinom you want to fit to the dataset separated by spaces.\n"
					"The file must be .txt format, filled the following way:\n"
					"x y\nx y\nx y and so on...\n"
					"The file musn't contain empty lines or other characters.\n"
					"The listed exponents must be whole, non-negative numbers."<< std::endl;
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
	// el is k�ne kapni azokat az exception�ket - de �jra fel�ll�s hib�s f�jl ut�n: nem egy�rtelm�,
	// hogy jogos-e az exception�s/nem exception�s megval�s�t�s, ez�rt ink�bb hagyom:
	// hiba, pr�b�lkozz �jra, refer to help command stb.
	try {
		function = storeExponents(argc, argv);
		Matrix mat(argv[1]);
		Vector resultCoefficients = mat.SolveLeastSquaresProblem(function);
		resultCoefficients.printEquation(function);
	}
	catch (...) {
		std::cerr << "Unexpected error, terminating program" << std::endl;
		std::exit(-1);
	}
	return 0;
}