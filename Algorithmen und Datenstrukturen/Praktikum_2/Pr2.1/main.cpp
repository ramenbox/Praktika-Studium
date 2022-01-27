/*************************************************
* ADS Praktikum 2.1
* main.cpp
* 
*************************************************/
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <string>
#include "Ring.h"
#include "catch.hpp"

using namespace std;


int main()
{
	int result = Catch::Session().run();
	
	Ring test;

	cout << "Teste..." << endl;

	for (size_t i = 0; i < 6; i++)
	{
		string info = "Info" + to_string(i);
		string data = "Data" + to_string(i);
		test.addNode(info, data);
	}

	test.print();
	cout << endl;

	for (size_t i = 6; i < 10; i++)
	{
		string info = "Info" + to_string(i);
		string data = "Data" + to_string(i);
		test.addNode(info, data);
	}

	test.print();

	cout << "............................................." << endl;

	
	cout << "OneRingToRuleThemAll v0.1, by Sauron Schmidt" << endl
		<< "====================================" << endl
		<< "1) Backup einfuegen" << endl
		<< "2) Backup suchen" << endl
		<< "3) Alle Backups ausgeben" << endl;
	
	
	Ring backup;
	

	int option = 0;
	do
	{
		cout << "?> ";

		cin >> option;
		cin.ignore();

		string beschreibung = "", daten = "";

		switch (option)
		{
			case 1:
				cout << "+Neuen Datensatz einfuegen" << endl;
				
				cout << "Beschreibung ?> ";
				getline(cin, beschreibung);

				cout << "Daten ?> ";
				cin >> daten;

				backup.addNode(beschreibung, daten);
				cout << "+Ihr Datensatz wurde hinzugefuegt." << endl;
				break;
			case 2:
				cout << "+Nach welchem Daten soll gesucht werden?" << endl;
				cout << "?> ";
				cin >> daten;

				if (!backup.search(daten))
				{
					cout << "+ Datensatz konnte nicht gefunden werden." << endl;
				}
				break;
			case 3:
				backup.print();
				break;
			default:
				option = -1;
				break;
		}
	}
	while (option != -1);

	system("Pause");
	return 0;
}
