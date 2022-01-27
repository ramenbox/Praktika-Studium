#include <iostream>
#include "suchen.h"
#include "funktionen.h"

using namespace std;

int zeichenkette_suchen(const char* text, const char* zkette)
{
    if (cstring_leer(zkette)) return -1; //Der zusuchende Text darf nicht leer sein
    
    unsigned int cmp_cnt = 0, start_pos = 0;
    
    for(unsigned int i = 0; i < cstring_len(text); i++)
    {
        // Vergleich von Text und Zeichenkette
        // Counter zählt nur bei Erfolg
        if(text[i] == zkette[cmp_cnt])
        {
            if(cmp_cnt == 0) start_pos = i;
            cmp_cnt++;
        }
        else
        {
            // Reset Counter
            if (cmp_cnt != cstring_len(zkette))
                cmp_cnt = 0;
            else break;
        }
    }
    
    if (cmp_cnt == cstring_len(zkette))
        return start_pos;
    else return -1;
}