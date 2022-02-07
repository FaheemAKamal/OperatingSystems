// Faheem Kamal
// CSC 33200
// Lab 3: Task 3: Process_P2.c

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    printf("Process_P2.c says:\n\tWriting data into destination files...");
    // Define files being operated on
    char *sourcefile = "source.txt";
    char *destinationfile1 = "destination1.txt";
    char *destinationfile2 = "destination2.txt";
    // sb to be used to get size of data
    struct stat sb;
    // Buffers to store read data in
    char read_data1[100];
    char read_data2[50];
    // Storing results of read system calls
    int did_read1;
    int did_read2;
    // Try to get size of source file
    if (stat(sourcefile, &sb) == -1) {
        printf("-1: Error: could not get size of source file.\n");
        perror("Reason");
    }
    else {
        size_t size = sb.st_size;                               // Get size of source file
        int fd = open(sourcefile, O_RDONLY);                    // Open source file in read mode
        int fd2 = open(destinationfile1, O_RDWR | O_CREAT);     // Open destination1 file in read/write mode
        int fd3 = open(destinationfile2, O_RDWR | O_CREAT);     // Open destination2 file in read/write mode
        int num_loops = size / 150;                             // Determine number of times to read 150 bytes
        int remainder = size % 150;                             // Determine remainder when less than 150 bytes are left
        for (int i = 0; i < num_loops; ++i) {                   // Loop until num_loops for reading full sets of 150 bytes            
            did_read1 = read(fd, read_data1, 100);              // Read 100 bytes
            for (int j = 0; j < 100; ++j) {                     // Loop through the data just read, changing all 1s to As
                if (read_data1[j] == '1') {
                    read_data1[j] = 'A';
                }
            }
            did_read2 = read(fd, read_data2, 50);               // Read 50 bytes
            for (int j = 0; j < 50; ++j) {                      // Loop through the data just read, changing all 2s to Bs
                if (read_data2[j] == '2') {
                    read_data2[j] = 'B';
                }
            }
            write(fd2, read_data1, 100);            // Write the 100 bytes from read_data1 to destination1.txt
            write(fd3, read_data2, 50);             // Write the 50 bytes from read_data2 to destination2.txt
        }
        char remainder_data_2_B[50];                        // Declare first new buffer to read/write remaining data
        did_read2 = read(fd, remainder_data_2_B, 50);       // Read 50 bytes of the remaining data
        for (int i = 0; i < 50; ++i) {                      // Loop through the data just read, changing all 2s to Bs
            if (remainder_data_2_B[i] == '2') {
                remainder_data_2_B[i] = 'B';
            }
        }
        write(fd3, remainder_data_2_B, 50);                 // Write the remaining bytes to destination2.txt
        char remainder_data_1_A[remainder - 50];                        // Declare second new buffer to read/write remaining data
        did_read2 = read(fd, remainder_data_1_A, remainder - 50);       // Read all remaining data
        for (int i = 0; i < (remainder - 50); ++i) {                    // Loop through the data just read, changing all 1s to As
            if (remainder_data_1_A[i] == '1') {
                remainder_data_1_A[i] = 'A';
            }
        }      
        write(fd2, remainder_data_1_A, remainder - 50);                 // Write the remaining bytes to destination1.txt
        int did_close = close(fd);
        int did_close2 = close(fd2);
        int did_close3 = close(fd3);                // Close all files
        printf("\n\tData has been written.\n\n");
    } 
    return 0;
}
