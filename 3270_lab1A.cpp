/*  Joseph Hein
 *  CS3270 Lab1A
 *
 *
 *
 *
 */
 
 #include <iostream>
 #include <stdio.h>
 #include <sys/types.h>
 #include <unistd.h>
 #include <stdlib.h>
 
 using namespace std;
 
 int main() {
	int pid;
	int num;
	int max = -1;
	int min = 1001;
	
	cout << "*** This is the main" << endl;
	
	for (int k = 0; k < 2; ++k) { /* Runs through twice */
	
	if (pid < 0) { /* If shows up negative, error occured */
		cout << "Error!" << endl;
		exit(1);
	}
	else if ((pid = fork()) == 0) { /* Calls and assigns fork return to PID, then checks for child */
		/* CHILD PROCESS */
		srand((time(0) - getpid())); /* Takes time rand() and subtracts PID for different values*/
	for (int c = 0; c < 20; c++) { /* For-loop to generate 20 random numbers */
		num = rand() % 1000; /* Makes the random numbers between 0 - 1000 */
		cout << "Child ID: " << getpid() << ", number generated is " << num << endl;
		if (num > max) /* Checking value for new max */
			max = num;
		if (num < min) /* Checking value for new min */
			min = num;
	}
		cout << "[Child] Child ID: my minimum is " << min << ", and maximum is " << max << endl;
		cout << "[Child] Child ID: " << getpid() << " Done! Terminating and joining the parent" << endl;
		exit(0);
	}
	if (pid > 0) 
		/* PARENT PROCESS */
		wait(NULL);
		cout << "[Parent] Child ID; " << getpid() << " Termindated, good job child!" << endl;
	}
	
	return 0;
	}