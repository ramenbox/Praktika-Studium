#include "sort.h"

void tausche(int &i, int &j)
{
    int tmp = i;
    i = j;
    j = tmp;
}

void sortiere(int *a, int N)
{
    // Bubblesort
    int n = N;
    
    // Äußere Schleife durchläuft solange bis keine Vertauschung notwending mehr ist
    do
    {
        // Abbruchbedingung bei n < 1, da keine Vertauschung notwendig
        n = 1;
        
        for(int i = 0; i < N - 1; i++)
        {
            if(a[i] > a[i + 1])
            {
                tausche(a[i], a[i + 1]);
                
                // bleibt größer als 1
                n = i + 1;
            }
        }
    } while(n > 1);
}