#include "Matrix.h"

Matrix::Matrix(unsigned rows, unsigned columns)
{
	setSize(rows, columns);
}

Matrix::Matrix(const Matrix& other) {
	*this = other;
}

Matrix::Matrix(const char* fName) : rows(0), columns(2)
{																			// TODO hibakezel�s, mely �j lehet�s�get biztos�t m�sik f�jl, m�sik foksz�m megadad�s�ra, �s nem egyb�l kil�p a program
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

unsigned Matrix::getSize() const {
	return columns * rows;
}

void Matrix::setSize(unsigned rows, unsigned columns) {
	this->rows = rows;
	this->columns = columns;
	this->data.resize(rows * columns);
}

void Matrix::empty() {
	rows = 0;
	columns = 0;
	data.clear();																// vektort ki�r�ti, m�rete 0, de a lefoglalt ter�let nincs felszabad�tva
	data.shrink_to_fit();														// a vektor t�nylegesen lefoglalt ter�l�t is felszabad�tja, 
}																				// mert 0 m�ret tartozik a clear-elt vektorhoz, �s arra zsugor�tja

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

void Matrix::transpose()														// transzpon�l�s
{																				// 1 2 3	 1 4 7
	Matrix tmp;																	// 4 5 6  >> 2 5 8
	tmp.setSize(columns, rows);													// 7 8 9	 3 6 9
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++)
			tmp(j, i) = (*this)(i, j);
	*this = tmp;
}

void Matrix::pushVector(const Vector& other)									// oszlopvektor beilleszt�se m�trix elej�be 
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

void Matrix::fillFromArray(unsigned rows, unsigned columns, double* dataArray)	// TODO kinek a felel�ss�ge j� indexet megadni? - megh�v�, oda kell majd a catch
{
	empty();
	setSize(rows, columns);
	unsigned k=0;
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++, k++)
			(*this)(i, j) = dataArray[k];
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
	if (columnindex > columns - 1)
		std::exit(11); //TODO hibakezel�s t�l nagy index eset�n
	Vector result;
	result.setSize(rows);
	for (unsigned i = 0; i < rows; i++)
		result(i) = (*this)(i, columnindex);
	return result;
}

//void Matrix::vectorToMatrix(const Vector& other) {
//	(*this).empty();
//	setSize(other.getSize(), 1);
//	for (unsigned i = 0; i < rows; i++)
//		(*this)(i, 0) = other(i);
//}

void Matrix::outerProduct(const Vector& other) {								// k�t vektor diadikus szorzata
	Matrix vToTranspose;														// A=v*v^T
	vToTranspose.pushVector(other);												// ha v vektor n sor�, akkor A egy n*n-es m�trix lesz
	Matrix v = vToTranspose;
	vToTranspose.transpose();
	(*this) = v * vToTranspose;
}

// m�r a keresett f�ggv�ny szerint be�ll�tott m�trixra m�k�dik - m�sik f�ggv�ny lesz, ami sz�tbontja a koordin�ta m�trixot
Matrix Matrix::HouseholderOrthogonalize() const {
	Matrix A = (*this);
	unsigned howManyIterations = std::min(rows - 1, columns);
	std::vector<Matrix> QforEveryStep;
	for (unsigned iter = 0; iter < howManyIterations; iter++) {
		Vector x = A.extractColumn(0);				x.print();					// els� oszlop kiemel�se 
		Vector e;
		e.makeCanonicBase(rows - iter);				e.print();					// azonos m�ret� kanonikus b�zisvektor [1;0;...;0]
		Vector u = x - e * x.length();				u.print();					// u=x-||X||*e
		Vector v = u * (1 / u.length());			v.print();					// v=u/||u||

		Matrix I;
		I.makeIdentity(rows - iter);				I.print();					//x hossz�nak megfelel� egys�gm�trix
		Matrix Q;
		Q.setSize(rows - iter);													//Q is legyen ekkora
		Matrix dyad;
		dyad.outerProduct(v);													// diadikus szorzat
		Q = I - dyad * 2;							Q.print();					//Q = I - v * v^T * 2; Householder t�kr�z�s

		Matrix identityQ;
		identityQ.makeIdentity(rows);				identityQ.print();
		for (unsigned i = iter; i < rows; i++)									// Q m�trixot az A m�trix soraival megegyez� egys�gm�trixx� kell kib�v�teni �gy, hogy Q-t�l balra fel legyen a kit�lt�s
			for (unsigned j = iter; j < rows; j++)								// el�g, ha egy egys�gm�trix jobb als� alm�trix�t �rjuk fel�l
				identityQ(i , j ) = Q(i-iter, j-iter);	
													identityQ.print();			
		QforEveryStep.push_back(identityQ);										//Q-k elt�rol�sa, cikluson k�v�li alkalmaz�sra
		Matrix H = Q * A;							H.print();					// H=Q*A //H1-ben 0-k hely�n 1*10^-16 �rt�kekek vannak, ezekr�l tudjuk, hogy k�zi sz�mol�s eset�n mind 0 lenne,
		Matrix subH;															// kezelhetj�k �ket �gy (nem sz�ks�ges vel�k k�s�bb sz�m�t�st v�gezni, el�g kihagyni)

		subH.setSize(A.rows - 1, A.columns - 1);								//alm�trix, melynek k�vetkez� ciklusban az els� oszlop�t kell venni
		for (unsigned i = 1; i < H.rows; i++)									//
			for (unsigned j = 1; j < H.columns; j++)
				subH(i - 1, j - 1) = H(i, j);
													subH.print();
		A = subH;
	}
	Matrix finalQ;
	finalQ.makeIdentity(rows);													//Q=Q1*Q2*...*QN
	for (unsigned i = 0; i < howManyIterations; i++) {
		//finalQ.transpose();
		//QforEveryStep.at(howManyIterations - 1 - i).transpose();
		//finalQ = QforEveryStep.at(howManyIterations - 1 - i) * finalQ;
		finalQ= QforEveryStep.at(howManyIterations - 1 - i) * finalQ;
	}
	finalQ.print();
	return finalQ;
}

Matrix Matrix::makeLeastSquaresMatrix(std::vector<unsigned> function) const {
	if (columns != 2)
		std::exit(18);//TODO hibakezel�s
	Matrix result;
	result.setSize(rows, function.size());											// a megadott polinom foksz�moknak megfelel� m�trixot hoz l�tre,
	for (unsigned i = 0; i < result.rows; i++)										// melyen v�grehajthat� a legkisebb n�gyzetek m�dszer�vel t�rt�n� megold�s
		for (unsigned j = 0; j < result.columns; j++)				
			result(i, j) = pow((*this)(i, 0), function.at(j));						// a m�trix egyes soraiba az adott pont x koordin�t�i ker�lnek megadott foksz�mokon: 
	result.print();																	// pl: (3,5) pont, y=a+bx+cx^2 polinom: 1 3 9 a hozz� tartoz� sorban 
	return result;
}

//Matrix Matrix::invertUpperTriangleSquare() const {
//	Matrix inverse(columns,columns);
//	for (unsigned i = 0; i < columns; i++)
//		for (unsigned j = 0; j < columns; j++)
//			inverse(i, j) = 0;
//	// nem m�k�dik, t�bb dolog m�k�d�k�pesnek t�nik
//	// TODO invert�l�s, ezen k�v�l m�r minden m�k�d�k�pesnek t�nik
//	
//	inverse.print();
//	return inverse;
//}

Vector Matrix::SolveUpperTriangle(const Vector& other) const {
	if (columns > rows)
		std::exit(19);//TODO hibakezel�s, nincs megold�s, t�bb pont k�ne: megadott foksz�mokkal legal�bb egyezzen meg a pontok sz�ma, de ink�bb legyen t�bb, j�val t�bb
	for (unsigned i = 0; i < columns; i++)
		if (abs((*this)(i, i)) < 0.000000001 ) // epsilonos k�zel�t�s, mert == 0 nem szabad double-el
			std::exit(20); //TODO hibakezel�s
	Matrix Rsquare(columns, columns);	// als� null�kat tartalmaz� r�sz n�lk�li n�gyzetes m�trix
	Vector v(columns);
	for (unsigned i = 0; i < columns; i++) {
		for (unsigned j = 0; j < columns; j++)
			Rsquare(i, j) = (*this)(i, j);
		v(i) = other(i);
	}
	Rsquare.print();
	v.print();
	//TODO fels� h�romsz�g n�gyzetes m�trix invert�l�sa
	//Matrix inverseRSquare = Rsquare.invertUpperTriangleSquare();
	//return inverseRSquare * b;

	Vector result(columns);
	result.fill(0);
	double temp;
	for (int i = columns - 1; i >= 0; i--) {										// trivi�lis egyenletrendszer megold�sa, visszahelyettes�t�ssel
		result(i) = v(i);															// ax1+bx2+cx3 = d
		for (int j = columns - 1; j > i; j--) {										//     ex2+fx3 = g
			result(i) -= Rsquare(i, j) * result(j);									//         hx3 = i
			result.print();															// teh�t x3=i/h, x2=(g-f*i/h)/e....stb.
		}
		result(i) /= Rsquare(i, i);
		result.print();
	}
	result.print();
	return result;
}

Vector Matrix::SolveLeastSquaresProblem(std::vector<unsigned> function) const {
	Matrix A = (*this).makeLeastSquaresMatrix(function);
	Matrix Q = A.HouseholderOrthogonalize();
	Matrix QT = Q;
	QT.transpose();
	QT.print();
	Matrix R = QT * A;
	R.print();
	// TODO R floating point hiba korrig�l�s, vagy csak hagyjuk figyelmen k�v�l azon �rt�keket, k�zi sz�mol�s eset�n null�k lenn�nek
	Vector b = (*this).extractColumn(1);
	unsigned iter = std::min(R.rows, R.columns);
	for (unsigned i = 0; i < R.rows; i++)
		for (unsigned j = 0; j < R.columns; j++)
			if (i > j)
				R(i, j) = 0;
	R.print();
	Vector y = QT * b;
	Vector result = R.SolveUpperTriangle(y);
	return result;
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

