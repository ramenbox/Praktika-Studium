#include <iostream>

using namespace std;

void waitForInput()
{
    cout << "Drücken Sie eine beliebige Taste...";
    cin.ignore();
    cin.get();
}


int main()
{
    //INF-WI-02.01
    /*
    Input       Expected output
    a           Der Buchstabe a hat die Position 1 im Alphabet.
    d           Der Buchstabe d hat die Position 4 im Alphabet.
    z           Der Buchstabe z hat die Position 26 im Alphabet.
    */
    char char_input = 'a';

    cout << "Bitte geben Sie den Buchstaben ein: ? ";
    cin >> char_input;

    cout << "Der Buchstabe " << char_input << " hat die Position " << (int(char_input) - int('a')+1) << " im Alphabet." << endl;

    waitForInput();

    //INF-WI-02.02
    /*
    Input       Expected output
    12.3        Die Temperatur in Fahrenheit lautet: 54.14
    55.4        Die Temperatur in Fahrenheit lautet: 131,72
    30.2        Die Temperatur in Fahrenheit lautet: 86.36
    */
    double temperature = 0.0;

    cout << "Bitte geben Sie die Temperatur in Grad Celsius ein: ? ";
    cin >> temperature;

    cout << "Die Temperatur in Fahrenheit lautet: " << temperature * 1.8 + 32 << endl;

    waitForInput();

    //INF-WI-02.03
    /*
    Input       Expected output
    23.4        Die Laenge in Fuss lautet: 76.7707
    19.1        Die Laenge in Fuss lautet: 62.6633
    55.1        Die Laenge in Fuss lautet: 180.7743
    */

    double length = 0.0;

    cout << "Bitte geben Sie die Laenge in Metern ein: ? ";
    cin >> length;

    cout << "Die Laenge in Fuss lautet: " << length * 3.2808 << endl;

    waitForInput();

    //INF-WI-02.04
    /*
    Input       Expected output
    34.5        Die Geldmenge in US Dollar lautet: 44.7017
    12.1        Die Geldmenge in US Dollar lautet: 13.95
    101.5       Die Geldmenge in US Dollar lautet: 117.03

    Wechselkurs (1,15 US Dollar [google])
    */
    double cash = 0.0;

    cout << "Bitte geben Sie die Geldmenge in Euro ein: ? ";
    cin >> cash;

    cout << "Die Geldmenge in US Dollar lautet: " << cash * 1.2957 << endl;

    waitForInput();


    //INF-WI-02.05
    /*
    Input       Expected output
    1 12.3        Das Ergebnis lautet: 54.14
    2 23.4        Das Ergebnis lautet: 76.7707
    3 34.5        Das Ergebnis lautet: 44.7017
    */

    double input = 0.0;
    int choice = 0;

    cout << "Ihre Eingabe: ? ";
    cin >> input;
    cout << "Ihre Auswahl der Umwandlung:" << endl
        << "1 - Celsius in Fahrenheit" << endl
        << "2 - Meter in Fuss" << endl
        << "3 - Euro in US Dollar" << endl;

    cin >> choice;

    cout << "Das Ergebnis lautet: "
        << 0.5 * (2 - choice) * (3 - choice) * (input * 1.8 + 32) +
        - (1 - choice) * (3 - choice) * (input * 3.2808) +
        0.5 * (2 - choice) * (1 - choice) * (input * 1.2957) << endl;

    waitForInput();


    return 0;
}
