// Joseph Hein MWF 2:30, Seat: 465
// Prog5 (Rational(Overloading)) Due: 12/4/17
// This .cpp is for all of the function bodies

#include <cstdlib>
#include <iostream> 
#include "rational.h"
using namespace std;

Rational::Rational( int pn, int pd )
{
   if (pd)
   {
		numerator = pn;
		denominator = pd;
   }
   else
   {
		numerator = 1;
		denominator = 1;
   }
}



void Rational::reduce(  )
{
   int largest, gcd = 1;  // greatest common divisor;

   largest = ( numerator > denominator ) ? numerator: denominator;

   for ( int loop = 2; loop <= largest; ++loop )
       if ( numerator % loop == 0 && denominator % loop == 0 )
          gcd = loop;

   numerator /= gcd;
   denominator /= gcd;
}

ostream &operator<<(ostream &output, Rational &Robj) {
	if (Robj.denominator == 1) { // if the value is 1 or greater don't show the denominator
		output << Robj.numerator;
	}
	else { //if the value is less then one then show the whole fraction
		output << Robj.numerator << "/" << Robj.denominator;
	}

	return output;
}

istream &operator>>(istream &input, Rational &Robj) {
	input >> Robj.numerator;
	input.ignore();
	input >> Robj.denominator;
	return input;
}

Rational Rational::operator+(Rational &Robj) {
	Rational Tobj;
	int tempnumer = numerator;
	int tempden = denominator;
	int temp2numer = Robj.numerator;
	int temp2den = Robj.denominator;

	while (tempden != temp2den) { // loop until LCD is found

		if (tempden < temp2den) {
			tempden += denominator;
			tempnumer += numerator;
		}
		else {
			temp2den += Robj.denominator;
			temp2numer += Robj.numerator;
		}
	}

	Tobj.numerator = tempnumer + temp2numer;
	Tobj.denominator = tempden;
	Tobj.reduce(); // fraction reduction before returning

	return Tobj;
}

Rational Rational::operator-(Rational &Robj) {
	Rational Tobj;
	int tempnumer = numerator;
	int tempden = denominator;
	int temp2numer = Robj.numerator;
	int temp2den = Robj.denominator;

	while (tempden != temp2den) { // loop until LCD is found

		if (tempden < temp2den) {
			tempden += denominator;
			tempnumer += numerator;
		}
		else {
			temp2den += Robj.denominator;
			temp2numer += Robj.numerator;
		}
	}

	Tobj.numerator = tempnumer - temp2numer;
	Tobj.denominator = tempden;
	Tobj.reduce(); // fraction reduction before returning

	return Tobj;
}

Rational Rational::operator/(Rational &Robj) {
	Rational Tobj;
	int tempnumer = numerator;
	int tempden = denominator;
	int temp2numer = Robj.numerator;
	int temp2den = Robj.denominator;

	while (tempden != temp2den) { // loop until LCD is found

		if (tempden < temp2den) {
			tempden += denominator;
			tempnumer += numerator;
		}
		else {
			temp2den += Robj.denominator;
			temp2numer += Robj.numerator;
		}
	}

	Tobj.numerator = tempnumer * temp2den;
	Tobj.denominator = temp2numer * tempden;
	Tobj.reduce(); // fraction reduction before returning

	return Tobj;
}

Rational Rational::operator*(Rational &Robj) {
	Rational Tobj;
	int tempnumer = numerator;
	int tempden = denominator;
	int temp2numer = Robj.numerator;
	int temp2den = Robj.denominator;

	Tobj.numerator = tempnumer * temp2numer;
	Tobj.denominator = tempden * temp2den;
	Tobj.reduce(); // fraction reduction before returning

	return Tobj;
}

bool Rational::operator<(Rational &Robj) {
	Rational Tobj;
	Rational Sobj;
	double fractionOne;
	double fractionTwo;

	Tobj.numerator = numerator;
	Tobj.denominator = denominator;
	Sobj.numerator = Robj.numerator;
	Sobj.denominator = Robj.denominator;

	Tobj.reduce(); // fraction reduction before comparing
	Sobj.reduce(); // fraction reduction before comparing

	fractionOne = (double)Tobj.numerator / (double)Tobj.denominator;
	fractionTwo = (double)Sobj.numerator / (double)Sobj.denominator;

	return (fractionOne < fractionTwo);
}

bool Rational::operator>(Rational &Robj) {
	Rational Tobj;
	Rational Sobj;
	double fractionOne;
	double fractionTwo;

	Tobj.numerator = numerator;
	Tobj.denominator = denominator;
	Sobj.numerator = Robj.numerator;
	Sobj.denominator = Robj.denominator;

	Tobj.reduce(); // fraction reduction before comparing
	Sobj.reduce(); // fraction reduction before comparing

	fractionOne = (double)Tobj.numerator / (double)Tobj.denominator;
	fractionTwo = (double)Sobj.numerator / (double)Sobj.denominator;

	return (fractionOne > fractionTwo);
}