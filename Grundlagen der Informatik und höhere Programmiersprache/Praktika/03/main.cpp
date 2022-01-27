#include<iostream>

using namespace std;

void datumsvergleich()
{
    int tag1 = 0,
        monat1 = 0,
        jahr1 = 0;

    cout << "Bitte geben Sie den Tag des ersten Datums ein: ";
    cin >> tag1;

    cout << "Bitte geben Sie den Monat des ersten Datums ein: ";
    cin >> monat1;

    cout << "Bitte geben Sie das Jahr des ersten Datums ein: ";
    cin >> jahr1;

    int tag2 = 0,
        monat2 = 0,
        jahr2 = 0;

    cout << "Bitte geben Sie den Tag des zweiten Datums ein: ";
    cin >> tag2;

    cout << "Bitte geben Sie den Monat des zweiten Datums ein: ";
    cin >> monat2;

    cout << "Bitte geben Sie das Jahr des zweiten Datums ein: ";
    cin >> jahr2;

    if (jahr1 != jahr2)
    {
        if (jahr1 < jahr2)
        {
            cout << "Das erste Datum liegt vor dem zeiten Datum." << endl;
        }
        else
        {
            cout << "Das zweite Datum liegt vor dem ersten Datum." << endl;
        }
    }
    else
    {
        if ((monat1 == monat2) && (tag1 == tag2))
            cout << "Beide Datumsangaben sind gleich." << endl;
        else
        {
            if (monat1 < monat2)
            {
                cout << "Das erste Datum liegt vor dem zeiten Datum." << endl;
            }
            else if (monat1 > monat2)
            {
                cout << "Das zweite Datum liegt vor dem ersten Datum." << endl;
            }
            else
            {
                if (tag1 < tag2)
                {
                    cout << "Das erste Datum liegt vor dem zeiten Datum." << endl;
                }
                else if (tag1 > tag2)
                {
                    cout << "Das zweite Datum liegt vor dem ersten Datum." << endl;
                }
            }
        }
    }

}

void zahlenvergleich()
{
    int werte[5] = {0, 0, 0, 0, 0};
    int kleinsteZahl[2] = {0, 0},
        groessteZahl[2] = {0, 0};

    for(int i = 0; i < 5; i++)
    {
        cout << "Bitte geben Sie die " << i+1 << ". Zahl ein: ? ";
        cin >> werte[i];

        if (i < 1)
        {
            kleinsteZahl[0] = werte[i];
            kleinsteZahl[1] = i+1;
            groessteZahl[0] = werte[i];
            groessteZahl[1] = i+1;
        }

        if (kleinsteZahl[0] > werte[i])
        {
            kleinsteZahl[0] = werte[i];
            kleinsteZahl[1] = i+1;
        }
        if (groessteZahl[0] < werte[i])
        {
            groessteZahl[0] = werte[i];
            groessteZahl[1] = i+1;
        }
    }

    cout << "Die " << kleinsteZahl[1] << ". Zahl war die kleinste der eingegebenen Zahlen und lautet: " << kleinsteZahl[0] << endl;
    cout << "Die " << groessteZahl[1] << ". Zahl war die groesste der eingegebenen Zahlen und lautet: " << groessteZahl[0] << endl;

}

int taschenrechner()
{
    char ziffer1 = 'a',
         ziffer2 = 'a';

    cout << "Bitte geben Sie die erste Ziffer ein: ? ";
    cin >> ziffer1;
    cout << "Bitte geben Sie die zweite Ziffer ein: ? ";
    cin >> ziffer2;

    if (ziffer1 != 'q' && ziffer2 != 'q')
    {
        int zahl1 = int(ziffer1) - int('0'),
            zahl2 = int(ziffer2) - int('0');
        cout << zahl1 << " + " << zahl2 << " = " << zahl1+zahl2 << endl;
        return 0;
    }
    else
    {
        cout << "Das Program wurde durch Eingabe von q beendet." << endl;
        return 1;
    }

}

int main()
{
    //datumsvergleich();
    //zahlenvergleich();
    int rueckgabe = taschenrechner();


    system("PAUSE");
    return rueckgabe;
}
