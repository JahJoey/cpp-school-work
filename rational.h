// Joseph Hein MWF 2:30, Seat: 465
// Prog5 (Rational(Overloading)) Due: 12/4/17
// This .cpp is for all of the function bodies for the class funtions

#include <iostream> 

using namespace std;

class Rational {

	friend ostream &operator<<(ostream &output, Rational &Robj);
	friend istream &operator>>(istream &input, Rational &Robj);
	
public:
   Rational( int pn = 1, int pd = 1 ); // default constructor

   Rational operator+(Rational &Robj);
   Rational operator-(Rational &Robj);
   Rational operator/(Rational &Robj);
   Rational operator*(Rational &Robj);
   bool operator>(Rational &Robj);
   bool operator<(Rational &Robj);

private:
   int numerator;
   int denominator;
   void reduce(  );
};

