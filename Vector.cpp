#include "Vector.h"

Vector::Vector(unsigned size)
{
	setSize(size);
}

Vector::Vector(const Vector& other)
{
	*this = other;
}

Vector::~Vector()
{}

unsigned Vector::getSize() const
{
	return size;
}

void Vector::setSize(unsigned size)
{
	if (size == 0 || this->size == size)
		std::exit(12); //TODO hibakezelés
	this->size = size;
	this->data.resize(size);
}

void Vector::empty()
{
	size = 0;
	data.clear();
	data.shrink_to_fit();
}

double Vector::length() const
{
	double result = 0;
	for (unsigned i = 0; i < size; i++)
		result += (*this)(i) * (*this)(i);
	return sqrt(result);
}

void Vector::normalize()
{
	double length = (*this).length();
	for (unsigned i = 0; i < size; i++)
		(*this)(i) /= length; // el kell tárolni a vektor hosszát, mert különben folyton változna a hossza
}

void Vector::print() const
{
	for (unsigned i = 0; i < size; i++)
		std::cout << (*this)(i) << std::endl;
	std::cout << std::endl;
}

double Vector::operator()(unsigned index) const
{
	if (index > size - 1)
		std::exit(13); //TODO hibakezelés
	return data.at(index);
}

double& Vector::operator()(unsigned index)
{
	if (index > size - 1)
		std::exit(13); //TODO hibakezelés
	return data.at(index);
}

Vector Vector::operator+(const Vector& other) const
{
	Vector result;
	if (this->size != other.size)
		std::exit(14); //TODO hibakezelés
	result.setSize(size);
	for (unsigned i = 0; i < size; i++)
		result(i) = (*this)(i) + other(i);
	return result;
}

Vector Vector::operator-(const Vector& other) const
{
	Vector result;
	if (this->size != other.size)
		std::exit(14); //TODO hibakezelés
	result.setSize(size);
	for (unsigned i = 0; i < size; i++)
		result(i) = (*this)(i) - other(i);
	return result;
}

double Vector::dotProduct(const Vector& other) const
{
	if (this->size != other.size)
		std::exit(15); //TODO hibakezelés
	double result = 0;
	for (unsigned i = 0; i < size; i++)
		result += (*this)(i) * other(i);
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
