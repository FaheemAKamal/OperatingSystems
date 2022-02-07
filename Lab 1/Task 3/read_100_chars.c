#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

// Faheem Kamal: Program to read groups of 100 characters from source file.
// Replace every "1" with "A", add "XYZ" at end of the group.
// And write group to the destination file; both files are provided as arguments.

int main(int argc, char* argv[]) {
    // Pass the first argument into the sourcepath variable
    char* source_path = argv[1];
    // Pass the second argument into the destinationpath variable
    char* destination_path = argv[2];
    // sb to be used to get size of data
    struct stat sb;
    // Buffer to store the read data in
    char read_data[100];
    // Storing result of the read system call
    int did_read;

    // Attempt to get size of the source file
    // Give an error message if needed
    if (stat(source_path, &sb) == -1) {
        printf("-1: Error: Could not get size of the source file.\n");
        perror("Reason");
    }
    // Otherwise, get size of the source file and proceed to open.
    // Read and copy into the destination file
    else {
        size_t size = sb.st_size;
        // Try to open the file
        int fd = open(source_path, O_RDONLY);
        // If there is an error, print error message
        if (fd < 0) {
            printf("%d: Error: Could not open the source file.\n", fd);
            perror("Access");
        }
        // Otherwise, read from source file
        // And copy into destination file
        else {
            int fd2 = open(destination_path, O_RDWR | O_CREAT);
            // Determine number of times to read 100 bytes
            int num_loops = size / 100;           
            // Determine remainder when less than 100 bytes are left
            int remainder = size % 100;  
            // Loop until num_loops for reading full sets of 100 bytes
            for (int i = 0; i < num_loops; ++i) {       
                // Read 100 bytes
                did_read = read(fd, read_data, 100);
                // Loop through the data just read, changing all 1s to As
                for (int j = 0; j < 100; ++j) {         
                    if (read_data[j] == '1') {
                        read_data[j] = 'A';
                    }
                }
                // Write 100 bytes to the destination file
                write(fd2, read_data, 100);           
                // Write "XYZ" into destination file
                write(fd2, "XYZ", 3);                      
            }
            // Declare a new buffer to read/write remaining data
            char remainder_data[remainder];       
            // Read the remaining data
            did_read = read(fd, remainder_data, remainder);     
            // Loop through the data just read, changing all 1s to As
            for (int i = 0; i < remainder; ++i) {               
                if (remainder_data[i] == '1') {
                    remainder_data[i] = 'A';
                }
            }
            // Write the remaining bytes to destination file
            write(fd2, remainder_data, remainder);  
            // Write "XYZ" into destination file
            write(fd2, "XYZ", 3);                      
            
            // Close both files
            int did_close = close(fd);      
            int did_close2 = close(fd2);
        } 
    }
    return 0;
}
