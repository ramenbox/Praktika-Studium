#include "CLotto.h"

CLotto::CLotto(int n)
{
	if (n < 0)
	{
		cz.initialisiere(time(NULL));
	}
	else
	{
		cz.initialisiere(n);
	}
}

void CLotto::setTippzettel(std::vector<int> tippzettel)
{
	this->tippzettel = tippzettel;
}

int CLotto::lottoZiehung()
{
	int treffer = 0;

	std::vector<int> ziehung = ziehung_6_aus_49();

	// Vergleiche Ziehung mit dem Tippzettel
	for (auto lottoZahl: ziehung)
	{
		if (std::find(tippzettel.begin(), tippzettel.end(), lottoZahl) != tippzettel.end())
		{
			treffer++;
		}
	}
	// Anzahl von Treffern
	return treffer;
}

int CLotto::zweimalLottoZiehung()
{
	int treffer = 0;

	std::vector<int> ziehung1 = ziehung_6_aus_49();
	std::vector<int> ziehung2 = ziehung_6_aus_49();

	for (auto lottoZahl : ziehung1)
	{
		if (std::find(ziehung2.begin(), ziehung2.end(), lottoZahl) != ziehung2.end())
		{
			treffer++;
		}
	}

	// Anzahl von Treffern
	return treffer;
}

std::vector<int> CLotto::ziehung_6_aus_49()
{
	std::vector<int> ziehung;

	for(size_t i = 0; i < 6; i++)
	{
		int zufallsZahl = cz.wert(1, 49);
		if (std::find(ziehung.begin(), ziehung.end(), zufallsZahl) != ziehung.end())
		{
			i -= 1;
			continue;
		}
		else
		{
			ziehung.push_back(zufallsZahl);
		}
	}
	return ziehung;
}
