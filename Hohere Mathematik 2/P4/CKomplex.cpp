#include "CKomplex.h"
#include <math.h>
using namespace std;

CKomplex::CKomplex()
{
	Re = 0;
	Im = 0;
}

CKomplex::CKomplex(double a, double b)
{
	Re = a;
	Im = b;
}

CKomplex::CKomplex(double phi)
{
	Re = cos(phi);
	Im = sin(phi);
}

void CKomplex::operator+= (const CKomplex& a) 
{
	(*this) = (*this) + a;
}

void CKomplex::operator*= (const double& a) 
{
	(*this) = (*this) * CKomplex(a, 0);
}

CKomplex operator+ (const CKomplex& a, const CKomplex& b) 
{
	return CKomplex(a.Re + b.Re, a.Im + b.Im);
}

CKomplex operator* (const CKomplex& a, const CKomplex& b) 
{
	return CKomplex(a.Re * b.Re - a.Im * b.Im,  //Re
		a.Re * b.Im + a.Im * b.Re); //Im
}

double CKomplex::abs(void)
{
	return sqrt((Re * Re) + (Im * Im));
}
