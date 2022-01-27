#pragma once

namespace suchbaum
{
    struct BaumKnoten
    {
        BaumKnoten *kKnotenLinks, *kKnotenRechts;
        int wert;
    };
    
    bool suchen(BaumKnoten *&, int);
    void einfuegen(BaumKnoten *&, int);
    void knoten_ausgeben(BaumKnoten *, int);
    void ausgeben(BaumKnoten *);
}