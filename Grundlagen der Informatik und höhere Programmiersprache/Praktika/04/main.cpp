#include<iostream>
#include<cmath>
using namespace std;


void zahlenRaten()
{
    cout << "Merken Sie sich eine Zahl zwischen 1 (inklusive) und 100 (exklusive)" << endl;

    int anfang = 1,
        ende = 100,
        raten = ende/2;
    char eingabe;

    do
    {
        cout << "Aktueller Ratebereich: " << anfang << " bis " << ende << endl;
        cout << "Ist " << raten << " ihre Zahl?" << endl
            << "(j) ja: gleich," << endl
            << "(k) nein: meine Zahl ist kleiner," << endl
            << "(g) nein: meine Zahl ist groesser." << endl << "? ";
        cin >> eingabe;
        if (eingabe == 'k')
        {
            ende = raten;
            raten = ceil(raten / 2.0);
        }
        else if (eingabe == 'g')
        {
            anfang = raten;
            raten += ceil((ende - anfang) / 2.0);
        }
        else if (eingabe != 'j')
        {
            cout << "Heresy! Eingabe ungueltig." << endl;
        }

    }while(eingabe != 'j');

}

char rotc(char text, int rot, char c)
{
    int tmp = 0;
    tmp = int(text) - int(c);
    tmp += rot;
    tmp %= 26;
    tmp += int(c);

    return char(tmp);
}

void caesar()
{
    string klartext = "";
    int rot = 0;
    cout << "Bitte geben Sie den zu verschluesselnden Text ein: ";
    getline(cin, klartext);

    cout << "Bitte geben Sie die Anzahl Verschiebepositionen ein (als positive ganze Zahl): ";
    cin >> rot;

    string verschluesselt = "";

    for (int i = 0; i <= klartext.length(); i++)
    {
        if (isalpha(klartext[i]))
        {
            if (islower(klartext[i]))
            {
                verschluesselt += rotc(klartext[i], rot, 'a');
            }
            else
            {
                verschluesselt += rotc(klartext[i], rot, 'A');
            }

        }
        else
            verschluesselt += klartext[i];
    }
    cout << verschluesselt << endl;

}

void fahrplanauskunft()
{
    int stunden = 0,
        minuten = 0;
    do
    {
        cout << "Bitte geben Sie die Stunden der Startuhrzeit ein: ";
        cin >> stunden;

    } while(!(stunden >= 0 && stunden < 24));

    do
    {
        cout << "Bitte geben Sie die Minuten der Startuhrzeit ein: ";
        cin >> minuten;

    } while(!(minuten >= 0 && minuten < 60));

    cout << "Der erste Bus faehrt also um " << stunden << ":" << minuten << " Uhr." << endl;

    int taktzeit = 0;

    do
    {
        cout << "Bitte geben Sie die Taktzeit in Minuten ein: ";
        cin >> taktzeit;
    } while(!(taktzeit > 0 && taktzeit <= 180));

    while(stunden < 24)
    {
        cout << stunden << ":" << minuten << " ";
        if ((minuten+taktzeit) < 60)
        {
            minuten += taktzeit;
        }
        else
        {
            stunden += 1;
            minuten = (minuten+taktzeit) % 60;
            cout << endl;
        }
    }
}


int main()
{
    //zahlenRaten();
    //caesar();
    fahrplanauskunft();

    system("PAUSE");
}
