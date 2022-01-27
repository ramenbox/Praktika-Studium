#include <iostream>
#include "binaerer_suchbaum.h"

using namespace std;

int main()
{
    suchbaum::BaumKnoten * BKnoten = nullptr;
    
    suchbaum::ausgeben(BKnoten);
    
    int wert;
    do
    {
        cout << "Naechster Wert (99 beendet): ? ";
        cin >> wert;
        // erneut prüfen, sonst wird 99 übernommen
        if(wert != 99) 
        {
            suchbaum::einfuegen(BKnoten, wert);
        }
    } while(wert != 99);
    
    suchbaum::ausgeben(BKnoten);
    
	return 0;
}
