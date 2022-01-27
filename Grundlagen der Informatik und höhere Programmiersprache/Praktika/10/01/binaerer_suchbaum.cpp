#include "binaerer_suchbaum.h"
#include <iostream>

bool suchbaum::suchen(BaumKnoten *&BKnoten, int gesuchter_wert)
{
    // Erster Knoten
    if (BKnoten == nullptr) 
    {
        return true;
    }
    else if(gesuchter_wert == BKnoten->wert)
    {
        /* Ist der neue Wert gleich dem Wert im Knoten, so wird der neue
           Wert nicht erneut in den Baum eingefügt (duplikatfreier Baum).
        */
        return true;
    }
    else if(gesuchter_wert < BKnoten->wert)
    {
        /*
         * Ist der neue Wert kleiner dem Wert im Knoten und besitzt der
           Knoten keinen linken Kindknoten, so wird der neue Wert in einen
           neu zu erzeugenden linken Kindknoten eingefügt.
        */
        if(BKnoten->kKnotenLinks != nullptr)
        {
            /*
             * Ist der neue Wert kleiner dem Wert im Knoten und besitzt der
               Knoten einen linken Kindknoten, so wird die Prüfung ab Fall 1. für
               den linken Kindknoten erneut vorgenommen.
             */
            BKnoten = BKnoten->kKnotenLinks;
        }
        else return true;
    }
    else if(gesuchter_wert > BKnoten->wert)
    {
        /*
         * Ist der neue Wert größer dem Wert im Knoten und besitzt der
           Knoten keinen rechten Kindknoten, so wird der neue Wert in einen
           neu zu erzeugenden rechten Kindknoten eingefügt.
         */
        if(BKnoten->kKnotenRechts != nullptr)
        {
            /*
             * Ist der neue Wert größer dem Wert im Knoten und besitzt der
               Knoten einen rechten Kindknoten, so wird die Prüfung ab Fall 1. für
               den rechten Kindknoten erneut vorgenommen.
             */
             BKnoten = BKnoten->kKnotenRechts;
        }
        else return true;
    }
    
    return false;
}

void suchbaum::einfuegen(suchbaum::BaumKnoten *&BKnoten, int naechster_wert)
{
    BaumKnoten * neuer_knoten = new BaumKnoten;
    neuer_knoten->kKnotenLinks = nullptr;
    neuer_knoten->kKnotenRechts = nullptr;
    neuer_knoten->wert = naechster_wert;
    
    BaumKnoten * tmpKnoten = BKnoten;
    
    // Weg des Knoten setzen
    while(not suchen(tmpKnoten, neuer_knoten->wert));
    
    if(BKnoten == nullptr) // Erster Knoten ist die Wurzel des Baumes
    {
        BKnoten = neuer_knoten;
    }
    // Keine duplikaten Werte sind im Ast vorhanden
    else if(neuer_knoten->wert != tmpKnoten->wert)
    {
        // Rechts die größeren Werte
        if(neuer_knoten->wert > tmpKnoten->wert)
        {
            tmpKnoten->kKnotenRechts = neuer_knoten;
        }
        else
        {
            tmpKnoten->kKnotenLinks = neuer_knoten;
        }
    }
    
}

void suchbaum::knoten_ausgeben(BaumKnoten* knoten, int tiefe)
{
    // Wenn Knoten vorhanden, wird Tiefe erhöht
    if(knoten != nullptr)
    {
        // Zuerst werden die rechten Einträge der Knoten ausgegeben - größere Werte
        knoten_ausgeben(knoten->kKnotenRechts, tiefe + 1);

        // Tiefe
        for(int i = 1; i <= tiefe; i++) std::cout << "++";
        
        std::cout << knoten->wert << std::endl;
        
        knoten_ausgeben(knoten->kKnotenLinks, tiefe + 1);
        
        
    }
}

void suchbaum::ausgeben(suchbaum::BaumKnoten * BKnoten)
{
    if (BKnoten == nullptr)
    {
        std::cout << "Leerer Baum." << std::endl;
    }
    else knoten_ausgeben(BKnoten, 0);
}