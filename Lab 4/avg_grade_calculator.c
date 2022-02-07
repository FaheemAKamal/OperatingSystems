//Faheem Kamal
// Lab 4: Task 2: avg_grade_calculator.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
int main() {
    int director = fork();
    if (director == 0) {
        printf("\nDirector says: I am the Director process.\n\n");

        int arr[10][4];                             //Array that stores data 10 rows (x) by 4 columns (y)

        FILE *f;
        f = fopen("file.txt", "r");                 // Read Mode Open File

        for (int i = 0; i < 10; ++i) {              // Read Contents of File and store in Array
            for (int j = 0; j < 4; ++j) {
                fscanf(f, "%d", &arr[i][j]);
            }
        }      
        int max_row = 0;
        printf("1  \t2  \t3  \t4   <-- Homework #\n\n");
        for (int i = 0; i < 10; ++i) {              // Print Array
            for (int j = 0; j < 4; ++j) {
                if (arr[i][j] < 10) {
                    printf("%d  \t", arr[i][j]);
                }
                else {
                    printf("%d \t", arr[i][j]);
                }
                ++max_row;
                if (max_row % 4 == 0) {
                    printf("\n");
                }
            }
        }
        printf("\n");
        int manager1 = fork();                      // Manager 1 process
        if (manager1 == 0) {
            int worker1 = fork();                   // Worker 1 process
            if (worker1 == 0) {
                int sum1 = 0;
                for (int i = 0; i < 10; ++i) {
                    sum1 += arr[i][0];
                }
                float average1 = ((double)sum1) / 10;
                printf("Worker 1 says: Homework 1 average = %.2f\n", average1);
                exit(0);
            }
            int worker2 = fork();                   // Worker 2 process
            if (worker2 == 0) {
                int sum2 = 0;
                for (int i = 0; i < 10; ++i) {
                    sum2 += arr[i][1];
                }
                float average2 = ((double)sum2) / 10;
                printf("Worker 2 says: Homework 2 average = %.2f\n", average2);
                exit(0);
            }

            else {
                waitpid(worker1, NULL, 0);
                waitpid(worker2, NULL, 0);
                exit(0);
            }
        }
        int manager2 = fork();                  // Manager 2 process
        if (manager2 == 0) {
            int worker3 = fork();               // Worker 3 process
            if (worker3 == 0) {
                int sum3 = 0;
                for (int i = 0; i < 10; ++i) {
                    sum3 += arr[i][2];
                }
                float average3 = ((double)sum3) / 10;
                printf("Worker 3 says: Homework 3 average = %.2f\n", average3);
                exit(0);
            }
            int worker4 = fork();               // Worker 4 process
            if (worker4 == 0) {
                int sum4 = 0;
                for (int i = 0; i < 10; ++i) {
                    sum4 += arr[i][3];
                }
                float average4 = ((double)sum4) / 10;
                printf("Worker 4 says: Homework 4 average = %.2f\n", average4);
                exit(0);
            }
            else {
                waitpid(worker3, NULL, 0);
                waitpid(worker4, NULL, 0);
                exit(0);
            }
        }
        else {
            waitpid(manager1, NULL, 0);
            waitpid(manager2, NULL, 0);
            exit(0);
        }
        fclose(f);
    }   
    else {
        waitpid(director, NULL, 0);
        printf("\nParent says: I am ending the program.\n\n");
    }
    return 0;
}