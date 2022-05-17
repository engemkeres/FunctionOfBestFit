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

Matrix::Matrix(const Vector& left, const Vector& right)	// diadikus szorzat, két vektorból mátrixot hoz létre
{
	try {
		if (left.getSize() != right.getSize())
			throw std::domain_error("Vectors can't be multiplied, size mismatch!");	// eltérõ méretû vektorok
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
			throw std::out_of_range("Too great index!"); // indexelési hiba
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
			throw std::out_of_range("Too great index!"); // indexelési hiba
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
			throw std::domain_error("Differently sized matrices can't be added to each other!"); // eltérõ méretû mátrixok
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
			throw std::domain_error("Differently sized matrices can't be added to each other!"); // eltérõ méretû mátrixok
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
			throw std::domain_error("Matrices can't be multiplied due to column - row size mismatch!"); // hibás méretû mátrixok, nincs oszlop-sor egyezés
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
			throw std::domain_error("Matrix and vector can't be multiplied due to column - row size mismatch!"); // hibás méretû mátrixok, nincs oszlop-sor egyezés
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
			result(i, j) = (*this)(i, j) * times; // minden elemét szorozzuk
	}
	return result;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	setSize(other.rows, other.columns);
	this->data = other.data;
	return (*this);
}

void Matrix::transpose()														// transzponálás
{																				// 1 2 3	 1 4 7
	Matrix tmp;																	// 4 5 6  >> 2 5 8
	tmp.setSize(columns, rows);													// 7 8 9	 3 6 9
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++)
			tmp(j, i) = (*this)(i, j);
	*this = tmp;
}

void Matrix::print() const {													// diagnosztikai jellegû kiírás
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
			std::cout << (*this)(i, j) << '\t';
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Matrix::makeIdentity(unsigned size) {										// identitásmátrixxá alakítás
	setSize(size,size);															// 1 0 0 
	for (unsigned i = 0; i < size; i++)											// 0 1 0 
	{																			// 0 0 1 alakú
		for (unsigned j = 0; j < size; j++)
			if(i==j)
				(*this)(i, j) = 1;
			else
				(*this)(i, j) = 0;
	}
}

Vector Matrix::extractColumn(unsigned columnindex) const {						// adott indexû oszlopvektor kiemelése mátrixból
	try {
		if (columnindex > columns - 1)
			throw std::out_of_range("Too great index!");						// indexelési hiba
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
		Vector x = A.extractColumn(0);											// elsõ oszlop kiemelése 
		Vector e;
		e.makeCanonicBase(rows - iter);											// azonos méretû kanonikus bázisvektor [1;0;...;0]
		Vector u = x - e * x.length();											// u=x-||X||*e
		u.normalize();															// v=u/||u||

		Matrix I;
		I.makeIdentity(rows - iter);											//x hosszának megfelelõ egységmátrix
		Matrix Q;
		Q.setSize(rows - iter);													//Q is legyen ekkora
		Matrix dyad(u, u);														// diadikus szorzat
		Q = I - dyad * 2;														//Q = I - v * v^T * 2; Householder tükrözés

		Matrix identityQ;
		identityQ.makeIdentity(rows);			
		for (unsigned i = iter; i < rows; i++)									// Q mátrixot az A mátrix soraival megegyezõ egységmátrixxá kell kibõvíteni úgy, hogy Q-tól balra fel legyen a kitöltés
			for (unsigned j = iter; j < rows; j++)								// elég, ha egy egységmátrix jobb alsó almátrixát írjuk felül
				identityQ(i , j ) = Q(i-iter, j-iter);	
														
		QforEveryStep.push_back(identityQ);										//Q-k eltárolása, cikluson kívüli alkalmazásra
		Matrix H = Q * A;														// H=Q*A //H1-ben 0-k helyén 1*10^-16 értékekek vannak, ezekrõl tudjuk, hogy kézi számolás esetén mind 0 lenne,
		Matrix subH;															// kezelhetjük õket úgy (nem szükséges velük késõbb számítást végezni, elég kihagyni)

		subH.setSize(A.rows - 1, A.columns - 1);								//almátrix, melynek következõ ciklusban az elsõ oszlopát kell venni
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
	result.setSize(rows, function.size());											// a megadott polinom fokszámoknak megfelelõ mátrixot hoz létre,
	for (unsigned i = 0; i < result.rows; i++)										// melyen végrehajtható a legkisebb négyzetek módszerével történõ megoldás
		for (unsigned j = 0; j < result.columns; j++)				
			result(i, j) = pow((*this)(i, 0), function.at(j));						// a mátrix egyes soraiba az adott pont x koordinátái kerülnek megadott fokszámokon: 
																					// pl: (3,5) pont, y=a+bx+cx^2 polinom: 1 3 9 a hozzá tartozó sorban 
	return result;
}

Vector Matrix::SolveUpperTriangle(const Vector& other) const {
	try {
		if (columns > rows)
			throw std::runtime_error("Not enough coordinates to accurately calculate coefficients, the algorithm need at least [greatest exponent]+1 coordinates!");		// nem elég koordináta hibát okoz
	}
	catch (std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << "Try again with more coordinates in the file!" << std::endl;
		std::exit(-1);
	}
	try {
		for (unsigned i = 0; i < columns; i++)
			if (abs((*this)(i, i)) < 0.000000001) // epsilonos közelítés, mert == 0 nem szabad double-el
				throw std::domain_error("Equation system with infinite solutions!");
	}
	catch (std::domain_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << "Algorithm unable to fit polynomial." << std::endl;
		std::exit(-1);
	}
	Matrix Rsquare(columns, columns);	// alsó nullákat tartalmazó rész nélküli négyzetes mátrix
	Vector v(columns);
	for (unsigned i = 0; i < columns; i++) {
		for (unsigned j = 0; j < columns; j++)
			Rsquare(i, j) = (*this)(i, j);
		v(i) = other(i);
	}

	Vector result(columns);
	result.fill(0);
	for (int i = columns - 1; i >= 0; i--) {										// triviális egyenletrendszer megoldása, visszahelyettesítéssel
		result(i) = v(i);															// ax1+bx2+cx3 = d
		for (int j = columns - 1; j > i; j--) {										//     ex2+fx3 = g
			result(i) -= Rsquare(i, j) * result(j);									//         hx3 = i
																					// tehát x3=i/h, x2=(g-f*i/h)/e....stb.
		}
		result(i) /= Rsquare(i, i);
	}
	return result;
}

Vector Matrix::SolveLeastSquaresProblem(std::vector<double> function) const {
	Matrix A = (*this).makeLeastSquaresMatrix(function);							// Q*R = A
	Matrix Q = A.HouseholderOrthogonalize();										// Q ortogonalizált mátrix
	Matrix QT = Q;
	QT.transpose();
	Matrix R = QT * A;																// R felsõ háromszög mátrix
	Vector b = (*this).extractColumn(1);
	for (unsigned i = 0; i < R.rows; i++)
		for (unsigned j = 0; j < R.columns; j++)
			if (i > j)
				R(i, j) = 0;
	Vector y = QT * b;																// A*x=b
	Vector result = R.SolveUpperTriangle(y);										// Q*R*x=b
	return result;																	// R*x=y -> y=Q^(-1)*b
}																					// x = R^(-1)*y