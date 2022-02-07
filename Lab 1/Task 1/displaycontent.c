#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

//Faheem Kamal: Program to display contents of file provided in argument

int main(int argc, char* argv[]) {
    // Pass argument into the filepath variable
    char* filepath = argv[1];
    // Here, SB is used to get the size of File
    struct stat sb;
    // Here is a Buffer to store the read data in
    char* read_data;
    // Attempt to get the size of the File
    // Will give an error if it is necessary
    if (stat(filepath, &sb) == -1) {
        printf("-1: Error: could not get size of source file.\n");
        perror("Reason");
    }
    // Otherwise, get the size of File and proceed to open, read and print
    else {
        size_t size = sb.st_size;
        // Try to open the file
        int fd = open(filepath, O_RDONLY);
        // If error, print the error message
        if (fd < 0) {
            printf("%d: Error, could not open source file.\n", fd);
            perror("Access");
        }
        // Read from File and Print 
        else {
            // Read the File
            read_data = (char *) calloc(size, sizeof(char)); 
            int did_read = read(fd, read_data, size);
            // If there is an error, print the error message
            if (did_read < 0) {
                printf("%d: Error, could not read source file.\n", did_read);
                perror("Access");
            }
            // Otherwise, print the read data and close the File
            else {
                write(1, read_data, size);
                int did_close = close(fd);
            }
        }
    }
    return 0;
}