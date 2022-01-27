#pragma once
#include "CMyVektor.h"

class C_DGLSolver 
{
private:
	bool DGL_System; //DGL_System(true) oder DGL höherer Ordnung(false)

	//Funktionspointer
	CMyVektor (*f_DGL_System)(CMyVektor, double);
	double (*f_DGL_nterOrdnung)(CMyVektor, double);

	CMyVektor ableitungen(CMyVektor y, double x);

public:
	void setDGL_nterOrdnung(double (*f_DGL_nterOrdnung)(CMyVektor y, double x));
	void setDGL_System(CMyVektor(*f_DGL_System)(CMyVektor y, double x));
	void setBool(bool x);
	C_DGLSolver(CMyVektor(*f_DGL_System)(CMyVektor y, double x));
	C_DGLSolver(double (*f_DGL_nterOrdnung)(CMyVektor y, double x));

	void DGL_Euler_Ausgabe(double x_start, double x_ende, const int schritte, CMyVektor y_start);
	void DGL_Heun_Ausgabe(double x_start, double x_ende, const int schritte, CMyVektor y_start);

	CMyVektor DGL_Euler(double x_start, double x_ende, const int schritte, CMyVektor y_start);
	CMyVektor DGL_Heun(double x_start, double x_ende, const int schritte, CMyVektor y_start);
};
