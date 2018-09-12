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
 
 #define READ_END	 0
 #define WRITE_END	 1
 #define BUFFER_SIZE sizeof(buf)
 
 using namespace std;
 
 int buf[2];
 
 int main(int argc, char *argv[]) {
	 int num;
	 int fd[2];
	 int pid, pid_2;
	 int max1 = -1, max2 = -1;
	 int min1 = 1001, min2 = 1001;
	 int omax, omin;

	if (argc < 4) {
		fprintf(stderr, "Expected number of arguments is 3");
		return 1;
	}

	cout << "Program name is: " << argv[0] << endl;

	for (int k = 1; k < argc; k++) {
		cout << "(Next) Argument is: " << argv[k] << endl;
	}
	
	 int seed1 = *argv[1];
	 int seed2 = *argv[2];
	 int numrand = *argv[3];
 
	if (pipe(fd) == -1) {
		fprintf(stderr, "Pipe failed");
	}

	if ((pid = fork()) == 0) {
		srand(seed1);
			
		/* CHILD PROCESS */
		for (int c = 0; c < numrand; c++) { /* For-loop to generate 20 random numbers */
			num = rand() % 1000; /* Makes the random numbers between 0 - 1000 */

			cout << "Child ID: " << getpid() << ", number generated is " << num << endl;
					
			/* closing the unused end */
			close(fd[READ_END]);

			/* write to the pipe */
			write(fd[WRITE_END], &num, sizeof(num));
		}
			
		/* Close unused end*/
		close(fd[WRITE_END]);
			
		cout << "[Child] Child ID: " << getpid() << " Done! Terminating and joining the parent" << endl;
		exit(0);
		}
	else if (pid < 0) {
		fprintf(stderr, "Fork error");
		exit(1);
	}	
		
	if (pid > 0) {
	
		/* PARENT PROCESS */
		
		/* Close unused end*/
		close(fd[WRITE_END]);

		/* read from the pipe */
		read(fd[READ_END], &num, sizeof(num));
		cout << "[Parent] received number: " << num << " from Child ID: " << getpid() << endl;

		if (num > max1)
			max1 = num;
		if (num < min1)
			min1 = num;
		
		/* close unused end */
		close(fd[WRITE_END]);

		wait(NULL);
		cout << "[Parent] Child ID: " << getpid() << " minimum received is " << min1
			<< ", and maximum is " << max1 << "." << endl;
			
		if ((pid_2 = fork()) == 0) {
			srand(seed2);
			
			/* CHILD PROCESS */
			for (int c = 0; c < numrand; c++) { /* For-loop to generate 20 random numbers */
				num = rand() % 1000; /* Makes the random numbers between 0 - 1000 */

				cout << "Child ID: " << getpid() << ", number generated is " << num << endl;
					
				/* closing the unused end */
				close(fd[READ_END]);

				/* write to the pipe */
				write(fd[WRITE_END], &num, sizeof(num));
			}
			
			/* Close unused end*/
			close(fd[WRITE_END]);
			
			cout << "[Child] Child ID: " << getpid() << " Done! Terminating and joining the parent" << endl;
			exit(0);
		}
		else if (pid_2 < 0) {
			fprintf(stderr, "Fork error");
			exit(1);
		}
		if (pid_2 > 0) {
		
			/* PARENT PROCESS */
		
			/* Close unused end*/
			close(fd[WRITE_END]);

			/* read from the pipe */
			read(fd[READ_END], &num, sizeof(num));
			cout << "[Parent] received number: " << num << " from Child ID: " << getpid() << endl;

			if (num > max2)
				max2 = num;
			if (num < min2)
				min2 = num;
			
			/* close unused end */
			close(fd[WRITE_END]);

			wait(NULL);
			cout << "[Parent] Child ID: " << getpid() << " minimum received is " << min2
				<< ", and maximum is " << max2 << "." << endl;
		}
		if (max1 > max2)
			omax = max1;
		else
			omax = max2;
		if (min1 < min2)
			omin = min1;
		else 
			omin = min2;
			
		cout << "[Parent] The minimum of all numbers received is " << omin << "." << endl;
		cout << "[Parent] The maximum of all numbers received is " << omax << "." << endl;
	}
return 0;
}
  
	
   

