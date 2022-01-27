#define CATCH_CONFIG_RUNNER
#include "catch.h"

#include <iostream>
using namespace std;

#include "suchen.h"
#include "funktionen.h"

int main()
{
    //Unit-tests
    if(Catch::Session().run())
    {
        system("PAUSE");
        return 1;
    }
    
    
    const int len = 21; // Maximal 20 Zeichen vom Benutzer
                        // Nullcharacter miteinberechnet
    char text[len];
    char zeichenkette[len];

    cout << "Bitte geben Sie den Text ein: ";
    cstring_einlesen(text, true); // Der Text darf leer sein
    
    
    cout << "Bitte geben Sie die zu suchende Zeichenkette ein: ";
    cstring_einlesen(zeichenkette);
    
    // Gibt die Position der ersten gefundenen Zeichenkette
    int start_position = zeichenkette_suchen(text, zeichenkette);
    
    if(start_position != -1)
    {
        cout << "Die Zeichenkette '";
        cstring_ausgeben(zeichenkette);
        cout << "' ist in dem Text '";
        cstring_ausgeben(text);
        cout << "' enthalten." << endl;
        
        cout << "Sie startet ab Zeichen " << start_position << " (bei Zaehlung ab 0)." << endl;
    }
    else
    {
        cout << "Die Zeichenkette '";
        cstring_ausgeben(zeichenkette);
        cout << "' ist NICHT in dem Text '";
        cstring_ausgeben(text);
        cout << "' enthalten." << endl;
    }

    // Windows Gast
	system("PAUSE");
	return 0;
}