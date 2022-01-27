#include "texte.h"

void spalte_ab_erstem(char zeichen, std::string eingabe, std::string& erster_teil, std::string& zweiter_teil)
{
    bool found = false;
    for(unsigned int i = 0; i < eingabe.length(); i++)
    {
        if (not found)
        {
            if (eingabe.at(i) == zeichen)
            {
                found = true;
            }
            else
            {
                erster_teil += eingabe.at(i);
            }
        }
        else
        {
            zweiter_teil += eingabe.at(i);
        }
    }
}

std::string trimme(std::string s)
{
    std::string cleanbill = "";
    for(unsigned int i = 0; i < s.length(); i++)
    {
        if(s.at(i) != ' ' && s.at(i) != '\r')
        {
            cleanbill += s.at(i);
        }
    }
    
    return cleanbill;
}