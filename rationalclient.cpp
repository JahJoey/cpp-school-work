// Joseph Hein MWF 2:30, Seat: 465
// Prog5 (Rational(Overloading)) Due: 12/4/17
// This .cpp is for the client side of the program

#include<iostream>
#include"rational.h"
#include<fstream>

using namespace std;

ofstream outfile;
ifstream infile;


int main()
{
	Rational FractA, FractB, FractR;

	infile.open("ratdata.txt");
	outfile.open("465ratout.txt");   // Add your class code to the file name and close
								// the quote (example:  315ratout.txt) where 315 is your code
	
	int cnt = 0;
	char oper;

	infile >> FractA;
	while (!infile.eof())
	{	cnt++;
		infile >> oper;
		infile >> FractB;

		if(oper == '+')
			FractR =  FractA + FractB;

		else if(oper == '-')
			FractR =  FractA - FractB;

		else if(oper == '*')
			FractR =  FractA * FractB;

		else if(oper == '/')
			FractR =  FractA / FractB;


		outfile << cnt << ": ";
		outfile << FractA << "  " << oper 
			<< "  "  << FractB << " = " 
			<< FractR << endl << endl;
		outfile << cnt << ": ";
		if (FractA > FractB)
			outfile << FractA << " is greater than " << FractB << endl;
		else if (FractA < FractB)
			outfile << FractA << " is less than " << FractB << endl;
		else 
			outfile << FractA << " is equal to " << FractB << endl;
		outfile << "--------------------------------------" << endl;
		infile >> FractA;

	} // while

	infile.close();
	outfile.close();

	system("pause");
	return 0;
} // main
