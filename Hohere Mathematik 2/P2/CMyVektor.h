#pragma once
#include <cmath>
//#include "CMyMatrix.h"

class CMyVektor
{
private:
	int dimension;
	double* werte;

public:
	CMyVektor(int dim) : dimension(dim) { werte = new double[dim]; }

	int get_dimension() const { return dimension; }

	void set_number(double zahl, int index) { werte[index] = zahl; }

	double get_number(int index) { return werte[index]; }

	double get_length();
};

CMyVektor gradient(CMyVektor x, CMyVektor (*function)(CMyVektor x), int h); //NEU: Wackelstelle kann man mitgeben

CMyVektor operator+(CMyVektor a, CMyVektor b);

CMyVektor operator*(double lambda, CMyVektor a);

CMyVektor operator-(CMyVektor a, CMyVektor b); // NEU für die Minus-Operation

CMyVektor operator/(CMyVektor a, double h); //NEU: Division eins Vektors durch eine Zahl(h)

std::ostream& operator<<(std::ostream& os, CMyVektor x);

