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
	double temp;
	try {
		inputFile.open(fName);
		if (inputFile.is_open())
		{
			while (true) {
				inputFile >> temp;
				data.push_back(temp);
				// ha p�ratlan adatmennyis�g, kell hibakezel�s
				if (inputFile.eof())
					throw std::runtime_error("Odd amount of numbers or empty lines, unusable file!");
				// akkor is ezt a hib�t dobja, ha kett�n�l t�bb enter van a f�jl v�g�n
				inputFile >> temp;
				data.push_back(temp);
				rows++;
				if (inputFile.eof())
					break;
			}
			inputFile.close();
		}
		else
			throw std::runtime_error("File cannot be found!");
	}
	catch (const std::runtime_error& e) {
		std::cerr << "exception: " << e.what() << std::endl;
		std::cerr << "Terminating program.";
		std::exit(1);
	}
	// ha nem ny�lik meg a f�jl, hibakezel�s - jelenleg le�ll a program, ha ebbe �tk�zik
}

Matrix::~Matrix() {};

unsigned Matrix::getRows() const {
	return rows;
}

unsigned Matrix::getColumns() const {
	return columns;
}

void Matrix::setSize(unsigned rows, unsigned columns) {
	this->rows = rows;
	this->columns = columns;
	this->data.resize(rows * columns);
}

void Matrix::empty() {
	rows = 0;
	columns = 0;
	data.clear();		// vektort ki�r�ti, m�rete 0, de a lefoglalt ter�let nincs felszabad�tva
	data.shrink_to_fit();	// a vektor t�nylegesen lefoglalt ter�l�t is felszabad�tja, mert 0 m�ret tartozik a clear-elt vektorhoz, �s arra zsugor�tja
}

double Matrix::operator()(unsigned row, unsigned column) const {
	if (row > rows - 1 || column > columns - 1)
		std::exit(4); // TODO hibakezel�s
	return data.at(row * columns + column);
}

double& Matrix::operator()(unsigned row, unsigned column) {
	if (row > rows - 1 || column > columns - 1)
		std::exit(4); // TODO hibakezel�s
	return data.at(row * columns + column);
}

Matrix Matrix::operator+(const Matrix& other) const
{
	Matrix result;
	if (this->rows != other.rows || this->columns != other.columns)
		std::exit(10); //TODO hibakezel�s
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
		std::exit(9); //TODO hibakezel�s
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
	if (this->columns != other.rows)
		std::exit(6); //TODO hibakezel�s
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
	if (this->columns != other.getSize())
		std::exit(16); //TODO hibakezel�s
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
}

Matrix& Matrix::pushVector(const Vector& other)
{
	if (rows == 0 && columns == 0)
		(*this).setSize(other.getSize(), 0);
	if (rows != other.getSize() )
		std::exit(16); //TODO hibakezel�s
	Matrix temp(rows, columns + 1);
	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < columns; j++)
			temp(i, j) = (*this)(i, j);
		temp(i, columns) = other(i);
	}
	(*this) = temp;
	return (*this);
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

//void Matrix::fillFromPointVector(const PointVector& points, const std::vector<int>& function)
//{
//	empty();
//	setSize(points.getLength(), function.size());
//	for (unsigned i = 0; i < rows; i++) {
//		for (unsigned j = 0; j < columns; j++) {
//			(*this)(i,j) = pow(points(i, 'x'), function.at(j));
//		}
//	}
//}

void Matrix::fillFromArray(unsigned rows, unsigned columns, double* dataArray)	// TODO kinek a felel�ss�ge j� indexet megadni? - megh�v�, oda kell majd a catch
{
	empty();
	setSize(rows, columns);
	unsigned k=0;
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++, k++)
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

Vector Matrix::extractColumn(unsigned columnindex) const {
	if (columnindex > columns - 1)
		std::exit(11); //TODO hibakezel�s t�l nagy index eset�n
	Vector result;
	result.setSize(rows);
	for (unsigned i = 0; i < rows; i++)
		result(i) = (*this)(i, columnindex);
	return result;
}

void Matrix::vectorToMatrix(const Vector& other) {
	(*this).empty();
	setSize(other.getSize(), 1);
	for (unsigned i = 0; i < rows; i++)
		(*this)(i, 0) = other(i);
}
// m�r a keresett f�ggv�ny szerint be�ll�tott m�trixra m�k�dik - m�sik f�ggv�ny lesz, ami sz�tbontja a koordin�ta m�trixot, illetve ezt is fell kell majd bontani legal�bb 5-6 f�ggv�nyre
Vector Matrix::HouseholderSolve() {
	Matrix A = (*this);
	unsigned matrixRows = (*this).rows;
	unsigned matrixColumns = (*this).columns;
	unsigned howManyIterations = std::min(rows - 1, columns);
	std::vector<Matrix> QforEveryStep;
	for (unsigned i = 0; i < howManyIterations; i++) {
		Vector x = (*this).extractColumn(0);		x.print();		// els� oszlop kiemel�se 
		Vector e(matrixRows - i);					// azonos m�ret� kanonikus b�zisvektor [1;0;...;0]
		e.fill(0);
		e(0) = 1;									e.print();
		Vector u = x - e * x.length();				u.print();			// u=x-||X||*e
		Vector v = u * (1 / u.length());			v.print();					// v=u/||u||
		Matrix I;
		I.makeIdentity(matrixRows - i);				I.print();			//x hossz�nak megfelel� egys�gm�trix
		Matrix Q;
		Q.setSize(matrixRows - i);					//Q is legyen ekkora
		// kell diadikus szorzat implement�ci� - el�sz�r m�trixx� kell alak�tani a vektor, majd �nmaga*transzpon�lt(�nmaga)
		Matrix w;
		w.vectorToMatrix(v);						// m�trixx� alak�tott vektor, hogy lehessen diadikus szorzatot alkotni
		Matrix y = w;
		w.transpose();								y.print(); w.print();			//y= valamilyen vektor, w=el�z� vektor transzpont�ltja
		Q = I - y * w * 2;							Q.print();
		//Q-t Matrix.rows sor�v� �s oszlop�v� kell tenni el�sz�r, hogy ut�na csak �ssze kelljen szorozni �ket, de �gy, hogy a b�v�tett r�sz egys�gm�trix-szer� legyen
		Matrix identityQ;
		identityQ.makeIdentity(matrixRows);			identityQ.print();
		for (unsigned i = howManyIterations-1; i < matrixRows; i++)
			for (unsigned j = howManyIterations-1; j < matrixRows; j++)
				identityQ(i , j ) = Q(i-howManyIterations-1, j-howManyIterations-1);
													identityQ.print();				// valami itt nem j�, de eddig az els� teszt v�gig lefutott
		QforEveryStep.push_back(identityQ);	//Q-k elt�rol�sa, cikluson k�v�li alkalmaz�sra
		Matrix H = Q * (*this);						H.print();				// H=Q*A
		Matrix subH;
		subH.setSize(rows - 1, columns - 1);	//alm�trix, melynek k�vetkez� ciklusban az els� oszlop�t kell venni
		for (unsigned i = 1; i < H.rows; i++)
			for (unsigned j = 1; j < H.columns; j++)
				subH(i - 1, j - 1) = H(i, j);
													subH.print();
		(*this) = subH;
		//itt kezd�dik majd valahogy �jra, a subH-nak vessz�k az els� oszlop�t
	}
	Matrix finalQ;
	finalQ.makeIdentity(matrixRows);
	for (unsigned i = 0; i < howManyIterations; i++) {
		finalQ.transpose();
		QforEveryStep.at(howManyIterations - 1 - i).transpose();
		finalQ = QforEveryStep.at(howManyIterations - 1 - i) * finalQ;
	}
													finalQ.print();
	Matrix finalQtransposed = finalQ;
	finalQtransposed.transpose();
	Matrix R = finalQtransposed * A;				R.print();


	//temporary, csak hogy fusson
	Vector vir(2);
	return vir;
}