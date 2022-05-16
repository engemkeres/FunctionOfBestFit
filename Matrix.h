#pragma once
#include <iostream>
#include <vector>
#include "Vector.h"
#include <math.h>
#include <fstream>

/// Mátrix osztály, lineáris algebrát alkalmazó metódusok végrehajtásához
class Matrix
{
private:
	unsigned rows;
	unsigned columns;
	std::vector<double> data;		// STL tároló
public:
	/// \brief Mátrix objektum konstruktor
	/// @param rows: sorok száma
	/// @param columns: oszlopok száma
	/// 
	Matrix(unsigned rows=0, unsigned columns=0);
	/// \brief Mátrix objektum másoló konstruktor
	/// @param other: másolandó mátrix
	/// 
	Matrix(const Matrix& other);
	/// \brief Koordináta mátrixot konstruál egy fájlban található értékek alapján
	/// @param fName: fájl neve
	/// 
	Matrix(const char* fName);

	/// \brief Diadikus szorzat, két vektorból hoz létre mátrixot
	/// @param left: bal oldali oszlopvektor
	/// @param right: jobb oldali sorvektor
	Matrix(const Vector& left, const Vector& right);
	unsigned getRows() const; // pár helyen használhatnám ezt is, csak nem kötelezõ - változtatok majd ezen
	unsigned getColumns() const;
	/// \brief Visszaadja a mátrix méretét (sor*oszlop)
	/// 
	/// @returns unsigned: mátrix mérete
	unsigned getSize() const;
	/// \brief Identitásmátrixot hoz létre (négyzetes mátrix, mely a fõátló kivételével csupa 0, abban egyesek vannak)
	/// @param size: identitásmátrix mérete
	/// 
	void makeIdentity(unsigned size);
	/// \brief Méretparaméterek és az STL tároló méretének beállítása
	/// @param rows: sorok száma
	/// @param columms: oszlopok száma
	/// 
	void setSize(unsigned rows=0, unsigned columns=0);

	/// \brief Oszlopvektor készítése a mátrix adott indexû oszlopából
	/// @param columnindex: oszlop indexe
	/// @returns Vector: kiemelt oszlopvektor (másolat, mátrix nem rongálódik)
	Vector extractColumn(unsigned columnindex) const;
	/// \brief Mátrix kiíratás 
	/// 
	/// 
	void print() const;
	/// \brief Indexelõ operátor, érték szerint adja vissza adott sor adott elemét
	/// @param row: sorindex
	/// @param column: oszlopindex
	/// @returns double: row. sor column. eleme
	double operator()(unsigned row, unsigned column) const;
	/// \brief Indexelõ operátor, referenciát ad vissza az adott sor adott elemére
	/// @param row: sorindex
	/// @param column: oszlopindex
	/// @returns double&: row. sor column. elem referenciája
	double& operator()(unsigned row, unsigned columns);
	/// \brief Összeadás operátor
	/// @param other: jobb oldali operandus
	/// @returns Matrix: eredmény
	Matrix operator+(const Matrix& other) const;
	/// \brief Kivonás operátor
	/// @param other: jobb oldali operandus
	/// @returns Matrix: eredmény
	Matrix operator-(const Matrix& other) const;
	/// \brief Mátrix szorzás operátor
	/// @param other: jobb oldali operandus
	/// @returns Matrix: eredmény
	Matrix operator*(const Matrix& other) const;
	/// \brief Mátrix-vektor szorzás operátoe
	/// @param other: jobb oldali operandus
	/// @returns Vector: eredmény
	Vector operator*(const Vector& other) const;
	/// \brief Mátrix számmal való szorzás operátoe
	/// @param other: jobb oldali operandus
	/// @returns Matrix: eredmény
	Matrix operator*(double times) const;
	/// \brief Értékadás operátor
	/// @param other: másolandó objektum
	/// @returns Matrix&: referenciát ad vissza arra a módosított objektumra, amelyen a tagfüggvény meg lett hívva 
	Matrix& operator=(const Matrix& other);

	/// \brief Transzponálás: mátrix tükrözése a fõtengelyre
	/// 
	/// 
	void transpose();	
	/// \brief Legykisebb négyzetek módszeréhez hoz létre mátrixot
	/// @param function: fokszámokat tartalmazó adatvektor
	/// @returns Matrix: adott sorban az eredeti mátrix x koordinátája szerepel megfelelõ fokszámokon
	Matrix makeLeastSquaresMatrix(std::vector<unsigned> function) const;
	/// \brief Létrehozza a mátrix QR felbontásának Q, azaz ortogonalizált mátrixát,  Householder-tükrözés segítségével
	/// 
	/// @returns Matrix: Q ortogonalizált mátrix
	Matrix HouseholderOrthogonalize() const; // Q mátrixot adja vissza, melybõl a meghívó mátrix (A) segítségével R megkapható
	/// \brief Mátrix QR felbontás alapján a legkisebb négyzetek módszerével a legjobban illeszkedõ függvény együtthatóit keresi meg
	/// @param function: fokszámokat tartalmazó adatvektor
	/// @returns Vector: megoldás együtthatókat tartalmazó vektor
	Vector SolveLeastSquaresProblem(std::vector<unsigned> function) const;
	/// \brief Triviális egyenletrendszer megoldása
	/// @param other: változókra rendezett egyenletek jobb oldala
	/// @returns megoldás együtthatókat tartalmazó vektor
	Vector SolveUpperTriangle(const Vector& other) const;
};
