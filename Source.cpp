#include <iostream>
#include <string>
#include "Matrix.h"

/// \brief fokszámok eltárolása adatvektorba, csak egész, nem negatív kitevõk érvényesek
/// @param argc: parancssori argumentumok száma (0: program neve, 1: adatfájl neve, 2...n: fokszámok
/// @param argv: parancssoron érkezett stringekre mutató pointerek tömbje
/// @returns std::vector: fokszámok tömbje
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

/// \brief Fõfüggvény, csak az algoritmus elindítására. Eltárolja a fokszámokat, meghívja a kiszámoló függvényt, majd kiírja az eredményt
/// 
/// @param argc: parancssori argumentumok száma (0: program neve, 1: adatfájl neve, 2...n: fokszámok
/// @param argv: parancssoron érkezett stringekre mutató pointerek tömbje
/// 
int main(int argc, char* argv[]) {
	if (argc < 2)
		welcome();
	std::vector<double> function;		// fokszámokat tároló adatvektor
	// el is kéne kapni azokat az exceptionöket - de újra felállás hibás fájl után: nem egyértelmû,
	// hogy jogos-e az exceptionös/nem exceptionös megvalósítás, ezért inkább hagyom:
	// hiba, próbálkozz újra, refer to help command stb.
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