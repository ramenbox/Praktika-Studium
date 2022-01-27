#include "CZufall.h"

int CZufall::wert(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

void CZufall::initialisiere(int n)
{
	// n ist der Seed
	srand(n);
}

std::vector<int> CZufall::test(int a, int b, int N)
{
	//GIP Klausuraufgabe damals :)
	std::vector<int> haeufigkeiten(b+1, 0);
	int zufallszahl;
	for (size_t i = 0; i < N; i++)
	{
		zufallszahl = wert(a, b);
		haeufigkeiten[zufallszahl]++;
	}
	return haeufigkeiten;
}

std::vector<int> CZufall::test_falsch(int a, int b, int N)
{
	// Weil wir vor jeder einzelnen Ziehung srand(time(NULL)) init.
	// bedeutet es, dass wir die gleichen "Zufallszahlen" bekommen werden,
	// da die Zeit ist geringm‰ﬂig ver‰ndert wegen der CPU.
	std::vector<int> haeufigkeiten(b+1, 0);
	int zufallszahl;
	for (size_t i = 0; i < N; i++)
	{
		initialisiere(time(NULL));
		zufallszahl = wert(a, b);
		haeufigkeiten[zufallszahl]++;
	}
	return haeufigkeiten;
}
