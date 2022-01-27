#include <iostream>
#include "CMyMatrix.h"
#include "CMyVektor.h"
using namespace std;

CMyVektor f(CMyVektor x_vektor)
{
	CMyVektor z(3);
	double x1 = x_vektor.get_number(0),
		x2 = x_vektor.get_number(1),
		x3 = x_vektor.get_number(2),
		x4 = x_vektor.get_number(3);
	
	z.set_number(x1 * x2 * exp(x3), 0);
	z.set_number(x2 * x3 * x4, 1);
	z.set_number(x4, 2);
	return z;
}

CMyVektor g(CMyVektor x_vector)
{
	CMyVektor z(2);
	double x = x_vector.get_number(0),
		y = x_vector.get_number(1);

	z.set_number(x * x * x * y * y * y - 2 * y, 0);
	z.set_number(x - 2, 1);
	return z;
}

int main()
{
	CMyMatrix test1(3, 4);
	int cnt = 0;
	for (int i = 0; i < test1.getzeile(); i++) {
		for (int j = 0; j < test1.getspalte(); j++) {
			test1.setnum(cnt, i, j);
			cnt++;
		}
	}
	cout << test1 << endl;

	CMyMatrix test2(2, 2);
	test2.setnum(3, 0, 0);
	test2.setnum(2, 0, 1);
	test2.setnum(2, 1, 0);
	test2.setnum(-3, 1, 1);

	CMyMatrix inverse(2, 2);
	inverse = test2.invers();
	cout << inverse << endl;

	CMyVektor test3(2);
	test3.set_number(1, 0);
	test3.set_number(5, 1);
	cout << test3 << endl << endl;

	CMyVektor test4(2);
	test4 = test2 * test3;
	cout << test4 << endl;

	CMyVektor test5(4);
	test5.set_number(1, 0);
	test5.set_number(2, 1);
	test5.set_number(0, 2);
	test5.set_number(3, 3);
	cout << "Jacobi-Matrix zu test3: ";
	cout << jacobi(test5, *f) << endl;
	
	CMyVektor start_vektor(2);
	start_vektor.set_number(1, 0);
	start_vektor.set_number(1, 1);

	newtonverfahren(start_vektor, *g);

	return 0;
}