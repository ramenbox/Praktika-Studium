#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    int sudoku[9][9] = {0};
    
    string eingabe[11] = {""};
    
/*
.5.1.4.|.8.6.9.|.7.2.3
.8.7.2.|.3.4.5.|.6.1.9
.9.6.3.|.2.1.7.|.5.4.8
-------|-------|-------
.6.2.8.|.1.3.4.|.9.5.7
.1.9.7.|.6.5.2.|.8.3.4
.4.3.5.|.7.9.8.|.1.6.2
-------|-------|-------
.2.4.6.|.9.7.1.|.3.8.5
.7.5.1.|.4.8.3.|.2.9.6
.3.8.9.|.5.2.6.|.4.7.1

.9.4.6.|.3.1.8.|.2.7.5
.1.2.3.|.7.5.6.|.9.4.8
.5.8.7.|.2.4.9.|.6.3.1
-------|-------|-------
.8.1.4.|.9.2.5.|.7.6.3
.2.7.5.|.1.6.3.|.8.9.4
.6.3.9.|.8.7.4.|.1.5.2
-------|-------|-------
.3.6.8.|.5.9.2.|.4.1.7
.4.5.1.|.6.8.7.|.3.2.9
.7.9.2.|.4.3.1.|.5.8.6
*/
    
    cout << "Bitte geben Sie das Sudoku ein:" << endl;
    /*
    for(int i = 0; i < 11; i++)
    {
        getline(cin, eingabe[i]);
    }*/
    
    // Spalten
    for(unsigned int l = 0, i = 0; l < 11; l++)
    {
        getline(cin, eingabe[l]);
        
        // Zeilen
        for(unsigned int t = 0, j = 0; t < eingabe[l].length(); t++)
        {
            // i und j sollen nur bis auf 9 hochzählen, 
            // damit wir die Werte vom string array eingabe[11] in dem integer array sudoku[9][9] speichern können
            
            // Ignoriert alles außer Zahlen
            if (eingabe[l][t] >= '0' && eingabe[l][t] <= '9')
            {
                sudoku[i][j] = eingabe[l][t] - int('0');
                j++;
            }
        }
        
        // Prüft ob Zeile Zahlen enthält bzw. keine Trennzeile, somit 9x9 anstatt 11x9
        if (eingabe[l][0] == '.')
        {
            i++;
        }
    }
    
    cout << "Das Sudoku lautet:" << endl;
    
    // Spalten
    for(unsigned int i = 0; i < 9; i++)
    {
        // Zeilen
        for(unsigned int j = 0; j < 9; j++)
        {
            cout << ';' << sudoku[i][j];
            
            // j+1 überspringt 0
            // Nur bei 3. Zahl wird Trennung hinzugfügt
            // Bei j+1 = 9 keine Trennung
            if ((j+1) % 3 == 0 && (j+1) != 9)
            {
                cout << ";//";
            }
        }
        cout << endl;
        // Trennlinie bei der 3. Zeile
        if ((i+1) % 3 == 0 && (i+1) != 9)
        {
            cout << "=======//=======//=======" << endl;
        }
    }
    
	return 0;
}
