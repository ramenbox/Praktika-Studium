#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    int iarr[5];
    for(int i = 0; i < 5; i++)
    {
        cout << "Bitte geben Sie die " << i+1 << ". Zahl ein: ? ";
        cin >> iarr[i];
        
        if (iarr[i] < 1 or iarr[i] > 9)
        {
            i--;
        }
        
    }
    
    bool barr[5] = {false, false, false, false, false};
    
    
    for(int j = 9; j >= 1; j--)
    {
        cout << j << " ";
        for(int k = 0; k < 5; k++)
        {
            if (iarr[k] == j)
            {
                cout << "*";
                barr[k] = true;
            }
            else if (barr[k])
            {
                cout << "+";
            }
            else cout << ".";
        }
        
        cout << endl;
    }
    
    cout << "  12345" << endl;
    
	system("PAUSE");
	return 0;
}
