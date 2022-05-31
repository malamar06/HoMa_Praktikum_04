#include "Ckomplex.h"



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

CKomplex::CKomplex(double phi)
{
	//ich weiss nicht
}