#include "Matrix.h"

Matrix::Matrix(unsigned rows, unsigned columns)
{
	setSize(rows, columns);
}

Matrix::Matrix(const Matrix& other) {
	*this = other;
}

Matrix::Matrix(const char* fName) : rows(0), columns(2)
{									
	std::ifstream inputFile;
	try {
		inputFile.open(fName);
		if (inputFile.is_open())
		{
			double temp;
			while (true) {
				for (int i = 0; i < 2; i++) {
					inputFile >> std::ws;
					inputFile >> temp;
					if (inputFile.fail())
						throw std::invalid_argument("File has non-numeric characters, not usable!");
					data.push_back(temp);
					inputFile >> std::ws;
					if(i==0 && inputFile.eof())
						throw std::invalid_argument("Odd amount of numbers, can't produce coordinates, unusable file!");
				}
				rows++;
				if (inputFile.eof())
					break;
			}
			inputFile.close();
		}
		else
			throw std::invalid_argument("File cannot be found!");
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << "Try again with another file." << std::endl;
		std::exit(-1);
	}
}

Matrix::Matrix(const Vector& left, const Vector& right)	// diadikus szorzat, k�t vektorb�l m�trixot hoz l�tre
{
	try {
		if (left.getSize() != right.getSize())
			throw std::domain_error("Vectors can't be multiplied, size mismatch!");	// elt�r� m�ret� vektorok
	}
	catch (std::domain_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
	setSize(left.getSize(), left.getSize());
	for (unsigned i = 0; i < left.getSize(); i++)
		for (unsigned j = 0; j < left.getSize(); j++)
			(*this)(i, j) = left(i) * right(j);
}

unsigned Matrix::getRows() const {
	return rows;
}

unsigned Matrix::getColumns() const {
	return columns;
}

unsigned Matrix::getSize() const {
	return getColumns() * getRows();
}

void Matrix::setSize(unsigned rows, unsigned columns) {
	this->rows = rows;
	this->columns = columns;
	this->data.resize(rows * columns);
}

double Matrix::operator()(unsigned row, unsigned column) const {
	try {
		if (row > rows - 1 || column > columns - 1)
			throw std::out_of_range("Too great index!"); // indexel�si hiba
	}
	catch (std::out_of_range& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
	return data.at(row * columns + column);
}

double& Matrix::operator()(unsigned row, unsigned column) {
	try {
		if (row > rows - 1 || column > columns - 1)
			throw std::out_of_range("Too great index!"); // indexel�si hiba
	}
	catch (std::out_of_range& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
	return data.at(row * columns + column);
}

Matrix Matrix::operator+(const Matrix& other) const
{
	Matrix result;
	try {
		if (this->rows != other.rows || this->columns != other.columns)
			throw std::domain_error("Differently sized matrices can't be added to each other!"); // elt�r� m�ret� m�trixok
	}
	catch (std::domain_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
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
	try {
		if (this->rows != other.rows || this->columns != other.columns)
			throw std::domain_error("Differently sized matrices can't be added to each other!"); // elt�r� m�ret� m�trixok
	}
	catch (std::domain_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
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
	try {
		if (this->columns != other.rows)
			throw std::domain_error("Matrices can't be multiplied due to column - row size mismatch!"); // hib�s m�ret� m�trixok, nincs oszlop-sor egyez�s
	}
	catch (std::domain_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
	Matrix result;
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

Vector Matrix::operator*(const Vector& other) const
{
	try {
		if (this->columns != other.getSize())
			throw std::domain_error("Matrix and vector can't be multiplied due to column - row size mismatch!"); // hib�s m�ret� m�trixok, nincs oszlop-sor egyez�s
	}
	catch (std::domain_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
	Vector result;
	result.setSize(rows);
	result.fill(0);
	for (unsigned i = 0; i < rows;i++)
		for (unsigned j = 0; j < columns; j++)
			result(i) += (*this)(i, j) * other(j);
	return result;
		
}

Matrix Matrix::operator*(double times) const 
{
	Matrix result;
	result.setSize(rows, columns);
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
			result(i, j) = (*this)(i, j) * times; // minden elem�t szorozzuk
	}
	return result;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	setSize(other.rows, other.columns);
	this->data = other.data;
	return (*this);
}

void Matrix::transpose()														// transzpon�l�s
{																				// 1 2 3	 1 4 7
	Matrix tmp;																	// 4 5 6  >> 2 5 8
	tmp.setSize(columns, rows);													// 7 8 9	 3 6 9
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++)
			tmp(j, i) = (*this)(i, j);
	*this = tmp;
}

void Matrix::print() const {													// diagnosztikai jelleg� ki�r�s
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
			std::cout << (*this)(i, j) << '\t';
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Matrix::makeIdentity(unsigned size) {										// identit�sm�trixx� alak�t�s
	setSize(size,size);															// 1 0 0 
	for (unsigned i = 0; i < size; i++)											// 0 1 0 
	{																			// 0 0 1 alak�
		for (unsigned j = 0; j < size; j++)
			if(i==j)
				(*this)(i, j) = 1;
			else
				(*this)(i, j) = 0;
	}
}

Vector Matrix::extractColumn(unsigned columnindex) const {						// adott index� oszlopvektor kiemel�se m�trixb�l
	try {
		if (columnindex > columns - 1)
			throw std::out_of_range("Too great index!");						// indexel�si hiba
	}
	catch (std::out_of_range& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
	Vector result;
	result.setSize(rows);
	for (unsigned i = 0; i < rows; i++)
		result(i) = (*this)(i, columnindex);
	return result;
}



Matrix Matrix::HouseholderOrthogonalize() const {
	Matrix A = (*this);
	unsigned howManyIterations = std::min(rows - 1, columns);
	std::vector<Matrix> QforEveryStep;
	for (unsigned iter = 0; iter < howManyIterations; iter++) {
		Vector x = A.extractColumn(0);											// els� oszlop kiemel�se 
		Vector e;
		e.makeCanonicBase(rows - iter);											// azonos m�ret� kanonikus b�zisvektor [1;0;...;0]
		Vector u = x - e * x.length();											// u=x-||X||*e
		u.normalize();															// v=u/||u||

		Matrix I;
		I.makeIdentity(rows - iter);											//x hossz�nak megfelel� egys�gm�trix
		Matrix Q;
		Q.setSize(rows - iter);													//Q is legyen ekkora
		Matrix dyad(u, u);														// diadikus szorzat
		Q = I - dyad * 2;														//Q = I - v * v^T * 2; Householder t�kr�z�s

		Matrix identityQ;
		identityQ.makeIdentity(rows);			
		for (unsigned i = iter; i < rows; i++)									// Q m�trixot az A m�trix soraival megegyez� egys�gm�trixx� kell kib�v�teni �gy, hogy Q-t�l balra fel legyen a kit�lt�s
			for (unsigned j = iter; j < rows; j++)								// el�g, ha egy egys�gm�trix jobb als� alm�trix�t �rjuk fel�l
				identityQ(i , j ) = Q(i-iter, j-iter);	
														
		QforEveryStep.push_back(identityQ);										//Q-k elt�rol�sa, cikluson k�v�li alkalmaz�sra
		Matrix H = Q * A;														// H=Q*A //H1-ben 0-k hely�n 1*10^-16 �rt�kekek vannak, ezekr�l tudjuk, hogy k�zi sz�mol�s eset�n mind 0 lenne,
		Matrix subH;															// kezelhetj�k �ket �gy (nem sz�ks�ges vel�k k�s�bb sz�m�t�st v�gezni, el�g kihagyni)

		subH.setSize(A.rows - 1, A.columns - 1);								//alm�trix, melynek k�vetkez� ciklusban az els� oszlop�t kell venni
		for (unsigned i = 1; i < H.rows; i++)									//
			for (unsigned j = 1; j < H.columns; j++)
				subH(i - 1, j - 1) = H(i, j);
												
		A = subH;
	}
	Matrix finalQ;
	finalQ.makeIdentity(rows);													//Q=Q1*Q2*...*QN
	for (unsigned i = 0; i < howManyIterations; i++) {
		finalQ= QforEveryStep.at(howManyIterations - 1 - i) * finalQ;
	}
	return finalQ;
}

Matrix Matrix::makeLeastSquaresMatrix(std::vector<double> function) const {
	try {
		if (columns != 2)
			throw std::logic_error("Matrix not usable for 2D coordinates, it doesn't have 2 columns exactly!");
	}
	catch (std::logic_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::exit(-1);
	}
	Matrix result;
	result.setSize(rows, function.size());											// a megadott polinom foksz�moknak megfelel� m�trixot hoz l�tre,
	for (unsigned i = 0; i < result.rows; i++)										// melyen v�grehajthat� a legkisebb n�gyzetek m�dszer�vel t�rt�n� megold�s
		for (unsigned j = 0; j < result.columns; j++)				
			result(i, j) = pow((*this)(i, 0), function.at(j));						// a m�trix egyes soraiba az adott pont x koordin�t�i ker�lnek megadott foksz�mokon: 
																					// pl: (3,5) pont, y=a+bx+cx^2 polinom: 1 3 9 a hozz� tartoz� sorban 
	return result;
}

Vector Matrix::SolveUpperTriangle(const Vector& other) const {
	try {
		if (columns > rows)
			throw std::runtime_error("Not enough coordinates to accurately calculate coefficients, the algorithm need at least [greatest exponent]+1 coordinates!");		// nem el�g koordin�ta hib�t okoz
	}
	catch (std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << "Try again with more coordinates in the file!" << std::endl;
		std::exit(-1);
	}
	try {
		for (unsigned i = 0; i < columns; i++)
			if (abs((*this)(i, i)) < 0.000000001) // epsilonos k�zel�t�s, mert == 0 nem szabad double-el
				throw std::domain_error("Equation system with infinite solutions!");
	}
	catch (std::domain_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << "Algorithm unable to fit polynomial." << std::endl;
		std::exit(-1);
	}
	Matrix Rsquare(columns, columns);	// als� null�kat tartalmaz� r�sz n�lk�li n�gyzetes m�trix
	Vector v(columns);
	for (unsigned i = 0; i < columns; i++) {
		for (unsigned j = 0; j < columns; j++)
			Rsquare(i, j) = (*this)(i, j);
		v(i) = other(i);
	}

	Vector result(columns);
	result.fill(0);
	for (int i = columns - 1; i >= 0; i--) {										// trivi�lis egyenletrendszer megold�sa, visszahelyettes�t�ssel
		result(i) = v(i);															// ax1+bx2+cx3 = d
		for (int j = columns - 1; j > i; j--) {										//     ex2+fx3 = g
			result(i) -= Rsquare(i, j) * result(j);									//         hx3 = i
																					// teh�t x3=i/h, x2=(g-f*i/h)/e....stb.
		}
		result(i) /= Rsquare(i, i);
	}
	return result;
}

Vector Matrix::SolveLeastSquaresProblem(std::vector<double> function) const {
	Matrix A = (*this).makeLeastSquaresMatrix(function);							// Q*R = A
	Matrix Q = A.HouseholderOrthogonalize();										// Q ortogonaliz�lt m�trix
	Matrix QT = Q;
	QT.transpose();
	Matrix R = QT * A;																// R fels� h�romsz�g m�trix
	Vector b = (*this).extractColumn(1);
	for (unsigned i = 0; i < R.rows; i++)
		for (unsigned j = 0; j < R.columns; j++)
			if (i > j)
				R(i, j) = 0;
	Vector y = QT * b;																// A*x=b
	Vector result = R.SolveUpperTriangle(y);										// Q*R*x=b
	return result;																	// R*x=y -> y=Q^(-1)*b
}																					// x = R^(-1)*y