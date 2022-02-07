// Faheem Kamal
// CSC 33200
// Lab 3: Task 2: list_all_files_process.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

	// Creating child process
    int all_files_child = fork();       

    if (all_files_child == 0) {
        printf("\nI am the child process that will list all files and their information. My PID is %d.\n\n", getpid());
        char *args[] = {"ls", "-a", "-l", (char *)0};
		// Child process is executing ls command with arguments
        execvp(args[0], args);          
    }
    else {
        waitpid(all_files_child, NULL, 0);
		// Parent waits for child to complete and ends program
        printf("\nI am the parent process. Ending program now.\n\n");       
    }



    return 0;
}