#pragma once
#include <vector>
using namespace std;
#include <iostream>

class CKomplex //Komplex nummar class
{
private:
	double real;
	double img;

public:
	CKomplex(double a, double b);//easy konstrukter
	//CKomplex(double phi);//this is just not clear what professor wants me to do...
	CKomplex();//empty constructer for just decleration
	double re();//return real part
	double im();//return img part
	double abs();//lenght of complex vector or absolute value
	void null();// number = 0
	void operator=(CKomplex b);//this is unnecceary i coded it just to be safe

};

CKomplex operator-(CKomplex a, CKomplex b);
CKomplex operator*(CKomplex a, double b);
CKomplex operator*(CKomplex a, CKomplex b);
CKomplex operator+(CKomplex a, CKomplex b);
//Operator overloading inorder to be able to do calculations with new complex number class

double vergleichen(vector<CKomplex> list1, vector<CKomplex> list2);//Checking the difference between the komplex value
vector<CKomplex> werte_einlesen(const std::string dateiname);//input funktion from Herr Hoever
void werte_ausgeben(const std::string dateiname, vector<CKomplex> werte, double epsilon = -1);//output funktion from Herr Hoever
vector<CKomplex> fourierTransform(vector<CKomplex> database, int richtung = 1);//Actual Fourier Transform funktion
//takes a list of values and transforms them into Fourier Koeffizienten. 
//Funktion can also perform a back transformation to calculate the Input list from before calculated Koeeffizienten.
//Input parameter 1 for Fourier Transform. -1 for back Transform
