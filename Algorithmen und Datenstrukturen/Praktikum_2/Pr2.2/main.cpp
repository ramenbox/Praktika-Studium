/*************************************************
* ADS Praktikum 2.2
* main.cpp
*
*************************************************/
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "Tree.h"
#include "catch.h"


#include <fstream>

using namespace std;

struct Person
{
	string name;
	string alter;	  // int
	string einkommen; // double
	string plz;		  // int
};

istream& lese_ein(istream& in, Person& p)
{
	getline(in, p.name, ';');
	getline(in, p.alter, ';');
	getline(in, p.einkommen, ';');
	getline(in, p.plz);

	return in;
}

int main() {

	int result = Catch::Session().run();

	Tree testBaum;
	
	cout << "Teste preorder Ausgabe des BT..." << endl;
	for (size_t i = 0; i < 150; i += 10)
	{
		testBaum.addNode("Test"+to_string(i), i, 11, 2+i);
	}
	for (size_t i = 20; i > 0; i--)
	{
		testBaum.addNode("Test-" + to_string(i), i, i+1, 20 - i);
	}
	testBaum.printAll();
	cout << endl << endl << endl;
	
	cout << "===================================================" << endl;
	cout << "Person Analyzer v19.84, by George Orwell" << endl
		<< "1) Datensatz einfuegen, manuell" << endl
		<< "2) Datensatz einfuegen, CSV Datei" << endl
		<< "3) Datensatz loeschen" << endl
		<< "4) Suchen" << endl
		<< "5) Datenstruktur anzeigen" << endl;
	
	Tree baum;
	
	int option = 0;
	do
	{
		cout << "?>";
		cin >> option;

		string name = "";
		int alter = 0;
		int plz = 0;
		int posID = 0;
		double einkommen = 0.0;
		
		char yes_no = 'n';
		switch (option)
		{
			case 1:
				cout << "+ Bitte geben Sie die den Datensatz ein" << endl;
				
				cout << "Name ?> ";
				cin >> name;
				
				cout << "Alter ?> ";
				cin >> alter;
				// Prüfe ob cin den erwarteten Input bekommt
				if (!cin) // or if(cin.fail())
				{
					// user didn't input a number
					cin.clear(); // reset failbit
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
					// next, request user reinput
					cout << "Ungueltiges Alter. Alter default zu 0." << endl;
				}
				

				cout << "Einkommen ?> ";
				cin >> einkommen;
				if (!cin) // or if(cin.fail())
				{
					// user didn't input a number
					cin.clear(); // reset failbit
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
					// next, request user reinput
					cout << "Ungueltiges Alter. Einkommen default zu 0." << endl;
				}

				cout << "PLZ ?> ";
				cin >> plz;
				if (!cin) // or if(cin.fail())
				{
					// user didn't input a number
					cin.clear(); // reset failbit
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
					// next, request user reinput
					cout << "Ungueltiges Alter. PLZ default zu 0." << endl;
				}

				baum.addNode(name, alter, einkommen, plz);
				cout << "+ Ihr Datensatz wurde eingefuegt" << endl;
				break;
			case 2:
				cout << "+ Moechten Sie die Daten aus Datei \"ExportZielanalyse.csv\" importieren (j/n) ?>";
				cin >> yes_no;
				if (yes_no == 'j')
				{
					ifstream csvfile("ExportZielanalyse.csv");
					if (!csvfile.is_open())
					{
						cout << "Fehler beim Oeffnen der Datei!" << endl;
					}
					else
					{
						for (Person person; lese_ein(csvfile, person);)
						{
							// Einfügen eines Datensatz nach dem Entnehmen
							baum.addNode(
								person.name,
								atoi(person.alter.c_str()),
								atof(person.einkommen.c_str()),
								atoi(person.plz.c_str())
							);
						}
						cout << "+ Daten wurden dem Baum hinzugefuegt." << endl;
					}
					
					
				}
				else
				{
					cout << "+ Moechten Sie vielleicht die Daten aus Datei \"ExportZielanalyse_Fall2.csv\" importieren (j/n) ?>";
					cin >> yes_no;
					if (yes_no)
					{
						ifstream csvfile2("ExportZielanalyse_Fall2.csv");

						if (!csvfile2.is_open())
						{
							cout << "Fehler beim Oeffnen der Datei!" << endl;
						}
						else
						{
							for (Person person; lese_ein(csvfile2, person);)
							{
								// Einfügen eines Datensatz nach dem Entnehmen
								baum.addNode(
									person.name,
									atoi(person.alter.c_str()),
									atof(person.einkommen.c_str()),
									atoi(person.plz.c_str())
								);
								
							}

							cout << "+ Daten wurden dem Baum hinzugefuegt." << endl;
						}

					}
				}
				

				break;
			case 3:
				cout << "+ Bitte geben Sie den zu loeschenden Datensatz an" << endl;
				
				cout << "PosID ?> ";
				cin >> posID;
				if (!cin) // or if(cin.fail())
				{
					// user didn't input a number
					cin.clear(); // reset failbit
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
					// next, request user reinput
					cout << "Ungueltige PosID!" << endl;
				}
				else
				{

					cout << "+ Datensatz wurde geloescht.";
					baum.deleteNode(posID);
					cout << endl;
				}
				
				break;
			case 4:
				cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;
				
				cout << "Name ?> ";
				cin >> name;

				if (!baum.searchNode(name))
				{
					cout << "+ Datensatz konnte nicht ermittelt werden." << endl;
				}
				break;
			case 5:
				baum.printAll();
				break;
			default:
				cout << "Ungueltige Eingabe! Exit menu." << endl;
				option = -1;
				break;
		}
	} while (option != -1);
	
	system("PAUSE");

	return 0;
}
