#pragma once
#include <iostream>
#include <vector>
#include <math.h>

/// \brief Matematikai vektor osztály, lineális algebrát alkalmazó metódusok elvégzésére
/// 
class Vector
{
private:
	unsigned size;
	std::vector<double> data;
public:
	/// \brief Vector objektum konstruktor
	/// @param size: vektor mérete
	Vector(unsigned size = 0);
	/// \brief Vector objektum másoló konstruktor
	/// @param other: lemásolandó objektum
	Vector(const Vector& other);

	/// \brief Vektor méretét adja vissza
	/// 
	/// @returns unsigned: vektor mérete
	unsigned getSize() const;
	/// \brief Vetkor méretét beállítja
	/// @param size: kívánt méret
	///
	void setSize(unsigned size);
	/// \brief Vektor hosszát adja vissza
	/// 
	/// @returns double: vektor mérete
	double length() const;
	/// \brief Egységhosszúvá teszi a vektort
	/// 
	/// 
	void normalize();
	/// \brief Vektort adott értékkel tölti meg
	/// @param num: betöltendõ érték
	/// 
	void fill(double num);
	/// \brief Létrehoz egy olyan size nagyságú vektort, mely a size-ad dimenziós térben egységvektor 
	/// @param size: kanonikus bázis dimenziója
	/// 
	void makeCanonicBase(unsigned size);
	/// \brief Vektor tartalmának kiírása
	///
	///
	void print() const;
	/// \brief A vektorban található együtthatók és a megadott fokszámok alapján kiírja a legjobban illeszkedõ grafikonú polinom képletét
	/// @param function: fokszámokat tartalmazó adatvektor
	/// 
	void printEquation(std::vector<unsigned> function) const;
	/// \brief Indexelõ operátor, visszaadja az index-edik számot a vektorban
	/// @param index: kívánt érték indexe
	/// @returns double: index-edik helyen található érték
	double operator()(unsigned index) const;
	/// \brief Indexelõ operátor, visszaadja az index-edik szám referenciáját a vektorban
	/// @param index: kívánt érték indexe
	/// @returns double&: index-edik helyen található érték 
	double& operator()(unsigned size);
	/// \brief Összeadó operátor
	/// @param other: jobb oldali operandus
	/// @returns Vector: eredmény
	Vector operator+(const Vector& other) const;
	/// \brief Kivonás operátor
	/// @param other: jobb oldali operandus, amit kivonunk
	/// @returns Vector: eredmény
	Vector operator-(const Vector& other) const;
	/// \brief Szorzás operátor (számmal)
	/// @param times: szorzó szám
	/// @returns Vector: eredmény
	Vector operator*(double times) const;
	/// \brief Értékadás operátor
	/// @param other: értékül adandó vektor
	/// @returns Vector&: referenciát ad vissza arra a módosított objektumra, amelyen a tagfüggvény meg lett hívva
	Vector& operator=(const Vector& other);
};

