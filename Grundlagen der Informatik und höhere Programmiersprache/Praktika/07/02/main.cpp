#include <iostream>
#include <fstream>
#include "person.h"

using namespace std;

//HTML-Formatierungsfunktionen
string b(string s) //Fettgedruckt
{
    return "<b>" + s + "</b>";
}

string br(string s) //Neue Zeile
{
    return s + "<br/>";
}

string ersetze(string s, char zeichen, string newS)
{
    string tmp = "";
    for(unsigned int i = 0; i < s.length(); i++)
    {
        if (s.at(i) != zeichen)
        {
            tmp += s.at(i);
        }
        else
        {
            tmp += newS;
        }
    }
    
    return tmp;
}

int main()
{
    string eingabezeile, kurztext, langtext = "";
    ifstream textdatei("personendaten.txt");
    
    while (getline(textdatei, eingabezeile)) // EOF
    {
        Person p = extrahiere_person(eingabezeile);
        
        kurztext += br(b(p.nachname) + ", " + p.vorname) + "\n";
        
        langtext += br(b(p.vorname + " " + p.nachname) + 
                        ", " + 
                        p.geburtsdatum
                    ) + "\n";
    }
    
    
    ifstream templatedatei("webseite.html.tmpl");
    ofstream ausgabedatei("webseite.html");
    
    while(getline(templatedatei, eingabezeile))
    {
        eingabezeile = ersetze(eingabezeile, '%', kurztext);
        eingabezeile = ersetze(eingabezeile, '$', langtext);
        
        ausgabedatei << eingabezeile + "\n";
        
    }
    
    textdatei.close();
    templatedatei.close();
    ausgabedatei.close();

	return 0;
}
