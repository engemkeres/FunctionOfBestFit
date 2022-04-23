#include "Matrix.h"

unsigned Matrix::getRows() const {
	return rows;
}

unsigned Matrix::getColumns() const {
	return columns;
}
bool Matrix::setSize(unsigned rows, unsigned columns) {
	if ( (rows == 0 && columns == 0 ) || (this->rows==rows && this->columns==columns) )		// csak akkor ker�l be�ll�t�sra, ha elt�r az alap�rtelmezett�l, vagy a jelenlegit�l
		return false;
	this->rows = rows;
	this->columns = columns;
	this->data.resize(rows * columns * sizeof(double));
	return true;
}

