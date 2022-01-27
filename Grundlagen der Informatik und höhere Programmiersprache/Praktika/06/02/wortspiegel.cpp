#include "wortspiegel.h"


void myreverse(string &text, unsigned int b, unsigned int e)
{
    char tmp;
    for(; b <= e; b++, e--) // Anfangsposition und Endposition bewegt sich zur Mitte
    {
        // Dreieckstausch
                                  // Bsp. Haus 
        tmp = text.at(b);         // H       a
        text.at(b) = text.at(e);  // H -> s  a -> u
        text.at(e) = tmp;         // s -> H  u -> a
                                  // Haus -> suaH
    }
    
}


void wortspiegel(string &text, int pos)
{
    int begPos = pos;
    unsigned int endPos = pos;


    if ( (text.at(pos) >= 'a' && text.at(pos) <= 'z') ||
         (text.at(pos) >= 'A' && text.at(pos) <= 'Z') )
    {
        while(true)
        {
            if(begPos >= 0 && ((text.at(begPos) >= 'a' && text.at(begPos) <= 'z') ||
                              (text.at(begPos) >= 'A' && text.at(begPos) <= 'Z')))
            {
                begPos--;
            }
            else if(endPos <= text.length()-1 && ((text.at(endPos) >= 'a' && text.at(endPos) <= 'z') ||
                                                 (text.at(endPos) >= 'A' && text.at(endPos) <= 'Z')))
            {
                endPos++;
            }
            else
            {
                begPos += 1;
                endPos -= 1;
                break;
            }
        }
        
        myreverse(text, begPos, endPos); // Hilfs-funktion
    }
}