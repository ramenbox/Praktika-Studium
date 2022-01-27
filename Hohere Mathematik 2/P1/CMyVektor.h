#pragma once
#include <math.h>

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

void gradientenverfahren(CMyVektor x, double(*funktion)(CMyVektor x), double lambda = 1.0); //lambda soll default-Wert 1.0 haben

CMyVektor gradient(CMyVektor x, double (*function)(CMyVektor x));

CMyVektor operator+(CMyVektor a, CMyVektor b);

CMyVektor operator*(double lambda, CMyVektor a);

std::ostream& operator<<(std::ostream& os, CMyVektor x);
