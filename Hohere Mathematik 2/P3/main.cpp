#include <iostream>
#include "C_DGLSolver.h"
#include "CMyVektor.h"
using namespace std;

CMyVektor DGL_System(CMyVektor y_vector, double x)
{
	CMyVektor z(y_vector.getD());
	double y1 = y_vector.getN(0),
		y2 = y_vector.getN(1);

	z.setN(2 * y2 - x * y1, 0);
	z.setN(y1 * y2 - 2 * x * x * x, 1);
	return z;
}

double DGL_nterOrdnung(CMyVektor y_vector, double x)
{

	//y′′′ = 2xy′y′′ + 2y2y′
	double y0 = y_vector.getN(0),
		y1 = y_vector.getN(1),
		y2 = y_vector.getN(2);
	return 2 * x * y1 * y2 + 2 * pow(y0, 2) * y1;
}

int main()
{
	CMyVektor y(2);
	y.setN(0, 0);
	y.setN(1, 1);

	C_DGLSolver solver(DGL_System);

	//solver.DGL_Euler_Ausgabe(0, 2, 100, y);

	//solver.DGL_Heun_Ausgabe(0, 2, 100, y);

	CMyVektor y1(3);
	y1.setN(1, 0);
	y1.setN(-1, 1);
	y1.setN(2, 2);

	CMyVektor eulerR(3);

	C_DGLSolver solverNOrd(DGL_nterOrdnung);
	int schritte = 10;
	
	cout << "Abweichung bei Euler bei " << schritte << " Schritten: " << (solverNOrd.DGL_Euler(1.0, 2.0, schritte, y1).getN(0) - 0.5) << endl;
	cout << "Abweichung bei Heun bei " << schritte << " Schritten: " << (solverNOrd.DGL_Heun(1.0, 2.0, schritte, y1).getN(0) - 0.5) << endl;

	cout << "Abweichung bei Euler bei " << pow(schritte, 2) << " Schritten: " << (solverNOrd.DGL_Euler(1.0, 2.0, pow(schritte, 2), y1).getN(0) - 0.5) << endl;
	cout << "Abweichung bei Heun bei " << pow(schritte, 2) << " Schritten: " << (solverNOrd.DGL_Heun(1.0, 2.0, pow(schritte, 2), y1).getN(0) - 0.5) << endl;

	cout << "Abweichung bei Euler bei " << pow(schritte, 3) << " Schritten: " << (solverNOrd.DGL_Euler(1.0, 2.0, pow(schritte, 3), y1).getN(0) - 0.5) << endl;
	cout << "Abweichung bei Heun bei " << pow(schritte, 3) << " Schritten: " << (solverNOrd.DGL_Heun(1.0, 2.0, pow(schritte, 3), y1).getN(0) - 0.5) << endl;

	cout << "Abweichung bei Euler bei " << pow(schritte, 4) << " Schritten: " << (solverNOrd.DGL_Euler(1.0, 2.0, pow(schritte, 4), y1).getN(0) - 0.5) << endl;
	cout << "Abweichung bei Heun bei " << pow(schritte, 4) << " Schritten: " << (solverNOrd.DGL_Heun(1.0, 2.0, pow(schritte, 4), y1).getN(0) - 0.5) << endl;
	
	

	return 0;
}