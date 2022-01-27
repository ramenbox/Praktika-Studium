#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>

class CZufall
{
public:
	// Liefere eine (ungefähr) gleichverteilte Zufallszahl a <= n <= b
	int wert(int a, int b);
	// Init. Zufallsgenerator
	void initialisiere(int n);
	// Es wird N mal eine Zufallszahl zwischen a und b zieht und ermittelt,
	// wie oft dabei die Werte a, a + 1, ..., b auftreten,
	// und diese Häufigkeiten als Vektor ausgibt.
	std::vector<int> test(int a, int b, int N);
	// Vor jeder einzelnen Ziehung mit initialisiere(time(NULL))
	// den Zufallsgenerator neu init.
	std::vector <int> test_falsch(int a, int b, int N);
private:
};