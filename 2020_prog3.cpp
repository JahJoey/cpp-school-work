// Joseph Hein MWF 2:30, Seat: 465
// Prog3 (Linked List) Due: 10/25/17
// The purpose of this program is to read from a file input and create
// a linked list and then run through the corresponding functions to determine
// things such as lowest premium, etc. While also displaying the clients in the
// linked list. Then, terminated the whole linked list.

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct Client {  // Client struct
	int id;
	string name;
	string policy;
	int years;
	int premium;
	Client *nextClient; // Pointer dereferencing the next node
};

fstream infile;

int getChoice();
Client *createClient();
void addToList(Client *&firstclient , Client *newclient);
void removeOneClient(Client *&firstclient, int targetid);
void listClients(Client *&firstclient);
void listPolicy(Client *&firstclient);
void listYears(Client *&firstclient);
void lowestPremium(Client *&firstclient);
void clearList(Client *&firstclient);


int main() {

	Client *firstclient = NULL;
	Client *newclient = NULL;
	
	int targetid;
	int choice = getChoice();

	infile.open("prog3.txt"); // opening the file

	while (choice != 7 && !infile.eof()) {
		if (choice == 1) {
			newclient = createClient();
			addToList(firstclient, newclient); 
		}
		else if (choice == 2) {
			infile >> targetid;
			removeOneClient(firstclient, targetid);
		}
		else if (choice == 3) {
			listClients(firstclient);
		}
		else if (choice == 4) {
			listPolicy(firstclient);
		}
		else if (choice == 5) {
			listYears(firstclient);
		}
		else if (choice == 6) {
			lowestPremium(firstclient);
		}
		choice = getChoice();
	}

	infile.close(); // file closing
	clearList(firstclient);  // Calling fucntion to destroy the linked list

	system("pause");
	return 0;
}

int getChoice() { // Function collects the user/file input choice
	int choice;

	infile >> choice;

	while ((choice < 1 || choice > 7) && !infile.eof()) {
		cout << "Try again! Enter Choice: ";
		infile >> choice;
	}

	return choice;
}

Client *createClient() { // Creates a new client
	Client *newclient = new Client;

	infile >> newclient->id;
	infile.ignore();
	getline(infile, newclient->name);
	getline(infile, newclient->policy);
	infile >> newclient->years;
	infile >> newclient->premium;
	newclient ->nextClient = NULL;

	return newclient;
}

void addToList(Client *&firstclient, Client *newclient) { // adds the new client to the linked list
	Client *run = NULL;

	if (!firstclient) {
		firstclient = newclient;
	}
	else {
		run = firstclient;
		while (run->nextClient) {
			run = run->nextClient;
		}
		run->nextClient = newclient;
	}
}

void removeOneClient(Client *&firstclient, int targetid) {
	Client *nodeptr;
	Client *prevnode;

	if (!firstclient) { // Figures out if the head of the list is empty
		cout << "The list is empty" << endl;
		cout << "The Client (ID: " << targetid << ") was not in the list." << endl;
		return;
	}

	if (firstclient->id == targetid) { // Determines if it is first node
		nodeptr = firstclient;
		firstclient = firstclient->nextClient;
		delete nodeptr;
		cout << "The Client (ID: " << targetid << ") has been removed." << endl;
	}
	else { 
		nodeptr = firstclient;

		while (nodeptr != NULL && nodeptr->id != targetid) {
			prevnode = nodeptr;
			nodeptr = nodeptr->nextClient;
		}

		if (nodeptr) {// if nodePtr is not at the end of the list
			prevnode->nextClient = nodeptr->nextClient;
			delete nodeptr;
			cout << "The Client (ID: " << targetid << ") has been removed." << endl;
		}
		else {
			cout << "The Client (stock num: " << targetid << ") was not on the list" << endl;
		}
	}
}

void listClients(Client *&firstclient) {
	Client *nodeptr;
	nodeptr = firstclient;

	cout << "----------------------------------------------------------------------------" << endl;
	cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(20) << "Policy"
		<< setw(10) << "Years" << setw(10) << "Premium" << endl;
	cout << setw(5) << "--" << setw(20) << "----" << setw(20) << "------" << setw(10)
		<< "-----" << setw(10) << "----" << endl;

	while (nodeptr) { //runs through the nodes to display until nodeptr = NULL
		cout << left << setw(5) << nodeptr->id << setw(20) << nodeptr->name << setw(20)
			<< nodeptr->policy << setw(10) << nodeptr->years << setw(10) << nodeptr->premium << endl;

		nodeptr = nodeptr->nextClient;
	}
	cout << "----------------------------------------------------------------------------" << endl << endl;
}

void listPolicy(Client *&firstclient) {
	int cnt = 0;
	int sum = 0;
	string target;
	Client *nodeptr;

	cout << endl;
	infile.ignore();
	getline(infile, target);
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "All clients with a " << target << " policy." << endl << endl;
	cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(20) << "Policy"
		<< setw(10) << "Years" << setw(10) << "Premium" << endl;
	cout << setw(5) << "--" << setw(20) << "----" << setw(20) << "------" << setw(10)
		<< "-----" << setw(10) << "----" << endl;



	nodeptr = firstclient;
	if (!nodeptr) { // if there are no policy holders of the target
		cout << "There are no " << target << " policy holders." << endl;
		cout << "----------------------------------------------------------------------------" << endl;
	}
	else { // Run and calculates for a specific target policy
		while (nodeptr) {
			if (nodeptr->policy == target) {
				cout << left << setw(5) << nodeptr->id << setw(20) << nodeptr->name << setw(20)
					<< nodeptr->policy << setw(10) << nodeptr->years << setw(10) << nodeptr->premium << endl;
				cnt++;
				sum += nodeptr->premium;
			}
			nodeptr = nodeptr->nextClient;
		}
	}
	if (cnt > 0) {
		cout << endl;
		cout << "The average premium for " << target << " policies is: " << sum / cnt << endl << endl;
		cout << "----------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << endl;
		cout << "There were no " << target << " policy holders." << endl << endl;
		cout << "----------------------------------------------------------------------------" << endl << endl;
		
		return;
	}
}

void listYears(Client *&firstclient) {
	int target;
	int cnt = 0;
	Client *nodeptr;
	nodeptr = firstclient;

	infile >> target;
	cout << "----------------------------------------------------------------------------" << endl << endl;
	cout << "All clients with " << target << " or more years." << endl << endl;
	cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(20) << "Policy"
		<< setw(10) << "Years" << setw(10) << "Premium" << endl;
	cout << setw(5) << "--" << setw(20) << "----" << setw(20) << "------" << setw(10)
		<< "-----" << setw(10) << "----" << endl;


	if (!nodeptr) { // If there are no clients with target years or more
		cout << endl;
		cout << "There are no clients with " << target << " or more years." << endl << endl;
		cout << "----------------------------------------------------------------------------" << endl;
	}
	else {
		while (nodeptr) { // Runs through target and calculates
			if (nodeptr->years >= target) {
				cout << left << setw(5) << nodeptr->id << setw(20) << nodeptr->name << setw(20)
					<< nodeptr->policy << setw(10) << nodeptr->years << setw(10) << nodeptr->premium << endl;
				cnt++;
			}
			nodeptr = nodeptr->nextClient;
		}
	}

	if (cnt > 0) {
		cout << "----------------------------------------------------------------------------" << endl << endl;
	}
	else {
		cout << "There were no clients with " << target << " or more years." << endl;
		cout << "----------------------------------------------------------------------------" << endl << endl;

		return;
	}
}

void lowestPremium(Client *&firstclient) {
	int lowest = 100000;
	Client *nodeptr;
	Client *holder;
	nodeptr = firstclient;

	cout << endl;
	cout << "----------------------------------------------------------------------------" << endl << endl;
	cout << "The client with the lowest premium is: " << endl;

	while (nodeptr) { // Figures out lowest premium
		if (nodeptr->premium < lowest) {
			holder = nodeptr;
			lowest = holder->premium;
		}
		nodeptr = nodeptr->nextClient;
	}
	cout << left << setw(5) << holder->id << setw(20) << holder->name << setw(20)
		<< holder->policy << setw(10) << holder->years << setw(10) << holder->premium << endl;
	cout << "----------------------------------------------------------------------------" << endl << endl;
}

void clearList(Client *&firstclient) {
	Client *nodeptr;
	nodeptr = firstclient;

	while (firstclient) { // Initiates the destroying of list
		firstclient = nodeptr->nextClient;
		cout << "The client (ID: " << nodeptr->id << ") has been removed from the list." << endl;
		delete nodeptr;
		nodeptr = firstclient;
	} //Finishing
	cout << "The list is now empty!" << endl;
	cout << "Fin!" << endl;
	cout << "Program Terminated." << endl;
}