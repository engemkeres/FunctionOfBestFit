#pragma once
#include <iostream>
#include <vector>
#include <math.h>

/// \brief Matematikai vektor oszt�ly, line�lis algebr�t alkalmaz� met�dusok elv�gz�s�re
/// 
class Vector
{
private:
	unsigned size;
	std::vector<double> data;
public:
	/// \brief Vector objektum konstruktor
	/// @param size: vektor m�rete
	Vector(unsigned size = 0);
	/// \brief Vector objektum m�sol� konstruktor
	/// @param other: lem�soland� objektum
	Vector(const Vector& other);

	/// \brief Vektor m�ret�t adja vissza
	/// 
	/// @returns unsigned: vektor m�rete
	unsigned getSize() const;
	/// \brief Vetkor m�ret�t be�ll�tja
	/// @param size: k�v�nt m�ret
	///
	void setSize(unsigned size);
	/// \brief Vektor hossz�t adja vissza
	/// 
	/// @returns double: vektor m�rete
	double length() const;
	/// \brief Egys�ghossz�v� teszi a vektort
	/// 
	/// 
	void normalize();
	/// \brief Vektort adott �rt�kkel t�lti meg
	/// @param num: bet�ltend� �rt�k
	/// 
	void fill(double num);
	/// \brief L�trehoz egy olyan size nagys�g� vektort, mely a size-ad dimenzi�s t�rben egys�gvektor 
	/// @param size: kanonikus b�zis dimenzi�ja
	/// 
	void makeCanonicBase(unsigned size);
	/// \brief Vektor tartalm�nak ki�r�sa
	///
	///
	void print() const;
	/// \brief A vektorban tal�lhat� egy�tthat�k �s a megadott foksz�mok alapj�n ki�rja a legjobban illeszked� grafikon� polinom k�plet�t
	/// @param function: foksz�mokat tartalmaz� adatvektor
	/// 
	void printEquation(std::vector<unsigned> function) const;
	/// \brief Indexel� oper�tor, visszaadja az index-edik sz�mot a vektorban
	/// @param index: k�v�nt �rt�k indexe
	/// @returns double: index-edik helyen tal�lhat� �rt�k
	double operator()(unsigned index) const;
	/// \brief Indexel� oper�tor, visszaadja az index-edik sz�m referenci�j�t a vektorban
	/// @param index: k�v�nt �rt�k indexe
	/// @returns double&: index-edik helyen tal�lhat� �rt�k 
	double& operator()(unsigned size);
	/// \brief �sszead� oper�tor
	/// @param other: jobb oldali operandus
	/// @returns Vector: eredm�ny
	Vector operator+(const Vector& other) const;
	/// \brief Kivon�s oper�tor
	/// @param other: jobb oldali operandus, amit kivonunk
	/// @returns Vector: eredm�ny
	Vector operator-(const Vector& other) const;
	/// \brief Szorz�s oper�tor (sz�mmal)
	/// @param times: szorz� sz�m
	/// @returns Vector: eredm�ny
	Vector operator*(double times) const;
	/// \brief �rt�kad�s oper�tor
	/// @param other: �rt�k�l adand� vektor
	/// @returns Vector&: referenci�t ad vissza arra a m�dos�tott objektumra, amelyen a tagf�ggv�ny meg lett h�vva
	Vector& operator=(const Vector& other);
};

