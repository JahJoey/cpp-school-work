// Joseph Hein MWF 2:30, Seat: 465
// Prog4 (Classes) Due: 11/13/17
// This .cpp is for all of the function bodies for the class funtions

#include <iostream>
#include <string>
#include <iomanip>
#include "atm.h"


ATM::ATM(int csavings, int cchecking) {
	if (cchecking > 0 && cchecking % 10 == 0) {
		checkingbalance = cchecking;
	}
	else {
		checkingbalance = 0;
	}

	if (csavings > 0 && csavings % 10 == 0) {
		savingsbalance = csavings;
	}
	else {
		savingsbalance = 0;
	}
}

void ATM::printreceipt(int cmoney, string caccount, string trans) {
	cout << "----------------------------------------" << endl;
	if (caccount == "Checking") {
		cout << setw(18) << right << "Transaction Type: " << left << trans << endl;
		cout << setw(18) << right << "Account: " << left << caccount << endl;
		cout << setw(18) << right << "Amount: $" << setw(10) << cmoney << endl;
		cout << setw(18) << right << "New Balance: $" << setw(10) << checkingbalance << endl;
	}
	else {
		cout << setw(18) << right << "Transaction Type: " << left << trans << endl;
		cout << setw(18) << right << "Account: " << left << caccount << endl;
		cout << setw(18) << right << "Amount: $" << setw(10) << cmoney << endl;
		cout << setw(18) << right << "New Balance: $" << setw(10) << savingsbalance << endl;
	}
	cout << "----------------------------------------" << endl;
}

int ATM::deposit(int cmoney, string caccount, string transaction) {
	if (caccount == "Checking") {
		checkingbalance += cmoney;
	 }
	else {
		savingsbalance += cmoney;
	}
	printreceipt(cmoney, caccount, transaction);
	return 0;
}

int ATM::withdrawal(int cmoney, string caccount, string transaction) {
	if (caccount == "Checking" && (currentwithdrawal + cmoney <= 300) && cmoney <= checkingbalance) {
		checkingbalance = checkingbalance - cmoney;
		currentwithdrawal += cmoney;
		printreceipt(cmoney, caccount, transaction);
		return 0;
	}
	else if (caccount == "Savings" && (currentwithdrawal + cmoney <= 300) && cmoney <= savingsbalance) {
		savingsbalance = savingsbalance - cmoney;
		currentwithdrawal += cmoney;
		printreceipt(cmoney, caccount, transaction);
		return 0;
	}
	else if (currentwithdrawal + cmoney > 300) {
		cout << "----------------------------------------" << endl;
		cout << "You have exceeded your daily limit" << endl;
		cout << "Sorry no Transaction" << endl;
		return 0;
	}
	else {
		cout << "----------------------------------------" << endl;
		cout << "You have exceeded your balance" << endl;
		cout << "Sorry no Transaction" << endl;
		return 0;
	}
}

int ATM::transferto(int cmoney, string caccount, string transaction) {
	if (caccount == "Checking" && (savingsbalance - cmoney >= 0)) {
		savingsbalance = savingsbalance - cmoney;
		checkingbalance += cmoney;
		printreceipt(cmoney, caccount, transaction);
		return 0;
	}
	else if (caccount == "Savings" && (checkingbalance - cmoney >= 0)) {
		checkingbalance = checkingbalance - cmoney;
		savingsbalance += cmoney;
		printreceipt(cmoney, caccount, transaction);
		return 0;
	}
	else {
		cout << "----------------------------------------" << endl;
		cout << "You have exceeded your balance" << endl;
		cout << "Sorry no Transaction" << endl;
		return 0;
	}
}