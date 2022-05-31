#include <iostream>
#include <fstream>
#include "CKomplex.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

CKomplex operator+(CKomplex a, CKomplex b)
{
	CKomplex neu(a.re() + b.re(), a.im() + b.im());
	return neu;
}
CKomplex operator*(CKomplex a, CKomplex b)
{
	double neu_real = (a.re() * b.re()) - (a.im() * b.im());
	double neu_im = (a.re() * b.im()) + (a.im() * b.re());
	CKomplex neu(neu_real, neu_im);
	return neu;
}
CKomplex operator*(CKomplex a, double b)
{
	CKomplex neu(a.re() * b, a.im() * b);
	return neu;
}

CKomplex operator*(double b,CKomplex a)
{
	CKomplex neu(a.re() * b, a.im() * b);
	return neu;
}

void CKomplex::operator=(CKomplex b)
{
	real = b.re();
	img = b.im();
}

vector<CKomplex> werte_einlesen(const std::string dateiname)
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
void werte_ausgeben(const std::string dateiname, vector<CKomplex> werte, double epsilon = -1)
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
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
	// File schliessen
	fp.close();
}

vector<CKomplex> fourierTransform(vector<CKomplex> database, int richtung) // 1 hin, -1 ruck
{
	vector<CKomplex> returnlist;
	CKomplex aktuelSUMM;
	//CKomplex hoeversZahl;
	int N = database.size();
	double koeffizient = 1 / sqrt(N);
	
	for (int n = 0; n < N; n++)
	{
		
		aktuelSUMM.null();
		for (int k = 0; k < N; k++)
		{
			CKomplex hoeversZahl(cos(2 * M_PI * k * n / N), -1 * richtung * sin(2 * M_PI * k * n / N));
			
			aktuelSUMM = aktuelSUMM + database[k] * hoeversZahl;
				
		}
		returnlist.push_back(aktuelSUMM * koeffizient);
	}
	
	return returnlist;
}

double vergleichen(vector<CKomplex> list1, vector<CKomplex> list2)
{
	double grossteunterschied = 0;
	double derBetrag = 0;

	/*
	int lenght1 = list1.size();
	int lenght2 = list2.size();
	int lenght;
	if (lenght1 > lenght2)
	{
		lenght = lenght1;
	}
	else
	{
		lenght = lenght2;
	}
	*/
	for (int i = 0; i < 1000; i++)
	{
		derBetrag = abs(list1[i].abs()) - abs(list2[i].abs());
		if (derBetrag > grossteunterschied)
		{
			grossteunterschied = derBetrag;
		}
		derBetrag = 0;
	}

	return grossteunterschied;
}


int main()
{
	
	vector<CKomplex> database = werte_einlesen("Daten_Original.txt");
	vector<CKomplex> fourier_komplex_koeffiziente = fourierTransform(database, 1);

	werte_ausgeben("epsilon = default.txt", fourier_komplex_koeffiziente);
	werte_ausgeben("epsilon = 1.txt", fourier_komplex_koeffiziente, 1);
	werte_ausgeben("epsilon = 0.1.txt", fourier_komplex_koeffiziente, 0.1);
	werte_ausgeben("epsilon = 0.01.txt", fourier_komplex_koeffiziente, 0.01);
	werte_ausgeben("epsilon = 0.001.txt", fourier_komplex_koeffiziente, 0.001);
	
	vector<CKomplex> databaseEpsilon = werte_einlesen("epsilon = default.txt");
	vector<CKomplex> ruck_werte_E1 = fourierTransform(databaseEpsilon, -1);
	cout << "Maximale Abweichung bei Standard-Epsilon: " << vergleichen(database, ruck_werte_E1) << endl;

	databaseEpsilon = werte_einlesen("epsilon = 0.001.txt");
	ruck_werte_E1 = fourierTransform(databaseEpsilon, -1);
	cout << "Maximale Abweichung bei epsilon=0.001: " << vergleichen(database, ruck_werte_E1) << endl;

	databaseEpsilon = werte_einlesen("epsilon = 0.01.txt");
	ruck_werte_E1 = fourierTransform(databaseEpsilon, -1);
	cout << "Maximale Abweichung bei epsilon=0.01: " << vergleichen(database, ruck_werte_E1) << endl;

	databaseEpsilon = werte_einlesen("epsilon = 0.1.txt");
	ruck_werte_E1 = fourierTransform(databaseEpsilon, -1);
	cout << "Maximale Abweichung bei epsilon=0.1: " << vergleichen(database, ruck_werte_E1) << endl;

	databaseEpsilon = werte_einlesen("epsilon = 1.txt");
	ruck_werte_E1 = fourierTransform(databaseEpsilon, -1);
	cout << "Maximale Abweichung bei epsilon=1: " << vergleichen(database, ruck_werte_E1) << endl;

	/*
	vector<CKomplex> database = werte_einlesen("testeingabe.txt");
	vector<CKomplex> fourierkoeffiziente = fourierTransform_hin(database, 1);
	werte_ausgeben("testausgabe.txt", fourierkoeffiziente, 0.001);
	vector<CKomplex> rucktransformationwerte = fourierTransform_hin(fourierkoeffiziente, -1);
	werte_ausgeben("testausgaberuck.txt", rucktransformationwerte, 0.001);
	*/

	return 0;
}