// Faheem Kamal
// CSC 33200
// Lab 3: Task 1: date_time_process.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	// Create child process
    int date_time_child = fork();          
    if (date_time_child == 0) {
        printf("\nI am the child process that will get the date and time. My PID is %d.\n\n", getpid());
		// Child process is executing date command
        execl("/bin/date", "date", (char *)0);          
    }
    else {
        waitpid(date_time_child, NULL, 0);
		// Parent waits for child to complete and ends program
        printf("\nI am the parent process. Ending program now.\n\n");       
    }



    return 0;
}