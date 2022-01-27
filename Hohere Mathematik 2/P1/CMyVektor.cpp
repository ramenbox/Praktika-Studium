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

CMyVektor gradient(CMyVektor x, double (*function)(CMyVektor x))
{
	const double h = 10e-8;
	int dim = x.get_dimension(), cnt = 0;
	CMyVektor e(dim); 
	CMyVektor temp(dim); 
	for (int i = 0; i < dim; i++) 
	{
		double grad = 0, summe = 0, tmp = 0, differenz = 0;
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
		summe = function(temp);
		// Alle Zahlen von x traversieren und nach temp kopieren, also jetzt .... - f(h_1,.....,h_n)
		for (int k = 0; k < dim; k++)
		{
			temp.set_number(x.get_number(k), k);
		}
		differenz = function(temp); 
		grad = (summe - differenz) / h; 
		cnt++; //Variable notwendig um mit h zu "wackeln"
		e.set_number(grad, i); 
	}
	return e;
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

void gradientenverfahren(CMyVektor x, double(*funktion)(CMyVektor x), double lambda)
{
	const double grad_betrags_ende = 1e-5;
	const int schrittende = 25;

	// Schrittsteuerung

	CMyVektor x_neu = x + lambda * gradient(x, funktion);
	double f_von_x = 0.0;
	CMyVektor grad_f_von_x(x.get_dimension());


	int schritte = 0;
	while (schritte < schrittende)
	{

		x_neu = x + lambda * gradient(x, funktion);
		double f_von_x_neu = funktion(x_neu);

		f_von_x = funktion(x);
		grad_f_von_x = gradient(x, funktion);

		if (grad_f_von_x.get_length() < grad_betrags_ende)
		{
			cout << endl << "Ende wegen ||grad f(x)|| < " << grad_betrags_ende << " bei" << endl;
			break;
		}

		cout << "Schritt " << schritte << ":" << endl
			<< "\tx = " << x << endl
			<< "\tlambda = " << lambda << endl
			<< "\tf(x) = " << f_von_x << endl
			<< "\tgrad f(x) = " << grad_f_von_x << endl
			<< "\t||grad f(x)|| = " << grad_f_von_x.get_length() << endl
			<< endl
			<< "\tx_neu = " << x_neu << endl
			<< "\tf(x_neu) = " << f_von_x_neu << endl
			<< endl;

		schritte++;

		if (f_von_x_neu > f_von_x)
		{
			CMyVektor x_test = x + (2 * lambda) * grad_f_von_x;
			double f_von_x_test = funktion(x_test);

			cout << "\tTest mit doppelter Schrittweite (lambda = " << lambda * 2 << "):" << endl
				<< "\tx_test = " << x_test << endl
				<< "\tf(x_test) = " << f_von_x_test << endl;

			if (f_von_x_test > f_von_x_neu)
			{
				cout << "\tverdoppele Schrittweite!" << endl;
				x = x_test;
				lambda *= 2;
			}
			else
			{
				cout << "\tbehalte alte Schrittweite!" << endl;
				x = x_neu;
			}
		}
		else if (f_von_x_neu <= f_von_x)
		{
			do // halbiere solange bis f(xneu) > f(x) ist
			{
				cout << "\thalbiere Schrittweite (lambda = " << lambda / 2 << "):" << endl;
				lambda /= 2;
				x_neu = x + lambda * gradient(x, funktion);
				f_von_x_neu = funktion(x_neu);
				cout << "\tx_neu = " << x_neu << endl
					<< "\tf(x_neu) = " << f_von_x_neu << endl;
			} while (f_von_x_neu <= f_von_x);
			x = x_neu;
		}
	}

	if (schritte >= schrittende)
		cout << endl << "Ende wegen Schrittanzahl = " << schrittende << " bei" << endl;

	cout << "\tx = " << x << endl
		<< "\tlambda = " << lambda << endl
		<< "\tf(x) = " << f_von_x << endl
		<< "\tgrad f(x) = " << grad_f_von_x << endl
		<< "\t||grad f(x)|| = " << grad_f_von_x.get_length() << endl;
}
