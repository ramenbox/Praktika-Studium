#pragma once
#include "CMyVektor.h"
class CMyMatrix
{
private:
	int zeile, spalte;
	double** werte;

public:
	CMyMatrix(int, int);

	int getzeile() const { return zeile; }

	int getspalte() const { return spalte; }

	double getnum(int zeile, int spalte) const { return werte[zeile][spalte]; }

	void setnum(double zahl, int zeile, int spalte) { werte[zeile][spalte] = zahl; }
	
	CMyMatrix invers();
};

CMyVektor operator*(CMyMatrix A, CMyVektor x);

std::ostream& operator<<(std::ostream& os, CMyMatrix x);

CMyMatrix jacobi(CMyVektor x, CMyVektor (*function)(CMyVektor x));

void newtonverfahren(CMyVektor x, CMyVektor (*funktion)(CMyVektor x));