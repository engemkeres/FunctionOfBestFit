#include "Matrix.h"

unsigned Matrix::getRows() const {
	return rows;
}

unsigned Matrix::getColumns() const {
	return columns;
}
bool Matrix::setSize(unsigned rows, unsigned columns) {
	if ( (rows == 0 && columns == 0 ) || (this->rows==rows && this->columns==columns) )		// csak akkor kerül beállításra, ha eltér az alapértelmezettõl, vagy a jelenlegitõl
		return false;
	this->rows = rows;
	this->columns = columns;
	this->data.resize(rows * columns * sizeof(double));
	return true;
}

