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
 * GÜLTIG

.5.1.4.|.1.6.9.|.7.2.3
.8.7.2.|.3.4.5.|.6.1.9
.9.6.3.|.2.1.7.|.5.4.8
-------|-------|-------
.4.2.8.|.1.3.4.|.9.5.7
.1.9.7.|.6.5.2.|.8.3.4
.4.3.5.|.7.9.8.|.1.6.2
-------|-------|-------
.2.4.6.|.9.7.1.|.3.8.5
.7.5.1.|.4.8.3.|.2.9.6
.3.8.9.|.5.2.6.|.4.7.1


.5.1.4.|.8.6.9.|.7.2.3
.8.7.1.|.3.4.2.|.6.1.9
.9.6.3.|.2.1.7.|.5.3.8
-------|-------|-------
.4.2.8.|.5.3.4.|.6.5.7
.1.9.7.|.6.5.2.|.8.3.4
.4.3.5.|.7.9.8.|.1.6.2
-------|-------|-------
.2.4.6.|.9.7.1.|.3.8.5
.7.5.1.|.4.8.3.|.2.9.6
.3.8.7.|.5.2.8.|.4.7.9
*/
    
    cout << "Bitte geben Sie das Sudoku ein:" << endl;
    
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
    
    // TODO
    
    bool fehlerhaft = false;
    
    
    for(unsigned int x = 0; x < 9; x++)
    {
        unsigned int zahlenbereich[10] = {0};
        
        for(unsigned int y = 0; y < 9; y++)
        {
            zahlenbereich[sudoku[y][x]]++;
        }
        
        
        for(int i = 1; i <= 9; i++)
        {
            if(zahlenbereich[i] > 1)
            {
                cout << "Spalte " << x << ": Zahl " << i << " kommt mehrfach vor." << endl;
                fehlerhaft = true;
            }
            else if(zahlenbereich[i] < 1)
            {
                cout << "Spalte " << x << ": Zahl " << i << " kommt nicht vor." << endl;
                fehlerhaft = true;
            }

        }
    }
    
    for(unsigned int y = 0; y < 9; y++)
    {
        unsigned int zahlenbereich[10] = {0};
        
        for(unsigned int x = 0; x < 9; x++)
        {
            zahlenbereich[sudoku[y][x]]++;
        }
        for(int i = 1; i <= 9; i++)
        {
            if(zahlenbereich[i] > 1)
            {
                cout << "Zeile " << y << ": Zahl " << i << " kommt mehrfach vor." << endl;
                fehlerhaft = true;
            }
            else if(zahlenbereich[i] < 1)
            {
                cout << "Zeile " << y << ": Zahl " << i << " kommt nicht vor." << endl;
                fehlerhaft = true;
            }
        }
    }
    
    // Block zu Block
    int block_cnt = 0;
    
    for(unsigned int y = 0; y < 9; y += 3)
    {
        for(unsigned int x = 0; x < 9; x += 3)
        {
            // Blöcke
            
            unsigned int block_zahlen[9];
            unsigned int cnt = 0;
                
            for(unsigned y2 = y; y2 < y+3; y2++)
            {
                for(unsigned x2 = x; x2 < x+3; x2++)
                {
                    //Zahlen im Block in der Reihe
                    block_zahlen[cnt] = sudoku[y2][x2];
                    cnt++;
                }
                
                // einzelner Block
                if((y2+1) % 3 == 0)
                {
                    unsigned int zahlenbereich[10] = {0};
                    for(unsigned int i = 0; i < 9; i++)
                    {
                        zahlenbereich[block_zahlen[i]]++;
                    }
                    
                    for(unsigned int j = 1; j <= 9; j++)
                    {
                        if(zahlenbereich[j] > 1)
                        {
                            cout << "Block " << block_cnt << ": Zahl " << j << " kommt mehrfach vor." << endl;
                            fehlerhaft = true;
                        }
                        else if(zahlenbereich[j] < 1)
                        {
                            cout << "Block " << block_cnt << ": Zahl " << j << " kommt nicht vor." << endl;
                            fehlerhaft = true;
                        }
                    }
                    cnt = 0;
                    block_cnt++;
                }
            }
        }
    }
    
    if(!fehlerhaft)
    {
        cout << "Das Sudoku ist gueltig." << endl;
    }
    
	return 0;
}