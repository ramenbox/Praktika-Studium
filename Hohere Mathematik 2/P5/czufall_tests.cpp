#include <vector>

#include "catch.h"
#include "CZufall.h"

bool in_range(int low, int high, std::vector<int> v)
{
	for (auto x: v)
	{
		if (!(x >= low && x <= high)) return false;
	}
	return true;
}

bool is_heavy(std::vector<int> v, int weight)
{
	for (auto x: v)
	{
		if (x == weight) return true;
	}
	return false;
}

TEST_CASE("Teste CZufall") 
{

    SECTION("100 Zufallswerte von 1 bis 10") 
	{
		const int n = 100;
		CZufall cz;
		cz.initialisiere(0);

		std::vector<int> zWerte;

		for (size_t i = 0; i < n; i++)
		{
			zWerte.push_back(cz.wert(1, 10));
		}

		REQUIRE(in_range(1, 10, zWerte) == true);
    }

	SECTION("1000 Zufallswerte von 30 bis 66") 
	{
		const int n = 100;
		CZufall cz;
		cz.initialisiere(2);

		std::vector<int> zWerte;

		for (size_t i = 0; i < n; i++)
		{
			zWerte.push_back(cz.wert(30, 66));
		}

		REQUIRE(in_range(30, 66, zWerte) == true);
	}

	SECTION("Teste Haeufigkeitmethode test(3, 7, 1000)") 
	{
		CZufall cz;
		cz.initialisiere(1);

		std::vector<int> haeufigkeiten = cz.test(3, 7, 1000);
		std::vector<int> haeufigkeitenSeed1;
		haeufigkeitenSeed1.push_back(0);
		haeufigkeitenSeed1.push_back(0);
		haeufigkeitenSeed1.push_back(0);
		haeufigkeitenSeed1.push_back(205);
		haeufigkeitenSeed1.push_back(190);
		haeufigkeitenSeed1.push_back(190);
		haeufigkeitenSeed1.push_back(225);
		haeufigkeitenSeed1.push_back(190);

		REQUIRE(haeufigkeiten == haeufigkeitenSeed1);
		
	}

	SECTION("Teste Haeufigkeitmethode mit verschiedenen Seeds test(3, 7, 1000)")
	{
		CZufall cz;
		cz.initialisiere(1);

		std::vector<int> haeufigkeiten = cz.test(3, 7, 1000);
		std::vector<int> haeufigkeitenSeed1;
		haeufigkeitenSeed1.push_back(0);
		haeufigkeitenSeed1.push_back(0);
		haeufigkeitenSeed1.push_back(0);
		haeufigkeitenSeed1.push_back(205);
		haeufigkeitenSeed1.push_back(190);
		haeufigkeitenSeed1.push_back(190);
		haeufigkeitenSeed1.push_back(225);
		haeufigkeitenSeed1.push_back(190);

		REQUIRE(haeufigkeiten == haeufigkeitenSeed1);

		cz.initialisiere(2);
		std::vector<int> haeufigkeiten2 = cz.test(3, 7, 1000);

		REQUIRE(haeufigkeiten2 != haeufigkeitenSeed1);

		cz.initialisiere(2);
		std::vector<int> haeufigkeiten3 = cz.test(3, 7, 1000);

		REQUIRE(haeufigkeiten3 != haeufigkeitenSeed1);

	}


	SECTION("Teste Haeufigkeitmethode test_falsch(3, 7, 1000)")
	{
		CZufall cz;

		std::vector<int> haeufigkeiten = cz.test_falsch(3, 7, 1000);

		REQUIRE(is_heavy(haeufigkeiten, 1000) == true);

	}
}
