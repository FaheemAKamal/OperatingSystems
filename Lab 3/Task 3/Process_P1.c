// Faheem Kamal
// CSC 33200
// Lab 3: Task 3: Process_P1.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    printf("\nProcess_P1.c says:\n");
    int fd1;
	// Creating and/or opening destination1.txt
    fd1 = open("destination1.txt", O_RDWR | O_CREAT);               
    if (fd1 > 0) {
        printf("\tFile destination1.txt created.\n");
    }
    else {
        printf("\t%d: Error: could not create/open destination1.txt\n", fd1);
    }
    int fd2;
	// Creating and/or opening destination2.txt
    fd2 = open("destination2.txt", O_RDWR | O_CREAT);               
    if (fd2 > 0) {
        printf("\tFile destination2.txt created.\n\n");
    }
    else {
        printf("\t%d: Error: could not create/open destination2.txt\n\n", fd2);
    }
    return 0;
}