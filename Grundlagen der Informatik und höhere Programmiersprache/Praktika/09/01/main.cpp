#define CATCH_CONFIG_RUNNER
#include "catch.h"

#include <iostream>

#include "liste.h"

using namespace std;


int main()
{
    
    //Unit-tests
    if(Catch::Session().run())
    {
        system("PAUSE");
        return 1;
    }
    
    
    const int laenge = 10;
    TListenKnoten *anker = nullptr;
    
    liste_ausgeben(anker);
    
    liste_loeschen(anker);
    
    for (int i = 0; i < laenge; i++)
        in_liste_einfuegen(anker, i*i, 9999);
        
    liste_ausgeben(anker);
    liste_ausgeben_rueckwaerts(anker);
    
    in_liste_einfuegen(anker, 99, 0);
    in_liste_einfuegen(anker, 99, 25);
    in_liste_einfuegen(anker, 99, 81);
    in_liste_einfuegen(anker, 99, 9999);
    in_liste_einfuegen(anker, 6, 25);
    
    liste_ausgeben(anker);
    liste_ausgeben_rueckwaerts(anker);
    
    liste_loeschen(anker);
    
    liste_ausgeben(anker);
    liste_ausgeben_rueckwaerts(anker);
    
    
    //system("PAUSE");
    return 0;
}