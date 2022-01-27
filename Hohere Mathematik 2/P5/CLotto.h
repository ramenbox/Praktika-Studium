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
	// d) eine Methode, die eine Lotto-Ziehung durchf�hrt 
	// und die Anzahl der mit dem Tippzettel
	// �bereinstimmenden Zahlen zur�ckgibt.
	int lottoZiehung();
	// e) eine Methode, die zwei Lotto - Ziehungen durchf�hrt 
	// und die Anzahl der dabei �bereinstimmenden Zahlen zur�ckgibt.
	int zweimalLottoZiehung();

private:
	CZufall cz;
	std::vector<int> tippzettel;
	std::vector<int> ziehung_6_aus_49();
};