#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

//Faheem Kamal: Program to open, create and open a File. Once open,write into it. And then, finally close it,
int main(int argc, char* argv[]) {
    // File descriptor variables provided below
    int fd;
    int did_close;
    char word[] = "Hello its a world created by something and someone";
    // Bitwise OR flag; the File is created and then opened.
    fd = open("destination.txt", O_RDWR | O_CREAT);
    // If less than 0, File cannot be opened
    if (fd < 0) {
        printf("%d: Error: could not open\n", fd);
        // Reason for not opening File
        perror("Access");
    }
    // If greater than 0, the File is accessed and opened
    else {
        printf("%d: Success, file opened\n", fd);
        // Write into the File
        write(fd, word, strlen(word));
        // Attempting to close File
        did_close = close(fd);
        // If less than 0, cannot close the File
        if (did_close < 0) {
            printf("%d: Error: could not close", did_close);
            // Reason for not closing the File
            perror("Reason");
        }
        // If greater than 0, the File id closed
        else {
            printf("%d: Success, file closed\n", did_close);
        }
    }
    return 0;
}