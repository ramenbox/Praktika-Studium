#include <iostream>
#include "wortspiegel.h"

using namespace std;


int main(int argc, char **argv)
{
    string text = "";
    cout << "Bitte geben Sie den Text ein: ? ";
    getline(cin, text);
    
    char eingabe;
    
    int pos = 0;
    
    do
    {
        cout << text << endl;
        for(int i = 0; i < pos; i++)
            cout << " ";
        cout << "*" << endl;
        
        cout << "Befehl (l: links, r: rechts, s: spiegeln, q: Ende) ?- ";
        cin >> eingabe;
        
        switch(eingabe)
        {
            case 'l':
            {
                pos--;
                break;
            }
            case 'r':
            {
                pos++;
                break;
            }
            case 's':
            {
                wortspiegel(text, pos);
                break;
            }
            default:
            {
                break;
            }
        }
        
        if (pos < 0)
        {
            pos = 0;
        }
        else if (unsigned(pos) > text.length()-1)
        {
            pos = text.length()-1;
        }
        
        
        
    } while(eingabe != 'q');

	return 0;
}
