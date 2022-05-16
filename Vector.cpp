#include "Vector.h"

Vector::Vector(unsigned size)
{
	setSize(size);
}

Vector::Vector(const Vector& other)
{
	*this = other;
}

unsigned Vector::getSize() const
{
	return size;
}

void Vector::setSize(unsigned size)
{	// nem csak a méret paraméter állítja át, hanem az STL tárolót is újraméretezi
	this->size = size;
	this->data.resize(size);
}

double Vector::length() const
{
	double result = 0;
	for (unsigned i = 0; i < size; i++)
		result += (*this)(i) * (*this)(i);
	return sqrt(result); // vonhatjuk a gyökés, mivel valós számok négyzetösszege biztonsan nem negatív
}

void Vector::normalize()
{
	double length = (*this).length();
	for (unsigned i = 0; i < size; i++)
		(*this)(i) /= length; // el kell tárolni a vektor hosszát, mert különben folyton változna a hossza számolás közben
}

void Vector::fill(double num)
{
	std::fill(data.begin(), data.end(), num);
}

void Vector::makeCanonicBase(unsigned size)
{	// az elsõ koordináta 1, minden más 0
	setSize(size);
	(*this)(0) = 1;
	for (unsigned i = 1; i < size; i++)
	{
		(*this)(i) = 0;
	}
}

void Vector::print() const
{
	for (unsigned i = 0; i < size; i++)
		std::cout << (*this)(i) << std::endl;
	std::cout << std::endl;
}

void Vector::printEquation(std::vector<double> function) const // ide is kell epsilonos becslés, mert nem lehet 0 a kitevõ igazán
{
	typedef std::numeric_limits< double > dbl;
	std::cout.precision(dbl::max_digits10);
	std::cout << "y = ";
	for (unsigned i = 0; i < function.size(); i++) {
		if (function.at(i)==0)
			std::cout << (*this)(i);
		else {
			std::cout << ((*this)(i) < 0 ? " - " : " + ");	// csak az elsõ együttható elé nem kell +/--t tenni
			if (function.at(i) == 1)
				std::cout << ((*this)(i) < 0 ? (-1) * (*this)(i) : (*this)(i)) << "x"; // x^1 helyett csak x
			else
				std::cout << ( (*this)(i) < 0 ? (-1)*(*this)(i) : (*this)(i) )<< "x^" << function.at(i); 
		}
	}
	std::cout << std::endl;
}

double Vector::operator()(unsigned index) const
{
	try {
		if (index > size - 1)
			throw std::out_of_range("Too great index!");
	}
	catch (std::out_of_range& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
	return data.at(index);
}

double& Vector::operator()(unsigned index)
{
	try {
		if (index > size - 1)
			throw std::out_of_range("Too great index!");
	}
	catch (std::out_of_range& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
	return data.at(index);
}

Vector Vector::operator+(const Vector& other) const
{ // eltérõ hosszúságú vektorok nem adhatóak össze
	Vector result;
	try {
		if (this->size != other.size)
			throw std::domain_error("Differently sized vectors can't be added to each other!");
	}
	catch (std::domain_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
	result.setSize(size);
	for (unsigned i = 0; i < size; i++)
		result(i) = (*this)(i) + other(i);
	return result;
}

Vector Vector::operator-(const Vector& other) const
{ // eltérõ hosszúságú vektorok nem vonhatóak ki egymásból
	Vector result;
	try {
		if (this->size != other.size)
			throw std::domain_error("Differently sized vectors can't be subtracted from each other!");
	}
	catch (std::domain_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
	result.setSize(size);
	for (unsigned i = 0; i < size; i++)
		result(i) = (*this)(i) - other(i);
	return result;
}

Vector Vector::operator*(double times) const
{
	Vector result;
	result.setSize(size);
	for (unsigned i = 0; i < size; i++)
		result(i) = (*this)(i) * times;
	return result;
}

Vector& Vector::operator=(const Vector& other)
{
	setSize(other.size);
	this->data = other.data;
	return (*this);
}
