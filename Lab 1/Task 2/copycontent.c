#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

// Faheem Kamal: Program to copy contents of source file into destination file; both files are provided as arguments

int main(int argc, char* argv[]) {

    // Pass the first argument into the source path variable
    char* source_path = argv[1];
    // Pass the second argument into the destination path variable
    char* destination_path = argv[2];
    // SB to be used to get size of data
    struct stat sb;
    // Buffer to store read the data in
    char* read_data;

    // Attempt to get size of the File; give error if needed
    if (stat(source_path, &sb) == -1) {
        printf("-1: Error: could not get size of the source file.\n");
        perror("Reason");
    }
    // Otherwise, get the size of the File and proceed to open.
    // Read and copy into the destination file
    else {
        size_t size = sb.st_size;
        // Try to open file
        int fd = open(source_path, O_RDONLY);
        // If there is an error, print the error message
        if (fd < 0) {
            printf("%d: Error: could not open the source file.\n", fd);
            perror("Access");
        }
        // Read from the source File.
        // And copy into the destination File
        else {
            // Attempt to read the  File
            read_data = (char *) calloc(size, sizeof(char)); 
            int did_read = read(fd, read_data, size);
            // If there is an error, print the error message
            if (did_read < 0) {
                printf("%d: Error: could not read the source file.\n", did_read);
                perror("Access");
            }
            // Otherwise, copy read data into the destination File 
            // And close all the files
            else {
                // Create and/or open the destination File
                int fd2 = open(destination_path, O_RDWR | O_CREAT);
                // If there is an error, print the error message
                if (fd2 < 0) {
                    printf("%d: Error: could not open destination file.\n", fd2);
                    perror("Access");
                }
                // Otherwise, write data into thedestination File
                // And close all the Files
                else {
                    write(fd2, read_data, size);
                    int did_close = close(fd);
                    int did_close2 = close(fd2);
                }
            }
        } 
    }
    return 0;
}