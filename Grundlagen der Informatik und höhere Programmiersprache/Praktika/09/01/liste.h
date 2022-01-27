#pragma once
#include <string>

struct TListenKnoten // Doppelte verkette Liste
{
    int data;
    TListenKnoten *next;
    TListenKnoten *prev;
};


bool suche_nach_eintrag(TListenKnoten *&ptr, int gesuchterWert);
void in_liste_einfuegen(TListenKnoten *&anker, int wert_neu, int vor_wert);
void hinten_anfuegen(TListenKnoten *&anker, const int wert);
void liste_loeschen(TListenKnoten* &anker);
std::string liste_als_string(TListenKnoten* anker);
std::string liste_rueckwaerts_als_string(TListenKnoten* anker);
void liste_ausgeben(TListenKnoten* anker);
void liste_ausgeben_rueckwaerts (TListenKnoten* anker);