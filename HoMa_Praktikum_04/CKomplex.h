#pragma once
#include <vector>

class CKomplex
{
private:
	double real;
	double img;

public:
	CKomplex(double a, double b);
	CKomplex(double phi);
	CKomplex();
	double re();
	double im();
	double abs();
	void null();
	void operator=(CKomplex b);

};



