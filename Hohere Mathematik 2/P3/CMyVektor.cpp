#include <iostream>
#include "CMyVektor.h"
using namespace std;

double CMyVektor::len()
{
	double length = 0;
	for (int i = 0; i < this->getD(); i++)
	{
		length += (werte[i] * werte[i]);
	}
	return sqrt(length);
}

CMyVektor& CMyVektor::operator=(const CMyVektor& a)
{
	this->dimension = a.getD();
	werte = new double[this->dimension];
	for (int i = 0; i < this->dimension; i++)
	{
		werte[i] = a.werte[i];
	}
	return *this;
}

CMyVektor operator+(CMyVektor a, CMyVektor b)
{
	const int dim = a.getD();
	CMyVektor c(dim);
	for (int i = 0; i < dim; i++)
	{
		c.setN(a.getN(i) + b.getN(i), i);
	}
	return c;
}

CMyVektor operator*(double lambda, CMyVektor a)
{
	const int dim = a.getD();
	CMyVektor d(dim);
	for (int i = 0; i < dim; i++)
	{
		d.setN(a.getN(i) * lambda, i);
	}
	return d;
}

CMyVektor operator-(CMyVektor a, CMyVektor b)
{
	const int dim = a.getD();
	CMyVektor differenz(dim);
	for (int i = 0; i < dim; i++)
	{
		differenz.setN(a.getN(i) - b.getN(i), i);
	}
	return differenz;
}

CMyVektor operator/(CMyVektor a, double h)
{
	const int dim = a.getD();
	CMyVektor quotient(dim);
	for (int i = 0; i < dim; i++)
	{
		quotient.setN(a.getN(i) / h, i);
	}
	return quotient;
}

std::ostream& operator<<(std::ostream& os, CMyVektor x)
{
	os << "(";
	const int dim = x.getD();
	for (int i = 0; i < dim; i++)
	{
		os << x.getN(i);
		if (!(i == dim - 1))
		{
			cout << "; ";
		}
	}
	os << ")";

	return os;
}

CMyVektor gradient(CMyVektor x, CMyVektor(*function)(CMyVektor x), int cnt)
{
	const double h = 1e-4;
	const int dim = x.getD();
	CMyVektor temp(dim);

	temp = x;

	for (int i = 0; i < dim; i++)
	{
		if (i == cnt)
		{
			temp.setN(x.getN(i) + h, i);
		}
	}
	return (function(temp) - function(x)) / h; // Differenzqoutient
}



