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

	cout << "===================================================" << endl;
	cout
		<< "1) Datensatz einfuegen, manuell" << endl
		<< "2) Datensatz einfuegen, CSV Datei" << endl
		<< "3) Datensatz loeschen" << endl
		<< "4) Suchen" << endl
		<< "5) Ausgabe in Preorder" << endl
		<< "6) Ausgabe in Levelorder" << endl
		<< "7) Minimale ausgabe in Inorder (Nur PosID)" << endl;
	cout << "===================================================" << endl;

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
			if (!cin) //cin.fail
			{
				//falls kein input vom user
				cin.clear(); //reset
				//überspringe
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				//neuen input vom user anfordern
				cout << "Ungueltiges Alter. Alter default zu 0." << endl;
			}


			cout << "Einkommen ?> ";
			cin >> einkommen;
			if (!cin) //cin.fail
			{
				//falls kein input vom user
				cin.clear(); //reset
				//überspringe
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				//neuen input vom user anfordern
				cout << "Ungueltiges Alter. Einkommen default zu 0." << endl;
			}

			cout << "PLZ ?> ";
			cin >> plz;
			if (!cin) //cin.fail
			{
				//falls kein input vom user
				cin.clear(); //reset
				//überspringe
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				//neuen input vom user anfordern
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
			if (!cin) //cin.fail
			{
				//falls kein input vom user
				cin.clear();// reset
				//überspringe
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				//neuen input vom user anfordern
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
		case 6:
			baum.printLevelOrder();
			break;
		case 7:
			baum.printInOrder();
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