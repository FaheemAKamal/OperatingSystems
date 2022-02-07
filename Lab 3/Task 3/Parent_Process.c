// Faheem Kamal
// CSC 33200
// Lab 3: Task 3: Parent_Process.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    printf("\nParent_Process.c says:\n\tI am the parent file.\n\n");
    sleep(2);

    int child1;
    int child2;
	// Fork child1 process for Process_P1.c
    child1 = fork();                

    // Only child1 will execute this if statement
    if (child1 == 0) {
        int compile_child_1 = fork();
        if (compile_child_1 == 0) {
            char *args[] = {"gcc", "Process_P1.c", "-o", "process1", NULL};
            execv("/usr/bin/gcc", args);
        }
        else {
            waitpid(compile_child_1, NULL, 0);
            char *args1[] = {"./process1", NULL};
            execv(args1[0], args1);
        }
    }

    else {
        waitpid(child1, NULL, 0);
        sleep(2);
		// Fork child2 process for Process_P2.c
        child2 = fork();            

        // Only child2 will execute this if statement
        if (child2 == 0) {
            int compile_child_2 = fork();
            if (compile_child_2 == 0) {
                char *args2[] = {"gcc", "Process_P2.c", "-o", "process2", NULL};
                execv("/usr/bin/gcc", args2);
            }
            else {
                waitpid(compile_child_2, NULL, 0);
                char *args3[] = {"./process2", NULL};
                execv(args3[0], args3);
            }
        }

        // Only the parent will execute this if statement
        else {
            waitpid(child2, NULL, 0);
            sleep(2);
            printf("Parent_Process.c says:\n\tI am the parent file and I am ending the program.\n\n");
        }
    }

    return 0;
}