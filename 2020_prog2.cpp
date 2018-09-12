// Joseph Hein MWF 2:30, Seat: 465
// Prog2 (CustAccounts) Due: 9/28/17
// The purpose of this program is to either read from a .txt or take user input
// to have customer data entered and then the ability to change/show all customers/ or to 
// add customer's until at capacity.

#include <iostream>	
#include <string>
#include <iomanip>
using namespace std;

const int MAXCUST = 30;  //customer capacity

struct Customer { //struct decleration
	int id;
	string name;
	string zip;
	double balance;
	string lastpay;
};

void menu(Customer customer[], const int MAXCUST, int& numcust, int& entry);
void addcust(Customer customer[], int& numcust);
void updatecust(Customer customer[], int numcust);
void displaycust(Customer customer[], int numcust);
int findcust(Customer customer[], int numcust, int entry);

int main() {
	int numcust = 0; // customer count set to zero
	int entry;
	Customer customer[30];

	menu(customer, MAXCUST, numcust, entry);

	return 0;
}

void menu(Customer customer[], const int MAXCUST, int& numcust, int& entry) {

	// Display a menu.
	cout << "------------------------------------------------" << endl;
	cout << "1. Enter new account information\n";
	cout << "2. Change account information\n";
	cout << "3. Display all account information\n";
	cout << "4. Exit the program\n";
	cout << "------------------------------------------------" << endl;
	// Get the user's choice.
	cout << "Enter your choice: ";
	cin >> entry;
	cout << entry << endl;  //echo statement for bgunix

	while (entry != 4) {

		while (entry < 1 || entry > 4) { // data validation for a value between 1-4
			cout << "Invalid Value, try again! ";
			cin >> entry;
			cout << entry << endl;
		}

		if (entry == 1) {
			if (numcust < MAXCUST) { // check to make sure not at capacity
				addcust(customer, numcust);
				numcust++; // customer count initiated
			}
			else {
				cout << "Customers cannot be added at this time!"; // at capacity
			}
		}
		else if (entry == 2) {
			updatecust(customer, numcust);
		}
		else if (entry == 3) {
			displaycust(customer, numcust);
		}
		menu(customer, MAXCUST, numcust, entry);
	}
}

void addcust(Customer customer[], int& numcust) {
	int bal = -1;
	
	cout << "Enter the customer ID: "; // gathering customer ID
	cin >> customer[numcust].id;
	cout << customer[numcust].id << endl;
	cin.ignore();

	cout << "Enter the customer name: "; // gathering customer name
	getline(cin, customer[numcust].name);
	cout << customer[numcust].name << endl;

	cout << "Enter the customer zipcode: "; // gathering customer zip
	getline(cin, customer[numcust].zip);
	cout << customer[numcust].zip << endl;

	cout << "Enter the customer's balance: "; // gathering customer balance
	cin >> bal;
	cout << bal << endl;
		while (bal < 0) { // data validation to make sure balance is positive
			cout << "Balance can not be negative; Try again!: ";
			cin >> bal;
			cout << bal << endl;
		}
	customer[numcust].balance = bal;
	cin.ignore();

	cout << "Enter customer's last pay date: "; // gathing customer last pay date
	getline(cin, customer[numcust].lastpay);
	cout << customer[numcust].lastpay << endl;
}

void updatecust(Customer customer[], int numcust) {
	int position;
	int entry;

	cout << "Enter the customer's ID: ";
	cin >> entry;
	cout << entry << endl;
	position = findcust(customer, numcust, entry); // returned position

	if (position == -1) {
		cout << "Customer was not found! " << endl;
	}
	else {
		cout << "Enter the new customer ID: "; //gathering changed ID
		cin >> customer[position].id;
		cout << customer[position].id << endl;
		cin.ignore();

		cout << "Enter the new customer name: "; // gathering changed name
		getline(cin, customer[position].name);
		cout << customer[position].name << endl;

		cout << "Enter the new customer zip: "; // gathing changed zip
		getline(cin, customer[position].zip);
		cout << customer[position].zip << endl;
		
		cout << "Enter the new customer balance: "; // gathing changed balance
		cin >> customer[position].balance;
		cout << customer[position].balance << endl;

		while (customer[position].balance < 0) { // positive balance validation
			cout << "Negative balance not accepted, try again! ";
			cin >> customer[position].balance;
			cout << customer[position].balance << endl;
		}

		cin.ignore();
		cout << "Enter the new customer last pay: "; //gathering changed last pay date
		getline(cin, customer[position].lastpay);
		cout << customer[position].lastpay << endl;
	}
}

int findcust(Customer customer[], int numcust, int entry) {
	for (int k = 0; k < numcust; k++) { //linear searching
		if (entry == customer[k].id) {
			return k; // returning position
		}
	}
	return -1; // if customer is not found, then returns -1
}

void displaycust(Customer customer[], int numcust) {
	cout << left <<setw(5) << "##" << setw(10) << "ID" << setw(15) << "Name" << setw(10) << "Zipcode" <<
		setw(10) << "Balance" << setw(10) << "Last Pay" << endl;
	cout << "-------------------------------------------------------------------" << endl;

	for (int k = 0; k < numcust; k++) {
		cout << left << setw(5) << k << setw(10) << customer[k].id << setw(15) << customer[k].name <<
			setw(10) << customer[k].zip << setw(10) << customer[k].balance <<
			setw(10) << customer[k].lastpay << endl;
	}
}