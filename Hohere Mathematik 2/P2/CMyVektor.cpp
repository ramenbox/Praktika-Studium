#include <iostream>
#include "CMyVektor.h"
using namespace std;

double CMyVektor::get_length()
{
	double length = 0;
	for (int i = 0; i < get_dimension(); i++)
	{
		length += (werte[i] * werte[i]);
	}
	return sqrt(length);
}

CMyVektor operator+(CMyVektor a, CMyVektor b)
{
	CMyVektor c(a.get_dimension());
	for (int i = 0; i < c.get_dimension(); i++)
	{
		c.set_number(a.get_number(i) + b.get_number(i), i);
	}
	return c;
}

CMyVektor operator*(double lambda, CMyVektor a)
{
	CMyVektor d(a.get_dimension());
	for (int i = 0; i < d.get_dimension(); i++)
	{
		d.set_number(a.get_number(i) * lambda, i);
	}
	return d;
}

CMyVektor operator-(CMyVektor a, CMyVektor b)
{
	CMyVektor differenz(a.get_dimension());
	for (int i = 0; i < a.get_dimension(); i++)
	{
		differenz.set_number(a.get_number(i) - b.get_number(i), i);
	}
	return differenz;
}

CMyVektor operator/(CMyVektor a, double h)
{
	CMyVektor quotient(a.get_dimension());
	for (int i = 0; i < a.get_dimension(); i++)
	{
		quotient.set_number(a.get_number(i) / h, i);
	}
	return quotient;
}

std::ostream& operator<<(std::ostream& os, CMyVektor x)
{
	os << "(";
	int ende = x.get_dimension();
	for (int i = 0; i < x.get_dimension(); i++)
	{
		os << x.get_number(i);
		if (!(i == ende - 1))
		{
			cout << "; ";
		}
	}
	os << ")";

	return os;
}

CMyVektor gradient(CMyVektor x, CMyVektor(*function)(CMyVektor x), int cnt)
{
	const double h = 10e-4;
	const int dim = x.get_dimension();
	CMyVektor temp(dim);
	CMyVektor grad(dim); 
	CMyVektor summe(dim);
	CMyVektor differenz(dim);

	for (int j = 0; j < dim; j++)
	{
		if (j == cnt)
		{
			temp.set_number(x.get_number(j) + h, j);
		}
		else
		{
			temp.set_number(x.get_number(j), j);
		}
	}

	summe = function(temp); //für den Teil links von minus
	differenz = function(x); //für den Teil rechts von minus
	grad = (summe - differenz) / h; //Eintrag von Gradient berechnen DIFFERENZQUOTIENT
	return grad;
}



