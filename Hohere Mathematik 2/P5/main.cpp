#include<iostream>
#include <iomanip>

#include "CZufall.h"
#include "CLotto.h"

#define CATCH_CONFIG_RUNNER
#include "catch.h"

using namespace std;

int monteCarloSim(CLotto &cl, size_t n, bool zweimalZiehung = false);

int main()
{
	Catch::Session().run();

	cout << "Monte-Carlo-Simulation" << endl << endl;

	CLotto cl(-1);

	vector<int> meineTipps;
	meineTipps.push_back(44);
	meineTipps.push_back(33);
	meineTipps.push_back(11);
	meineTipps.push_back(26);
	meineTipps.push_back(45);
	meineTipps.push_back(49);

	cl.setTippzettel(meineTipps);

	const int EinHunderttausend = 100000;
	const int EineMillionen = 1000000;

	int ergebnis1Hunderttausend = monteCarloSim(cl, EinHunderttausend);
	int ergebnis1Millionen = monteCarloSim(cl, EineMillionen);
	cout << "Ergebnis bei einer Lottoziehung mit einem vorher festgelegtem Tippzettel" << endl;
	cout << "Die Wahrscheinlichkeit fuer " << setw(7) << EinHunderttausend << " bei eine Ziehung mit genau 3 uebereinstimmende Zahlen: " << (ergebnis1Hunderttausend / double(EinHunderttausend)) * 100 << "%" << endl;
	cout << "Die Wahrscheinlichkeit fuer " << setw(7) << EineMillionen << " bei eine Ziehung mit genau 3 uebereinstimmende Zahlen: " << (ergebnis1Millionen / double(EineMillionen)) * 100 << "%" << endl;

	int ergebnis1Hunderttausend2 = monteCarloSim(cl, EinHunderttausend, true);
	int ergebnis1Millionen2 = monteCarloSim(cl, EineMillionen, true);

	cout << "Ergebnis bei einer Lottoziehung mit unterschiedlichen Tippzetteln" << endl;
	cout << "Die Wahrscheinlichkeit fuer " << setw(7) << EinHunderttausend << " bei eine Ziehung mit genau 3 uebereinstimmende Zahlen: " << (ergebnis1Hunderttausend2 / double(EinHunderttausend)) * 100 << "%" << endl;
	cout << "Die Wahrscheinlichkeit fuer " << setw(7) << EineMillionen << " bei eine Ziehung mit genau 3 uebereinstimmende Zahlen: " << (ergebnis1Millionen2 / double(EineMillionen)) * 100 << "%" << endl;

	cin.get();

	cout << endl << endl;
	cout
		<< setw(45) << EinHunderttausend
		<< setw(11) << EineMillionen 
		<< endl;
	cout
		<< left << setw(40) << "mit vorher festgelegtem Tippzettel"
		<< left << setw(10) << (ergebnis1Hunderttausend / double(EinHunderttausend)) * 100
		<< left << setw(10) << (ergebnis1Millionen / double(EineMillionen)) * 100
		<< endl
		<< left << setw(40) << "mit unterschiedlichen Tippzetteln "
		<< left << setw(10) << (ergebnis1Hunderttausend2 / double(EinHunderttausend)) * 100
		<< left << setw(10) << (ergebnis1Millionen2 / double(EineMillionen)) * 100
		<< endl;

	return 0;
}

int monteCarloSim(CLotto& cl, size_t n, bool zweimalZiehung)
{
	int genau3 = 0;
	for (size_t i = 0; i < n; i++)
	{
		int treffer = 0;
		if (zweimalZiehung)
		{
			treffer = cl.zweimalLottoZiehung();
		}
		else
		{
			treffer = cl.lottoZiehung();
		}

		if (3 == treffer)
		{
			genau3++;
		}
	}

	return genau3;
}
