// Faheem Kamal
// Lab 4: Task 1: command_interpreter.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void clr(char* input, char* c, char** args, int n, int fL) {
	if (args) {
		for (int i = 0; i < n; ++i) {
			if (args[i])
				free(args[i]);
			args[i] = NULL;
		}
	}
	if (input) 
		free(input);
	if (args && fL)
		free(args);
	if (c)
		free(c);
}
int main(int argc, char** argv) {
	int j = 0;
	int status;
	char* ptr = NULL;
	char* tmp = NULL;
	char* input = (char*) calloc(1025, sizeof(char));
	char* cwd = (char*) calloc(1024, sizeof(char));
	char** args = (char**) calloc(1024 / 64, sizeof(char*));
	printf("interpreter: ");
	while (fgets(input, 1024, stdin)) {
		input[strlen(input) - 1] = '\0';
		tmp = input;
		if (strcmp(input, "\0") == 0)		// If nothing was entered by User
			continue;
		for (j = 0, ptr = strtok(tmp, " "); ptr; ptr = strtok(NULL, " "), j++) {	// Take each input and put it in an array
			args[j] = (char*)calloc(65, sizeof(char));
			strcpy(args[j], ptr);
		}		
		if (strcmp(args[0], "quit") == 0) 		// If quit was entered
			break;		
		else if (strcmp(args[0], "cd") == 0) {	// If cd is entered, change the directory
			chdir((args[1]) ? args[1] : getenv("HOME"));
			for (int i = 0; i < j; ++i) {
				if (args[i])
					free(args[i]);
				args[i] = NULL;
			}
			printf("interpreter: ");
			continue;
		}		
		int child_exec = fork();	// Use fork child process to execute command		
		if (child_exec == 0) {		// True for child process
			if (execvp(args[0], args) == -1)
				perror("ERROR");
			clr(input, cwd, args, j, 1);
			exit(0);
		}
		else if (child_exec > 0) {	// True for parent process
			waitpid(child_exec, &status, 0);
			clr(NULL, NULL, args, j, 0);
		} 
		else 
			perror("ERROR");			
		printf("interpreter: ");
	}	
	printf("\n\nQuitting interpreter...\n\n");
	clr(input, cwd, args, 1, 1);
	return 0;
}
