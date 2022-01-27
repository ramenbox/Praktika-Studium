#include "CKomplex.h"
#include <iostream>
#include <fstream>   
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

vector<CKomplex> werte_einlesen(const char* dateiname)
{
	int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
	// File oeffnen
	ifstream fp;
	fp.open(dateiname);
	// Dimension einlesen
	fp >> N;
	// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0, 0);
	for (i = 0; i < N; i++)
		werte[i] = null;
	// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		CKomplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();

	return werte;
}

void werte_ausgeben(const char* dateiname, vector<CKomplex> werte, double epsilon = -1.0)
{
	int i;
	int N = werte.size();
	// File oeffnen
	ofstream fp;
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].getRe() << "\t" << werte[i].getIm() << endl;
	// File schliessen
	fp.close();
}

vector<CKomplex> HinTransformieren(vector<CKomplex> eingabe)
{
	vector<CKomplex> ausgabe;
	//ausgabe.resize(eingabe.size());
	int N = eingabe.size();

	for (int n = 0; n < N; n++)
	{
		CKomplex v;
		for (int k = 0; k < N; k++)
		{
			v += CKomplex(eingabe[k] * ((-2.0 * M_PI * k * n) / N));
		}
		v *= (1 / sqrt(N));
		ausgabe.push_back(v);
	}

	return ausgabe;
}

vector<CKomplex> RuckTransformieren(vector<CKomplex> eingabe)
{
	vector<CKomplex> ausgabe;
	//ausgabe.resize(eingabe.size());
	int N = eingabe.size();

	for (int n = 0; n < N; n++)
	{
		CKomplex v;
		for (int k = 0; k < N; k++)
		{
			v += CKomplex(eingabe[k] * ((2 * M_PI * k * n) / N));
		}
		v *= (1 / sqrt(N));
		ausgabe.push_back(v);
	}
	return ausgabe;
}

double abweichung(vector<CKomplex> hin, vector<CKomplex> ruck) 
{
	double maxAbweichung = 0;
	int N = hin.size();

	for (int i = 0; i < N; i++) 
	{
		double tmp = abs(hin[i].getRe() - ruck[i].getRe());
		if (tmp > maxAbweichung) 
		{
			maxAbweichung = tmp;
		}
	}
	return maxAbweichung;
}

int main()
{
	// Werte einlesen von Daten_original.txt
	vector<CKomplex> original = werte_einlesen("Daten_original.txt");

	// Transformieren der eingelesenen Daten durchführen
	vector<CKomplex> ausgabe = HinTransformieren(original);

	// Werte abspeichern
	werte_ausgeben("DateiDefault.txt", ausgabe);
	werte_ausgeben("Datei01.txt", ausgabe, 0.1);
	werte_ausgeben("Datei10.txt", ausgabe, 1.0);

	// Werte einlesen
	vector<CKomplex> HinDefault = werte_einlesen("DateiDefault.txt");
	vector<CKomplex> Hin01 = werte_einlesen("Datei01.txt");
	vector<CKomplex> Hin10 = werte_einlesen("Datei10.txt");

	// Rücktransformation
	vector<CKomplex> RuckDefault = RuckTransformieren(HinDefault);
	vector<CKomplex> Ruck01 = RuckTransformieren(Hin01);
	vector<CKomplex> Ruck10 = RuckTransformieren(Hin10);

	//Abweichungen
	cout << "Maximale Abweichung bei Standard-Epsilon: " << abweichung(original, RuckDefault) << endl;
	cout << "Maximale Abweichung bei epsilon=0.1: " << abweichung(original, Ruck01) << endl;
	cout << "Maximale Abweichung bei epsilon=1.0: " << abweichung(original, Ruck10) << endl;

	system("pause");
	return 0;
}
