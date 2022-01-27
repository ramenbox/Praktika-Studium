#include "catch.h"
#include "liste.h"

TEST_CASE("Testfall [1, 2, 3, 4] + liste_loeschen") 
{
    TListenKnoten *anker = nullptr;
    
    
    for (int i = 0; i < 4; i++)
        in_liste_einfuegen(anker, i+1, 9999);
        
    REQUIRE(liste_als_string(anker) == "[ 1 , 2 , 3 , 4 ]");
    liste_loeschen(anker);
    REQUIRE(liste_als_string(anker) == "Leere Liste.");
}

TEST_CASE("Testfall [4, 3, 2, 1]") 
{
    TListenKnoten *anker = nullptr;
    
    
    for (int i = 0; i < 4; i++)
        in_liste_einfuegen(anker, i+1, 9999);
        
    REQUIRE(liste_rueckwaerts_als_string(anker) == "[ 4 , 3 , 2 , 1 ]");
}

TEST_CASE("Testfall [4, 5, 3, 2, 1] -- Hinzufügen [5] vor [3]") 
{
    TListenKnoten *anker = nullptr;
    
    
    for (int i = 0; i < 4; i++)
        in_liste_einfuegen(anker, i+1, 9999);
        
    in_liste_einfuegen(anker, 5, 3);
        
    REQUIRE(liste_rueckwaerts_als_string(anker) == "[ 4 , 3 , 5 , 2 , 1 ]");
}