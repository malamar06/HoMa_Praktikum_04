#include "CKomplex.h"
using namespace std;

int main()
{
	//In this homework we have been asked to read from a file and write to a file as results.
	//For testing we are checking the deviation of values after the Fourier Transform.
	//It is here observed that with higher number of inputs, the Fourier Transform is able to calculate
	//with less deviation. 

	vector<CKomplex> database = werte_einlesen("Daten_Original.txt");
	vector<CKomplex> fourier_komplex_koeffiziente = fourierTransform(database, 1);

	//Here saving the coefficients.
	werte_ausgeben("epsilon = default.txt", fourier_komplex_koeffiziente);// save ALL
	werte_ausgeben("epsilon = 1.txt", fourier_komplex_koeffiziente, 1.0); // save values bigger than 1
	werte_ausgeben("epsilon = 0.1.txt", fourier_komplex_koeffiziente, 0.1);// save values bigger than 0.1
	werte_ausgeben("epsilon = 0.01.txt", fourier_komplex_koeffiziente, 0.01);// save values bigger than 0.01
	werte_ausgeben("epsilon = 0.001.txt", fourier_komplex_koeffiziente, 0.001);// save values bigger than 0.001
	
	vector<CKomplex> databaseEpsilon = werte_einlesen("epsilon = default.txt");//reading the saved coefficient values
	vector<CKomplex> ruck_werte_E1 = fourierTransform(databaseEpsilon, -1);//transforming coefficients to corresponding numbers
	cout << "Maximale Abweichung bei Standard-Epsilon: " << vergleichen(database, ruck_werte_E1) << endl;//printing the deviation

	databaseEpsilon = werte_einlesen("epsilon = 0.001.txt");//reading the saved coefficient values
	ruck_werte_E1 = fourierTransform(databaseEpsilon, -1);//back transformation
	cout << "Maximale Abweichung bei epsilon=0.001: " << vergleichen(database, ruck_werte_E1) << endl;//printing the deviation

	databaseEpsilon = werte_einlesen("epsilon = 0.01.txt");//reading the saved coefficient values
	ruck_werte_E1 = fourierTransform(databaseEpsilon, -1);//back transformation
	cout << "Maximale Abweichung bei epsilon=0.01: " << vergleichen(database, ruck_werte_E1) << endl;//printing the deviation

	databaseEpsilon = werte_einlesen("epsilon = 0.1.txt");//reading the saved coefficient values
	ruck_werte_E1 = fourierTransform(databaseEpsilon, -1);//back transformation
	cout << "Maximale Abweichung bei epsilon=0.1: " << vergleichen(database, ruck_werte_E1) << endl;//printing the deviation

	databaseEpsilon = werte_einlesen("epsilon = 1.txt");//reading the saved coefficient values
	ruck_werte_E1 = fourierTransform(databaseEpsilon, -1);//back transformation
	cout << "Maximale Abweichung bei epsilon=1: " << vergleichen(database, ruck_werte_E1) << endl;//printing the deviation

	/* TEST THINGS
	vector<CKomplex> database = werte_einlesen("testeingabe.txt");
	vector<CKomplex> fourierkoeffiziente = fourierTransform_hin(database, 1);
	werte_ausgeben("testausgabe.txt", fourierkoeffiziente, 0.001);
	vector<CKomplex> rucktransformationwerte = fourierTransform_hin(fourierkoeffiziente, -1);
	werte_ausgeben("testausgaberuck.txt", rucktransformationwerte, 0.001);
	*/

	return 0;
}