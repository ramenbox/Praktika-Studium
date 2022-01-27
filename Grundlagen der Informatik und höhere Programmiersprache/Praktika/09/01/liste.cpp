#include "liste.h"

#include <iostream>
using namespace std;

bool suche_nach_eintrag(TListenKnoten *&ptr, int gesuchterWert)
{
    while (ptr->next != nullptr)
    {
        if(ptr->data == gesuchterWert)
        {
            return true;
        }
        else ptr = ptr->next;
    }
    
    // Wenn man als gesuchten Wert den letzten Wert der Liste angibt,
    // wird die Überprüfung beim durchgehen der Liste übersprungen (da der Nullpointer erreicht worden ist) und
    // gibt als Rückgabewert false.
    // Somit muss man auch nach dem Traversieren der Liste den Wert des Eintrages überprüfen.
    if(ptr->data == gesuchterWert)
    {
        return true;
    }
    else return false;
}

void in_liste_einfuegen(TListenKnoten *&anker, int wert_neu, int vor_wert)
{
    // Neuer Eintrag
    TListenKnoten *neuer_eintrag = new TListenKnoten;
    neuer_eintrag->data = wert_neu;
    neuer_eintrag->next = nullptr;
    neuer_eintrag->prev = nullptr;
    
    
    if (anker == nullptr)
        anker = neuer_eintrag;
    else
    {
        // Anker könnte verschoben worden sein, nach einem neuem Knoten vor den vorherigen ersten Knoten.
        if(anker->prev != nullptr)
            anker = anker->prev;
        
        TListenKnoten *ptr = anker;
        if(suche_nach_eintrag(ptr, vor_wert))
        {
            // Prüfe ob es sich um den ersten Eintrag handelt
            if (ptr->prev != nullptr)
            {
                // Setze zuerst die Vor- und Nachzeiger des neuen Eintrages
                neuer_eintrag->next = ptr;
                neuer_eintrag->prev = ptr->prev;
                
                // Dann setze den Nachzeiger des Eintrages vor dem neuem Eintrag
                ptr->prev->next = neuer_eintrag;
                
                // Vorzeiger des nächstem Eintrag nach dem neuem Eintrag wird gesetzt.
                ptr->prev = neuer_eintrag;
            }
            else
            {
                // Fügt den neuen Eintrag vor dem vorherigem erstem Eintrag
                neuer_eintrag->next = ptr;
                ptr->prev = neuer_eintrag;
            }
        }
        else
        {
            // Fügt neuen Eintrag am Ende der Liste hinzu
            ptr->next = neuer_eintrag;
            neuer_eintrag->prev = ptr;
            // neuer_eintrag->prev ist schon bei der Initialisierung auf nullptr gestellt
        }

    }
}


void hinten_anfuegen(TListenKnoten *&anker, const int wert)
{
    // Neuer Eintrag
    TListenKnoten *neuer_eintrag = new TListenKnoten;
    neuer_eintrag->data = wert;
    neuer_eintrag->next = nullptr;
    neuer_eintrag->prev = nullptr;
    
    if (anker == nullptr)
        anker = neuer_eintrag;
    else
    {
        TListenKnoten *ptr = anker;
        while (ptr->next != nullptr)
            ptr = ptr->next;
        ptr->next = neuer_eintrag;
        
        // Setze den Vorzeiger zum vorherigen Eintrag
        neuer_eintrag->prev = ptr;
    }
}

void liste_loeschen(TListenKnoten* &anker)
{
    
    if (anker != nullptr)
    {
        // Anker ist verschoben, wenn ein neuer erster Eintrag hinzugefügt ist.
        // Fügt man vor dem erstem Eintrag einen neuen hinzu, so muss der Anker
        // dem hinzugefügtem Eintrag folgen.
        if(anker->prev != nullptr)
            anker = anker->prev;
            
        TListenKnoten *ptr = anker;
        
        // Traversiert den Nachzeiger bis zum Ende (links nach rechts)
        while(anker->next != nullptr)
        {
            // Der temporärer Zeiger wird genutzt,
            // um die Referenzen zu den Knoten zu speichern,
            // damit sie nicht beim Löschen verloren gehen.
            ptr = anker->next;
            anker->next = ptr->next;
            
            // Alle Knoten werden von links nach rechts gelöscht
            delete ptr;
        }
        anker = nullptr;
        
    }
}

string liste_als_string(TListenKnoten * anker)
{
    string resultat = "";
    if (anker == nullptr)
        return "Leere Liste.";
    else
    {
        resultat += "[ ";
        
        // Temp. Zeiger zum Anker, sonst wird der Anker verschoben
        TListenKnoten *ptr = anker;
        
        // Anker ist verschoben, wenn ein neuer erster Eintrag hinzugefügt ist.
        // Da man nach rechts traversiert
        if(ptr->prev != nullptr)
            ptr = ptr->prev;
        
        do
        {
            resultat += std::to_string(ptr->data);
            if (ptr->next != nullptr) 
                resultat += " , ";
            else 
                resultat += " ";
            
            ptr = ptr->next;
        } while (ptr != nullptr); // Traversiere die Knoten nach rechts
    
    resultat += "]";
    }
    return resultat;
}

string liste_rueckwaerts_als_string(TListenKnoten * anker)
{
    string resultat = "";
    if (anker == nullptr)
        return "Leere Liste.";
    else
    {
        resultat += "[ ";
        TListenKnoten *ptr = anker;
        
        // Traversiere die Liste bis zum letzten Eintrag
        while(ptr->next != nullptr)
            ptr = ptr->next;
        
        // Traversiere vom letztem Eintrag bis zum erstem
        do
        {
            resultat += std::to_string(ptr->data);
            
            if (ptr->prev != nullptr) 
                resultat += " , ";
            else 
                resultat += " ";
            
            ptr = ptr->prev; // Statt vorwärts (ptr->next)
        } while (ptr != nullptr);
    
    resultat += "]";
    }
    return resultat;
}

void liste_ausgeben(TListenKnoten * anker)
{
    cout << liste_als_string(anker) << endl;
}

void liste_ausgeben_rueckwaerts (TListenKnoten* anker)
{
    cout << liste_rueckwaerts_als_string(anker) << endl;
}
