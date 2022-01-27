#include <iostream>
#include "CMyMatrix.h"
using namespace std;

CMyMatrix::CMyMatrix(int dim1, int dim2) : zeile(dim1), spalte(dim2) {
	werte = new double*[dim1];
	for (int i = 0; i < dim1; i++)
	{
		werte[i] = new double[dim2];
	}
}

ostream& operator<<(ostream& os, CMyMatrix x)
{
	int ende = x.getspalte();
	os << endl << '\t';
	for (int j = 0; j < x.getzeile(); j++)
	{
		for (int i = 0; i < x.getspalte(); i++)
		{
			if (i == 0)
				cout << "\t|";

			os << x.getnum(j, i);
			
			if (!(i == ende - 1))
				cout << "; ";

			if (i == ende - 1)
				cout << "|" << endl << '\t';
		}
	}
	return os;
}

CMyVektor operator*(CMyMatrix A, CMyVektor x)
{
	CMyVektor produkt(A.getzeile());
	double summe = 0;
	for (int i = 0; i < A.getzeile(); i++)
	{
		for (int j = 0; j < A.getspalte(); j++)
		{
			summe += A.getnum(i, j) * x.get_number(j);
		}
		produkt.set_number(summe, i);
		summe = 0;
	}
	return produkt;
}

CMyMatrix CMyMatrix::invers()
{
	if (this->getzeile() == 2 && this->getspalte() == 2)
	{
		double det;
		det = this->getnum(0, 0) * this->getnum(1, 1) - this->getnum(1, 0) * this->getnum(0, 1);
		if (det != 0)
		{
			CMyMatrix a(2, 2);
			double zahl = this->getnum(1, 1) / det;
			a.setnum(this->getnum(1, 1) / det, 0, 0);
			a.setnum(-(this->getnum(0, 1)) / det, 0, 1);
			a.setnum(-(this->getnum(1, 0)) / det, 1, 0);
			a.setnum(this->getnum(0, 0) / det, 1, 1);
			return a;
		}
		else
		{
			cout << "Det = 0. Inverse ist nicht mit der Regel von Sarrus zu bilden!" << endl;
		}
	}

	cout << "Keine Inverse machbar!" << endl;
	return *this;
}

CMyMatrix jacobi(CMyVektor x, CMyVektor (*funktion)(CMyVektor x))
{
	CMyVektor f(x.get_dimension()); // Gradient reinpacken
	CMyMatrix j(funktion(x).get_dimension(), x.get_dimension());

	for (int i = 0; i < j.getspalte(); i++)
	{
		f = gradient(x, funktion, i);
		for (int k = 0; k < j.getzeile(); k++)
		{
			j.setnum(f.get_number(k), k, i);
		}
	}
	return j;
}

void newtonverfahren(CMyVektor x, CMyVektor(*funktion)(CMyVektor x))
{
	const double max = 10e-5;
	const int schrittende = 50;

	int schritte = 0;
	while (schritte < schrittende)
	{
		CMyVektor f_von_x = funktion(x);
		CMyMatrix j(f_von_x.get_dimension(), x.get_dimension());
		CMyMatrix j_von_x = jacobi(x, funktion);
		CMyVektor delta_x = j_von_x.invers() * (-1 * f_von_x);

		if (f_von_x.get_length() < max)
		{
			cout << endl << "Ende wegen ||f(x)||<1e-5 bei " << endl
				<< "\tx = " << x << endl
				<< "\tf(x) = " << funktion(x) << endl
				<< "\t||f(x)|| = " << funktion(x).get_length() << endl;
			return;
		}

		cout << endl << "Schritt " << schritte << ":" << endl
			<< "\tx = " << x << endl
			<< "\tf(x) = " << f_von_x << endl
			<< "\tf'(x) = " << j_von_x
			<< "(f'(x))^(-1)) = " << j_von_x.invers()
			<< "dx = " << delta_x << endl
			<< "\t||f(x)|| = " << f_von_x.get_length() << endl;

		x = x + delta_x;
		schritte++;
	}
	cout << endl << "Ende wegen Schrittanzahl = 50 bei" << endl
		<< "\tx = " << x << endl
		<< "\tf(x) = " << funktion(x) << endl
		<< "\t||f(x)|| = " << funktion(x).get_length() << endl;
}

