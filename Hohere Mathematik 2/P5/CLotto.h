#pragma once
#include <stdlib.h>
#include <time.h>
#include "CZufall.h"

class CLotto
{
public:
	// n < 0 = time(NULL)
	CLotto(int n);
	void setTippzettel(std::vector<int> tippzettel);
	// d) eine Methode, die eine Lotto-Ziehung durchführt 
	// und die Anzahl der mit dem Tippzettel
	// übereinstimmenden Zahlen zurückgibt.
	int lottoZiehung();
	// e) eine Methode, die zwei Lotto - Ziehungen durchführt 
	// und die Anzahl der dabei übereinstimmenden Zahlen zurückgibt.
	int zweimalLottoZiehung();

private:
	CZufall cz;
	std::vector<int> tippzettel;
	std::vector<int> ziehung_6_aus_49();
};