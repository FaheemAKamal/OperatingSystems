//Faheem Kamal

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	// Declaring two child process variables
    pid_t childone;
    pid_t childtwo;
	// Process for Child one is created by Parent
    childone = fork(); 
	// Process for Child two is created by both Parent and Child one
    childtwo = fork();    
    // Because child one also ran this line, a grandchild process is created.
    if (childone == 0 && childtwo > 0) {            // Only child one will return true here
        printf("I am child one, my pid is %d.\n", getpid());
    }
    else if (childtwo == 0 && childone > 0) {       // Only child two will return true here
        printf("I am child two, my pid is %d.\n", getpid());
    }
    else if (childone > 0 && childtwo > 0) {        // Only parent will return true here
        waitpid(childone, NULL, 0);
        waitpid(childtwo, NULL, 0);
        printf("I am the parent, all child processes are terminated.\n");
    }
    return 0;
}