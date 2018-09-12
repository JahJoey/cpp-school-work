// Joseph Hein MWF 2:30, Seat: 465
//Prog1 (insurance) Due: 9/12/17
// The purpose of this program is to read the information from a .txt document, fill that 
// information into a set of 4 parallel arrays, bubble sort it by name, and then to display
// specific things by client request. The last thing is it has a built in binary search
// and display for searching up specific clients.

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const int SIZE = 50;

//function prototypes
void fillarrays(int& numclients, string clientname[],
	string policy[], int yrs[], int premium[]);
void printarrays(int numclients, string clientname[], string policy[],
	int yrs[], int premium[]);
void BSort(int numclients, string clientname[], string policy[],
	int yrs[], int premium[]);
void LoyalClient(int numclients, string clientname[], int yrs[]);
void ShowBoats(int numclients, string clientname[], string policy[], int premium[]);
int HighestPremium(int numclients, int premium[]);
void FindClient(int numclients, string targetname, string clientname[], string policy[],
	int yrs[], int premium[]);
int BinarySearch(string clientname[], int numclients, string targetname);

int main() {

	//decleration
	int numclients = 0;
	int highPre;
	string targetname;
	string clientname[SIZE];  //Start of array decleration
	string policy[SIZE];
	int yrs[SIZE];
	int premium[SIZE];

	fillarrays(numclients, clientname, policy, yrs, premium); //Start of function calls
	printarrays(numclients, clientname, policy, yrs, premium);
	BSort(numclients, clientname, policy, yrs, premium);
	printarrays(numclients, clientname, policy, yrs, premium);
	LoyalClient(numclients, clientname, yrs);
	ShowBoats(numclients, clientname, policy, premium);
	highPre = HighestPremium(numclients, premium); //End of function calls

	//Display for highest premium with the returned position
	cout << "The client with the highest Premium : " << clientname[highPre]
		<< endl << endl;

	//client search and display function call
	FindClient(numclients, targetname, clientname, policy, yrs, premium);

	system("pause");
	return 0;
}

void fillarrays(int& numclients, string clientname[],
	string policy[], int yrs[], int premium[]) {
	ifstream infile;

	infile.open("insur.txt"); //File opened

	while (!infile.eof()) { //reads file until end of file (eof)
		
		//start of reading file, filling parallel arrays
		getline(infile, clientname[numclients]);
		getline(infile, policy[numclients]);
		infile >> yrs[numclients];
		infile >> premium[numclients];
		infile.ignore();
		numclients++; //client counter

	}
	infile.close(); //File closed
}

void printarrays(int numclients, string clientname[], string policy[],
	int yrs[], int premium[]) {

	cout << setw(10) << "Client" << right << setw(16) << "Policy" << setw(9) << "Years"
		<< setw(12) << "Premium" << endl;
	cout << "-------------------------------------------------------------------" << endl;

	for (int k = 0; k < numclients; k++) {
		cout << left << setw(20) << clientname[k] << setw(10) << policy[k] <<
			setw(10) << yrs[k] << setw(20) << premium[k] << endl;
	}
	cout << endl;
}

void BSort(int numclients, string clientname[], string policy[],
	int yrs[], int premium[]) {
	string temp1, temp2;
	int temp3, temp4;
	bool sort = false;

	while (!sort) {
		sort = true;
		for (int k = 0; k < (numclients - 1); k++) {
			if (clientname[k] > clientname[k + 1]) {
				temp1 = clientname[k];
				clientname[k] = clientname[k + 1];
				clientname[k + 1] = temp1;

				temp2 = policy[k];
				policy[k] = policy[k + 1];
				policy[k + 1] = temp2;

				temp3 = yrs[k];
				yrs[k] = yrs[k + 1];
				yrs[k + 1] = temp3;

				temp4 = premium[k];
				premium[k] = premium[k + 1];
				premium[k + 1] = temp4;

				sort = false;
			}
		}
		numclients--;
	}
}

void LoyalClient(int numclients, string clientname[], int yrs[]) {

	cout << "The Loyal Client(s): " << endl;
	for (int k = 0; k < numclients; k++) {
		if (yrs[k] >= 10) {
			cout << left << setw(20) << clientname[k] << endl;
		}
	}
	cout << endl;
}

void ShowBoats(int numclients, string clientname[], string policy[], int premium[]) {

	cout << "The client(s) with a boat policy (Premium of $4800+): " << endl;
	for (int k = 0; k < numclients; k++) {
		if (policy[k] == "Boat" && premium[k] >= 4800) {
			cout << clientname[k] << endl;
		}
	}
	cout << endl;
}

int HighestPremium(int numclients, int premium[]) {
	int high = -1;
	int pos;

	for (int k = 0; k < numclients; k++) {
		if (premium[k] > high) {
			pos = k;
			high = premium[k];
		}
	}
	return pos;
}

void FindClient(int numclients, string targetname, string clientname[], string policy[],
	int yrs[], int premium[]) {
	int position = -1;
	
	cout << "Enter client name to search(enter DONE to quit search): ";
	getline(cin, targetname);
	position = BinarySearch(clientname, numclients, targetname);
	while(targetname != "DONE") {
		if (position == -1) {
		cout << "Client not found!" << endl;

		getline(cin, targetname);
		position = BinarySearch(clientname, numclients, targetname);
		}
		else {
		cout << endl;
		cout << setw(10) << "Client" << right << setw(16) << "Policy" << setw(9) << "Years"
			<< setw(12) << "Premium" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << left << setw(20) << clientname[position] << setw(10) << policy[position] <<
			setw(10) << yrs[position] << setw(20) << premium[position] << endl;

		getline(cin, targetname);
		position = BinarySearch(clientname, numclients, targetname);
		}
	}

}

int BinarySearch(string clientname[], int numclients, string targetname) {
	int  first = 0,                    // first array element
		last = numclients - 1,          // last array element
		middle,                       // midpoint of search
		position = -1;                // position of search value
	bool found = false;                // flag

	while (!found && first <= last)
	{
		middle = (first + last) / 2;    // calculate midpoint
		if (clientname[middle] == targetname)     // if value is found at mid
		{
			found = true;
			position = middle;
		}
		else if (clientname[middle] > targetname) // if value is in lower half
			last = middle - 1;
		else
			first = middle + 1;          // if value is in upper half
	}
	return position;
}