#include "Matrix.h"

Matrix::Matrix(unsigned rows, unsigned columns)
{
	setSize(rows, columns);
}

Matrix::Matrix(const Matrix& other) {
	setSize(other.rows, other.columns);
	this->data = other.data;
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
		;// todo hibakezelés, csak akkor kerül beállításra, ha eltér az alapértelmezettõl, vagy a jelenlegitõl
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

void Matrix::print() const {
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
			std::cout << this->operator()(i, j) << '\t';
		std::cout << std::endl;
	}
}

void Matrix::fillFromPointVector(const PointVector& points, const std::vector<int>& function)
{
	empty();
	setSize(points.getLength(), function.size());
	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < columns; j++) {
			this->operator()(i,j) = pow(points(i, 'x'), function.at(j));
		}
	}
}

void Matrix::makeIdentity(unsigned size) {
	setSize(size,size);
	for (unsigned i = 0; i < size; i++)
	{
		for (unsigned j = 0; j < size; j++)
			if(i==j)
				this->operator()(i, j) = 1;
			else
				this->operator()(i, j) = 0;
	}
}