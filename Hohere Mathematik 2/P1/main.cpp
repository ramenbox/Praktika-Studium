#include <iostream>
#include "CMyVektor.h"
using namespace std;

double f(CMyVektor x_vektor)
{
	double x = x_vektor.get_number(0),
		y = x_vektor.get_number(1);

	return sin(x * y) + sin(x) + cos(y);
}

double g(CMyVektor x_vektor)
{
	double x1 = x_vektor.get_number(0),
		x2 = x_vektor.get_number(1),
		x3 = x_vektor.get_number(2);

	return -(2 * x1 * x1 - 2 * x1 * x2 + x2 * x2 + x3 * x3 - 2 * x1 - 4 * x3);
}

int main()
{
	CMyVektor a(3);
	CMyVektor b(3);
	CMyVektor test1(3);

	a.set_number(0.997155, 0);
	a.set_number(0.973400, 1);
	a.set_number(1.999917, 2);

	test1 = gradient(a, *g);

	b.set_number(0, 0);
	b.set_number(2.5, 1);
	b.set_number(9.2, 2);

	cout << "Matrix a ist: (" << a.get_number(0) << ", " << a.get_number(1) << ", " << a.get_number(2) << ")" << endl;
	cout << "Matrix b ist: (" << b.get_number(0) << ", " << b.get_number(1) << ", " << b.get_number(2) << ")" << endl;
	cout << "Gradient ist: (" << test1.get_number(0) << ", " << test1.get_number(1) << ", " << test1.get_number(2) << ")" << endl;

	CMyVektor c = a + b;
	cout << "Die Summe von a + b lautet : (" << c.get_number(0) << ", " << c.get_number(1) << ", " << c.get_number(2) << ")" << endl;

	double lambda = 0.1;
	CMyVektor test2(2);
	test2.set_number(-0.748589, 0);
	test2.set_number(0.710286, 1);
	cout << test2 << endl;
	cout << gradient(test2, *f) << endl;

	cout << endl << endl << endl;
	// Funktion von f(x,y)
	CMyVektor test3(3);
	test3.set_number(0.000000, 0);
	test3.set_number(0.000000, 1);
	test3.set_number(0.000000, 2);

	gradientenverfahren(test3, *g, 0.1);

	return 0;
}
