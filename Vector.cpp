#include "Vector.h"

Vector::Vector(unsigned size)
{
	setSize(size);
}

Vector::Vector(const Vector& other)
{
	*this = other;
}

Vector::~Vector() {}

unsigned Vector::getSize() const
{
	return size;
}

void Vector::setSize(unsigned size)
{
	this->size = size;
	this->data.resize(size);
}

// nincs használva
//void Vector::empty()
//{
//	size = 0;
//	data.clear();
//	data.shrink_to_fit();
//}

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
		(*this)(i) /= length; // el kell tárolni a vektor hosszát, mert különben folyton változna a hossza számolás közben
}

void Vector::fill(double num)
{
	std::fill(data.begin(), data.end(), num);
}

void Vector::makeCanonicBase(unsigned size)
{
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

void Vector::printEquation(std::vector<unsigned> function) const
{
	std::cout << "y = ";
	for (unsigned i = 0; i < function.size(); i++) {
		if (i == 0)
			std::cout << (*this)(i);
		else {
			std::cout << ((*this)(i) < 0 ? " - " : " + ");
			if (i == 1)
				std::cout << ((*this)(i) < 0 ? (-1) * (*this)(i) : (*this)(i)) << "x";
			else
				std::cout << ( (*this)(i) < 0 ? (-1)*(*this)(i) : (*this)(i) )<< "x^" << function.at(i);
		}
	}
	std::cout << std::endl;
}

double Vector::operator()(unsigned index) const
{
	if (index > size - 1)
		throw std::out_of_range("Too great index!");
	return data.at(index);
}

double& Vector::operator()(unsigned index)
{
	if (index > size - 1)
		throw std::out_of_range("Too great index!");
	return data.at(index);
}

Vector Vector::operator+(const Vector& other) const
{
	Vector result;
	if (this->size != other.size)
		throw std::domain_error("Differently sized vectors can't be added to each other!");
	result.setSize(size);
	for (unsigned i = 0; i < size; i++)
		result(i) = (*this)(i) + other(i);
	return result;
}

Vector Vector::operator-(const Vector& other) const
{
	Vector result;
	if (this->size != other.size)
		throw std::domain_error("Differently sized vectors can't be subtracted from each other!");
	result.setSize(size);
	for (unsigned i = 0; i < size; i++)
		result(i) = (*this)(i) - other(i);
	return result;
}

// nincs használva
//double Vector::dotProduct(const Vector& other) const
//{
//	if (this->size != other.size)
//		throw std::domain_error("Matrices can't be multiplied due to row size mismatch!");
//	double result = 0;
//	for (unsigned i = 0; i < size; i++)
//		result += (*this)(i) * other(i);
//	return result;
//}

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

// nincs használva
//void Vector::push(double value) {
//	setSize(size + 1);
//	data.push_back(value);
//}
