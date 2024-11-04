#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX 20

// Function to sort array in ascending order using bubble sort
void bubble_asc(int arr[], int n) { 
    int i, j, temp;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { // Swap if the element is greater than the next
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to sort array in descending order using bubble sort
void bubble_dsc(int arr[], int n) { 
    int i, j, temp;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) { // Swap if the element is smaller than the next
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print array elements
void print(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("\t%d", arr[i]);
    }
    printf("\n\n");
}

int main() {
    int i, n, arr[MAX], f, pid;

    // Input the number of elements in the array and the array elements
    printf("\nHOW MANY NUMBERS DO YOU WANT IN ARRAY: ");
    scanf("%d", &n);
    printf("ENTER ARRAY ELEMENTS: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Create a child process using fork
    pid = fork();

    // Child process (pid == 0) sorts the array in ascending order and demonstrates orphan state
    if (pid == 0) {
        printf("\n\t\t**********ORPHAN STATE**************\n");
        sleep(5); // Wait to potentially become an orphan if parent terminates

        printf("\n\t CHILD PROCESS PID: %d", getpid());
        printf("\n\t PARENT PROCESS PPID: %d", getppid());
        system("ps -el | grep init"); // Check if child is adopted by init

        printf("\n\nARRAY IN ASCENDING ORDER: ");
        bubble_asc(arr, n);
        print(arr, n);
    } 
    // Parent process (pid > 0) sorts the array in descending order and demonstrates zombie state
    else if (pid > 0) {
        printf("\n\t\t\t**********ZOMBIE STATE**************\n");
        system("ps -el | grep Z"); // Display any zombie processes

        f = wait(0); // Wait for child to finish, prevents child from becoming zombie
        printf("\n\tTERMINATED CHILD PID: %d", f);
        printf("\n\tPARENT PID (MAIN): %d", getpid());
        printf("\n\tPARENT'S PARENT PPID (BASH): %d", getppid());

        printf("\n\nARRAY IN DESCENDING ORDER: ");
        bubble_dsc(arr, n);
        print(arr, n);
    } 
    // If fork failed, print error message
    else {
        printf("\nERROR IN FORK!!");
    }
    
    return 0;
}
HOW MANY NUMBERS DO YOU WANT IN ARRAY: 5
ENTER ARRAY ELEMENTS: 2 4 1 5 3

			**********ZOMBIE STATE**************

		**********ORPHAN STATE**************
F S   UID     PID    PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD


	 CHILD PROCESS PID: 4941
	 PARENT PROCESS PPID: 4938

ARRAY IN ASCENDING ORDER: 	1	2	3	4	5


	TERMINATED CHILD PID: 4941
	PARENT PID (MAIN): 4938
	PARENT'S PARENT PPID (BASH): 4192

ARRAY IN DESCENDING ORDER: 	5	4	3	2	1

adityagawas@adityagawas-VirtualBox:~$ 
adityagawas@adityagawas-VirtualBox:~$ 


