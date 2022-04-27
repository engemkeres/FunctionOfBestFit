#include "Matrix.h"

Matrix::Matrix(unsigned rows, unsigned columns)
{
	setSize(rows, columns);
}

Matrix::Matrix(const Matrix& other) {
	*this = other;
}

Matrix::~Matrix() {};

unsigned Matrix::getRows() const {
	return rows;
}

unsigned Matrix::getColumns() const {
	return columns;
}

void Matrix::setSize(unsigned rows, unsigned columns) {
	if ((rows == 0 && columns == 0) || (this->rows == rows && this->columns == columns))
		std::exit(11);// todo hibakezelés, csak akkor kerül beállításra, ha eltér az alapértelmezettõl, vagy a jelenlegitõl
	this->rows = rows;
	this->columns = columns;
	this->data.resize(rows * columns);
}

void Matrix::empty() {
	rows = 0;
	columns = 0;
	data.clear();		// vektort kiüríti, mérete 0, de a lefoglalt terület nincs felszabadítva
	data.shrink_to_fit();	// a vektor ténylegesen lefoglalt terülét is felszabadítja, mert 0 méret tartozik a clear-elt vektorhoz, és arra zsugorítja
}

double Matrix::operator()(unsigned row, unsigned column) const {
	if (row > rows - 1 || column > columns - 1)
		std::exit(4); // TODO hibakezelés
	return data.at(row * columns + column);
}

double& Matrix::operator()(unsigned row, unsigned column) {
	if (row > rows - 1 || column > columns - 1)
		std::exit(4); // TODO hibakezelés
	return data.at(row * columns + column);
}

Matrix Matrix::operator+(const Matrix& other) const
{
	Matrix result;
	if (this->rows != other.rows || this->columns != other.columns)
		std::exit(10); //TODO hibakezelés
	result.setSize(rows, columns);
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
			result(i, j) = (*this)(i, j) + other(i, j);
	}
	return result;
}

Matrix Matrix::operator-(const Matrix& other) const
{
	Matrix result;
	if (this->rows != other.rows || this->columns != other.columns)
		std::exit(9); //TODO hibakezelés
	result.setSize(rows, columns);
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
			result(i, j) = (*this)(i, j) - other(i, j);
	}
	return result;
}

Matrix Matrix::operator*(const Matrix& other) const
{
	Matrix result;
	if (this->columns != other.rows)
		std::exit(6); //TODO hibakezelés
	result.setSize(this->rows, other.columns);
	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < other.columns; j++) {
			result(i, j) = 0;
			for (unsigned k = 0; k < this->columns; k++) {
				result(i, j) += (*this)(i, k) * other(k, j);
			}
		}
	}
	return result;
}

Matrix Matrix::operator*(double times) const
{
	Matrix result;
	result.setSize(rows, columns);
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
			result(i, j) = (*this)(i, j) * times;
	}
	return result;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	setSize(other.rows, other.columns);
	this->data = other.data;
	return (*this);
}

void Matrix::transpose()
{
	Matrix tmp;
	tmp.setSize(columns, rows);
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++)
			tmp(j, i) = (*this)(i, j);
	*this = tmp;
	tmp.~Matrix();
}

void Matrix::print() const {
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
			std::cout << (*this)(i, j) << '\t';
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Matrix::fillFromPointVector(const PointVector& points, const std::vector<int>& function)
{
	empty();
	setSize(points.getLength(), function.size());
	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < columns; j++) {
			(*this)(i,j) = pow(points(i, 'x'), function.at(j));
		}
	}
}

void Matrix::fillFromArray(unsigned rows, unsigned columns, double* dataArray)	// TODO kinek a felelõssége jó indexet megadni? - meghívó, oda kell majd a catch
{
	empty();
	setSize(rows, columns);
	unsigned k=0;
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < rows; j++, k++)
			(*this)(i, j) = dataArray[k];
}

void Matrix::makeIdentity(unsigned size) {
	setSize(size,size);
	for (unsigned i = 0; i < size; i++)
	{
		for (unsigned j = 0; j < size; j++)
			if(i==j)
				(*this)(i, j) = 1;
			else
				(*this)(i, j) = 0;
	}
}

Matrix Matrix::extractColumn(unsigned columnindex) const {
	if (columnindex > columns - 1)
		std::exit(11); //TODO hibakezelés túl nagy index esetén
	Matrix result(rows, 1);
	for (unsigned i = 0; i < rows; i++)
		result(i, 0) = (*this)(i, columnindex);
	return result;
}