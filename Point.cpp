//#include "Point.h"
//
//PointVector::PointVector()
//{
//	length = 0;
//	vector.resize(0);
//}
//
//void PointVector::addPoint(double x, double y)
//{
//	length++;
//	vector.push_back(x);
//	vector.push_back(y);
//}
//
//PointVector::PointVector(const char* fName) : length(0) {
//	std::ifstream inputFile;
//	double tempx;
//	double tempy;
//	try {
//		inputFile.open(fName);
//		if (inputFile.is_open())
//		{
//			while (true) {
//				inputFile >> tempx;
//				vector.push_back(tempx);
//				// ha páratlan adatmennyiség van, kell hibakezelés
//				if (inputFile.eof())
//					throw std::runtime_error("Odd amount of numbers or empty lines, unusable file!");
//				// akkor is ezt a hibát dobja, ha kettõnél több enter van a fájl végén
//				inputFile >> tempy;
//				vector.push_back(tempy);
//				length++;
//				if (inputFile.eof())
//					break;
//			}
//			inputFile.close();
//		}
//		else
//			throw std::runtime_error("File cannot be found!");
//	}
//	catch (const std::runtime_error& e) {
//		std::cerr << "exception: " << e.what() << std::endl;
//		std::cerr << "Terminating program.";
//		std::exit(1);
//	}
//	// ha nem nyílik meg a fájl, hibakezelés - jelenleg leáll a program, ha ebbe ütközik
//}
//
//PointVector::PointVector(const PointVector& other)
//{
//	this->length = other.length;
//	this->vector = other.vector;
//}
//
//unsigned PointVector::getLength() const
//{
//	return length;
//}
//
//void PointVector::setLength(unsigned length)
//{
//	this->length = length;
//}
//
//double PointVector::operator()(unsigned index, char axis) const // esetleg lehet bool axis, de az elég aljas hibakezelés-kikerülés
//{
//	try {
//		if (index > length - 1)
//			throw std::out_of_range("Invalid index!"); // hibadobás, ha rossz index
//	}
//	catch (const std::out_of_range& e) { // ezt valószínûleg kívül kéne kezelni, így talán nem felejtem el
//		std::cerr << "exception: " << e.what() << std::endl;
//	}
//
//	unsigned axisValue = 2;
//
//	try {
//		switch (axis)
//		{
//		case 'x': axisValue = 0; break;
//		case 'y': axisValue = 1; break;
//		default: throw std::out_of_range("Invalid axis index!"); break;	// hibadobás, ha nem x/y oszlopból akarunk olvasni
//		}
//	}
//	catch (const std::out_of_range& e) { // ezt valószínûleg kívül kéne kezelni, így talán nem felejtem el
//		std::cerr << "exception: " << e.what() << std::endl;
//		std::cerr << "Terminating program.";
//		std::exit(2);
//	}
//
//	return vector.at((index * 2 + axisValue));
//}
//
//void PointVector::print() const {
//	for (unsigned i = 0; i < this->getLength(); i++)
//	{
//		std::cout << this->operator()(i, 'x') << '\t' << this->operator()(i, 'y') << std::endl;
//	}
//}
//
//PointVector::~PointVector()
//{
//	// vektor kezeli a saját memóriáját, nem kell felszabadítani?
//}
//
//
//
//
//
