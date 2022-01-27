#include <iostream>
#include "C_DGLSolver.h"
using namespace std;

void C_DGLSolver::setDGL_nterOrdnung(double (*f_DGL_nterOrdnung)(CMyVektor y, double x))
{
	this->f_DGL_nterOrdnung = f_DGL_nterOrdnung;
}         

void C_DGLSolver::setDGL_System(CMyVektor(*f_DGL_System)(CMyVektor y, double x))
{
	this->f_DGL_System = f_DGL_System;
}

void C_DGLSolver::setBool(bool x) 
{ 
	this->DGL_System = x; 
}

C_DGLSolver::C_DGLSolver(CMyVektor(*f_DGL_System)(CMyVektor y, double x))
{
	setBool(true);
	setDGL_System(f_DGL_System);
}

C_DGLSolver::C_DGLSolver(double (*f_DGL_nterOrdnung)(CMyVektor y, double x))
{
	setBool(false);
	setDGL_nterOrdnung(f_DGL_nterOrdnung);
}

CMyVektor C_DGLSolver::ableitungen(CMyVektor y, double x)
{
	const int dim = y.getD();
	CMyVektor a(dim);
	if (this->DGL_System)
	{
		a = this->f_DGL_System(y, x);
	}
	else
	{
		/*
		a0=y1;
		a1=y2;
		.....
		an-1=funktion(y,x);
		
		*/
		for (int i = 0; i < dim - 1; i++)
		{
			a.setN(y.getN(i + 1), i);
		}
		a.setN(this->f_DGL_nterOrdnung(y, x), dim - 1);

	}
	return a;
}

void C_DGLSolver::DGL_Euler_Ausgabe(double x_start, double x_ende, const int schritte, CMyVektor y_start)
{

	CMyVektor y(y_start.getD());
	y = y_start;

	CMyVektor ableitung_y(y_start.getD());

	double schrittweite = (x_ende - x_start) / double(schritte);

	cout << "h = " << schrittweite << endl << endl;

	double x = x_start;
	int schrittanzahl = 0;
	for (int i = 0; i < schritte; i++)
	{
		ableitung_y = ableitungen(y, x);

		cout << endl << "Schritt " << schrittanzahl++ << ":" << endl
			<< "\tx = " << x << endl
			<< "\ty = " << y << endl
			<< "\ty' = " << ableitung_y << endl;
		x += schrittweite;
		y = y + schrittweite * ableitung_y;
	}

	cout << endl << endl
		<< "Ende bei" << endl
		<< "\tx = " << x << endl
		<< "\ty = " << y << endl;

}

void C_DGLSolver::DGL_Heun_Ausgabe(double x_start, double x_ende, const int schritte, CMyVektor y_start)
{
	const int dim = y_start.getD();
	CMyVektor y(dim);
	CMyVektor y_test(dim);

	y = y_start;

	CMyVektor ableitung_y_orig(dim);
	CMyVektor ableitung_y_test(dim);
	CMyVektor ableitung_y_mittel(dim);

	double schrittweite = (x_ende - x_start) / double(schritte);

	cout << "h = " << schrittweite << endl << endl;

	double x = x_start;
	int schrittanzahl = 0;
	while(schrittanzahl < schritte)
	{
		ableitung_y_orig = ableitungen(y, x);

		cout << endl << "Schritt " << schrittanzahl++ << ":" << endl
			<< "\tx = " << x << endl
			<< "\ty = " << y << endl
			<< "\ty'_orig = " << ableitung_y_orig << endl;
		
		x += schrittweite;

		// Gehe einen Schritt testweise vor
		y_test = y + schrittweite * ableitung_y_orig;
		ableitung_y_test = ableitungen(y_test, x);

		cout << endl
			<< "\ty_Test = " << y_test << endl
			<< "\ty'_Test = " << ableitung_y_test << endl;

		ableitung_y_mittel = (ableitung_y_orig + ableitung_y_test) / 2;

		cout << endl
			<< "\ty'_Mittel = " << ableitung_y_mittel << endl;
		
		// Übernehme die bessere Approximation
		y = y + schrittweite * ableitung_y_mittel;
	}

	cout << endl << endl
		<< "Ende bei" << endl
		<< "\tx = " << x << endl
		<< "\ty = " << y << endl;


}


CMyVektor C_DGLSolver::DGL_Euler(double x_start, double x_ende, const int schritte, CMyVektor y_start)
{
	CMyVektor y(y_start.getD());
	y = y_start;

	CMyVektor ableitung_y(y_start.getD());

	double schrittweite = (x_ende - x_start) / double(schritte);

	double x = x_start;
	int schrittanzahl = 0;
	for (int i = 0; i < schritte; i++)
	{
		ableitung_y = ableitungen(y, x);
		x += schrittweite;
		y = y + schrittweite * ableitung_y;
	}
	return y;
}

CMyVektor C_DGLSolver::DGL_Heun(double x_start, double x_ende, const int schritte, CMyVektor y_start)
{
	const int dim = y_start.getD();
	CMyVektor y(dim);
	CMyVektor y_test(dim);

	y = y_start;

	CMyVektor ableitung_y_orig(dim);
	CMyVektor ableitung_y_test(dim);
	CMyVektor ableitung_y_mittel(dim);

	double schrittweite = (x_ende - x_start) / double(schritte);


	double x = x_start;
	for (int i = 0; i < schritte; i++)
	{
		ableitung_y_orig = ableitungen(y, x);

		x += schrittweite;

		// Gehe einen Schritt testweise vor
		y_test = y + schrittweite * ableitung_y_orig;
		ableitung_y_test = ableitungen(y_test, x);


		ableitung_y_mittel = (ableitung_y_orig + ableitung_y_test) / 2;


		// Übernehme die bessere Approximation
		y = y + schrittweite * ableitung_y_mittel;
	}

	return y;
}
