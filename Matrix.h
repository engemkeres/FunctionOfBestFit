#pragma once
#include <iostream>
#include <vector>
#include "Vector.h"
#include <math.h>
#include <fstream>

/// M�trix oszt�ly, line�ris algebr�t alkalmaz� met�dusok v�grehajt�s�hoz
class Matrix
{
private:
	unsigned rows;
	unsigned columns;
	std::vector<double> data;		// STL t�rol�
public:
	/// \brief M�trix objektum konstruktor
	/// @param rows: sorok sz�ma
	/// @param columns: oszlopok sz�ma
	/// 
	Matrix(unsigned rows=0, unsigned columns=0);
	/// \brief M�trix objektum m�sol� konstruktor
	/// @param other: m�soland� m�trix
	/// 
	Matrix(const Matrix& other);
	/// \brief Koordin�ta m�trixot konstru�l egy f�jlban tal�lhat� �rt�kek alapj�n
	/// @param fName: f�jl neve
	/// 
	Matrix(const char* fName);

	/// \brief Diadikus szorzat, k�t vektorb�l hoz l�tre m�trixot
	/// @param left: bal oldali oszlopvektor
	/// @param right: jobb oldali sorvektor
	Matrix(const Vector& left, const Vector& right);
	unsigned getRows() const; // p�r helyen haszn�lhatn�m ezt is, csak nem k�telez� - v�ltoztatok majd ezen
	unsigned getColumns() const;
	/// \brief Visszaadja a m�trix m�ret�t (sor*oszlop)
	/// 
	/// @returns unsigned: m�trix m�rete
	unsigned getSize() const;
	/// \brief Identit�sm�trixot hoz l�tre (n�gyzetes m�trix, mely a f��tl� kiv�tel�vel csupa 0, abban egyesek vannak)
	/// @param size: identit�sm�trix m�rete
	/// 
	void makeIdentity(unsigned size);
	/// \brief M�retparam�terek �s az STL t�rol� m�ret�nek be�ll�t�sa
	/// @param rows: sorok sz�ma
	/// @param columms: oszlopok sz�ma
	/// 
	void setSize(unsigned rows=0, unsigned columns=0);

	/// \brief Oszlopvektor k�sz�t�se a m�trix adott index� oszlop�b�l
	/// @param columnindex: oszlop indexe
	/// @returns Vector: kiemelt oszlopvektor (m�solat, m�trix nem rong�l�dik)
	Vector extractColumn(unsigned columnindex) const;
	/// \brief M�trix ki�rat�s 
	/// 
	/// 
	void print() const;
	/// \brief Indexel� oper�tor, �rt�k szerint adja vissza adott sor adott elem�t
	/// @param row: sorindex
	/// @param column: oszlopindex
	/// @returns double: row. sor column. eleme
	double operator()(unsigned row, unsigned column) const;
	/// \brief Indexel� oper�tor, referenci�t ad vissza az adott sor adott elem�re
	/// @param row: sorindex
	/// @param column: oszlopindex
	/// @returns double&: row. sor column. elem referenci�ja
	double& operator()(unsigned row, unsigned columns);
	/// \brief �sszead�s oper�tor
	/// @param other: jobb oldali operandus
	/// @returns Matrix: eredm�ny
	Matrix operator+(const Matrix& other) const;
	/// \brief Kivon�s oper�tor
	/// @param other: jobb oldali operandus
	/// @returns Matrix: eredm�ny
	Matrix operator-(const Matrix& other) const;
	/// \brief M�trix szorz�s oper�tor
	/// @param other: jobb oldali operandus
	/// @returns Matrix: eredm�ny
	Matrix operator*(const Matrix& other) const;
	/// \brief M�trix-vektor szorz�s oper�toe
	/// @param other: jobb oldali operandus
	/// @returns Vector: eredm�ny
	Vector operator*(const Vector& other) const;
	/// \brief M�trix sz�mmal val� szorz�s oper�toe
	/// @param other: jobb oldali operandus
	/// @returns Matrix: eredm�ny
	Matrix operator*(double times) const;
	/// \brief �rt�kad�s oper�tor
	/// @param other: m�soland� objektum
	/// @returns Matrix&: referenci�t ad vissza arra a m�dos�tott objektumra, amelyen a tagf�ggv�ny meg lett h�vva 
	Matrix& operator=(const Matrix& other);

	/// \brief Transzpon�l�s: m�trix t�kr�z�se a f�tengelyre
	/// 
	/// 
	void transpose();	
	/// \brief Legykisebb n�gyzetek m�dszer�hez hoz l�tre m�trixot
	/// @param function: foksz�mokat tartalmaz� adatvektor
	/// @returns Matrix: adott sorban az eredeti m�trix x koordin�t�ja szerepel megfelel� foksz�mokon
	Matrix makeLeastSquaresMatrix(std::vector<unsigned> function) const;
	/// \brief L�trehozza a m�trix QR felbont�s�nak Q, azaz ortogonaliz�lt m�trix�t,  Householder-t�kr�z�s seg�ts�g�vel
	/// 
	/// @returns Matrix: Q ortogonaliz�lt m�trix
	Matrix HouseholderOrthogonalize() const; // Q m�trixot adja vissza, melyb�l a megh�v� m�trix (A) seg�ts�g�vel R megkaphat�
	/// \brief M�trix QR felbont�s alapj�n a legkisebb n�gyzetek m�dszer�vel a legjobban illeszked� f�ggv�ny egy�tthat�it keresi meg
	/// @param function: foksz�mokat tartalmaz� adatvektor
	/// @returns Vector: megold�s egy�tthat�kat tartalmaz� vektor
	Vector SolveLeastSquaresProblem(std::vector<unsigned> function) const;
	/// \brief Trivi�lis egyenletrendszer megold�sa
	/// @param other: v�ltoz�kra rendezett egyenletek jobb oldala
	/// @returns megold�s egy�tthat�kat tartalmaz� vektor
	Vector SolveUpperTriangle(const Vector& other) const;
};
