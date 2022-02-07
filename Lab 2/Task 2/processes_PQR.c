// Faheem Kamal

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    // Parent P
    int a = 10, b = 25, fq = 0, fr = 0;
	// Fork child Q
    fq = fork(); 
	// Only child Q will return true here
    if (fq == 0) { 
        a = a + b;
		// Child Q: a = 35
        printf("a = %d\n", a);
		// Child Q: b = 25
        printf("b = %d\n", b);  
		// Child Q PID
        printf("I am child Q, my pid = %d\n", getpid());  
		// Fork child R
        fr = fork();    
		// Child R should not return true here, child Q should
        if (fr != 0) {  
            b = b + 20;   
			// Child Q: a = 35
            printf("a = %d\n", a);  
			// Child Q: b = 45
            printf("b = %d\n", b); 
			// Child Q PID
            printf("I am still child Q, my pid = %d\n", getpid());  
        }
        else {          
			// Child R should return true here
            a = (a * b) + 30;
			// Child R: a = (35 * 25) + 30 = 905
            printf("a = %d\n", a); 
			// Child R: b = 25
            printf("b = %d\n", b);  
			// Child R PID
            printf("I am child R, my pid = %d\n", getpid()); 
        }
    }
    else { 
		// The parent should return true here
        b = a + b - 5;
		// Parent: a = 10
        printf("a = %d\n", a);
		// Parent: b = 30
        printf("b = %d\n", b);  
		// Parent PID
        printf("I am the parent, my pid = %d\n", getpid()); 
    }
    return 0;
}