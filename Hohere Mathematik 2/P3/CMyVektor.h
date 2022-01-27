#pragma once
#include <cmath>

class CMyVektor
{
private:
	int dimension;
	double* werte;

public:
	CMyVektor(int dim) : dimension(dim) { werte = new double[dim]; }

	CMyVektor(const CMyVektor& a)
	{
		dimension = a.getD();
		werte = new double[dimension];
		for (int i = 0; i < dimension; i++)
		{
			werte[i] = a.werte[i];
		}
	}

	int getD() const { return dimension; }

	void setN(double n, int i) { werte[i] = n; }

	double getN(int i) { return werte[i]; }

	double len();

	CMyVektor& operator=(const CMyVektor& a);
};

CMyVektor gradient(CMyVektor x, CMyVektor(*function)(CMyVektor x), int h);

CMyVektor operator+(CMyVektor a, CMyVektor b);

CMyVektor operator*(double lambda, CMyVektor a);

CMyVektor operator-(CMyVektor a, CMyVektor b);

CMyVektor operator/(CMyVektor a, double h);

std::ostream& operator<<(std::ostream& os, CMyVektor x);

