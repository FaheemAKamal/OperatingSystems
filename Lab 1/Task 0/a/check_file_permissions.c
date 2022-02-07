#include <stdio.h>
#include <unistd.h>
#include <errno.h>

// Faheem Kamal: Program to check the permissions of the file 

// F_OK: Does file exist?
// R_OK: Can file be read?
// W_OK: Can file be written to?
// X_OK: Can file be executed?

int main(int argc, char *argv[]) {

    if (argv[1] == NULL) {
        printf("No File given in the argument. Please enter the name of a file as an argument.\n\n");
    }
    else {
        char *filepath = argv[1];
        int returnval;
        // Check if the file exists
        returnval = access(filepath, F_OK);
        // If access() returns 0, file exists
        if (returnval == 0) {
            printf("\n%s exists.\n\n", filepath);
        }
        else {
            // ENOENT: File does not exist
            if (errno == ENOENT) {
                printf("\n%s does not exist.\n\n", filepath);
            }
            // EACCES: File exists, but does not have proper permission
            else if (errno == EACCES) {
                printf("\n%s is not accessible.\n\n", filepath);
            }
        }
        // Check if the file has read permission
        returnval = access(filepath, R_OK);
        // If access() returns 0, the file has read permission
        if (returnval == 0) {
            printf("\n%s has read permission.\n\n", filepath);
        }
        else {
            // ENOENT: File does not exist
            if (errno == ENOENT) {
                printf("\n%s does not exist.\n\n", filepath);
            }
            // EACCES: File exists, but does not have proper permission
            else if (errno == EACCES) {
                printf("\n%s does not have read permission.\n\n", filepath);
            }
        }
        // Checking if the file has write permission
        returnval = access(filepath, W_OK);
        // If access() returns 0, file has write permission
        if (returnval == 0) {
            printf("\n%s has write permission.\n\n", filepath);
        }
        else {
            // ENOENT: File does not exist
            if (errno == ENOENT) {
                printf("\n%s does not exist.\n\n", filepath);
            }
            // EACCES: File exists, but does not have proper permission
            else if (errno == EACCES) {
                printf("\n%s does not have write permission.\n\n", filepath);
            }
        }
    }
    return 0;
}