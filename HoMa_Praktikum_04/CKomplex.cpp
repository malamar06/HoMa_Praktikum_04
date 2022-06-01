#include "Ckomplex.h"
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

double vergleichen(vector<CKomplex> list1, vector<CKomplex> list2)
{
	double grossteunterschied = 0;
	CKomplex hoeverszahl;
	double derBetrag;

	for (int i = 0; i < 1000; i++)
	{
		hoeverszahl = list1[i] - list2[i];
		derBetrag = hoeverszahl.abs();

		if (derBetrag > grossteunterschied)
		{
			grossteunterschied = derBetrag;
		}
		derBetrag = 0;
	}

	return grossteunterschied;
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
void werte_ausgeben(const std::string dateiname, vector<CKomplex> werte, double epsilon)
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
	returnlist.resize(N);

	for (int n = 0; n < N; n++)
	{

		aktuelSUMM.null();
		for (int k = 0; k < N; k++)
		{
			CKomplex hoeversZahl(cos(2 * M_PI * k * n / N), -1 * richtung * sin(2 * M_PI * k * n / N));

			aktuelSUMM = aktuelSUMM + database[k] * hoeversZahl;

		}
		returnlist[n] = (aktuelSUMM * koeffizient);
	}

	return returnlist;
}

void CKomplex::operator=(CKomplex b)
{
	real = b.re();
	img = b.im();
}
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
CKomplex operator-(CKomplex a, CKomplex b)
{
	CKomplex neu(a.re() - b.re(), a.im() - b.im());
	return neu;
}

void CKomplex::null()
{
	img = 0;
	real = 0;
}

double CKomplex::abs()
{
	double betrag = sqrt(real * real + img * img);
	return betrag;

}
double CKomplex::re()
{
	return real;
}
double CKomplex::im()
{
	return img;
}

CKomplex::CKomplex()
{
	real = 0;
	img = 0;
}

CKomplex::CKomplex(double a, double b)
{
	real = a;
	img = b;
}
