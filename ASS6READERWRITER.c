#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

// Function prototypes
void* reader(void* arg);
void* writer(void* arg);

// Shared buffer and flag
int buffer;
int flag = 0;      // Flag to indicate if buffer has data to be read
int read_count = 0; // Count of active readers

// Mutexes for mutual exclusion
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wrt = PTHREAD_MUTEX_INITIALIZER;

// Function to get input for buffer from user
int getbuff() {
    int temp;
    printf("Enter the number to add to buffer: ");
    scanf("%d", &temp);
    return temp;
}

// Function to display buffer contents
void readbuff(int buffer) {
    printf("Element read by reader = %d\n", buffer);
}

int main() {
    pthread_t writer_thread, reader_thread1, reader_thread2;

    // Creating writer and reader threads
    pthread_create(&writer_thread, NULL, writer, NULL);
    pthread_create(&reader_thread1, NULL, reader, NULL);
    pthread_create(&reader_thread2, NULL, reader, NULL);

    // Waiting for threads to finish
    pthread_join(writer_thread, NULL);
    pthread_join(reader_thread1, NULL);
    pthread_join(reader_thread2, NULL);

    return 0;
}

// Writer function to write to buffer
void* writer(void* arg) {
    while (1) {
        pthread_mutex_lock(&wrt); // Lock wrt mutex for exclusive access

        if (flag == 0) { // Write only if buffer is empty
            buffer = getbuff();
            flag = 1; // Indicate buffer has data
        }

        pthread_mutex_unlock(&wrt); // Release wrt mutex
    }
}

// Reader function to read from buffer with reader priority
void* reader(void* arg) {
    while (1) {
        // Reader entry section
        pthread_mutex_lock(&mutex1); 
        read_count++;
        if (read_count == 1) { // First reader locks wrt
            pthread_mutex_lock(&wrt);
        }
        pthread_mutex_unlock(&mutex1);

        // Reading section
        if (flag == 1) {
            readbuff(buffer); // Read buffer content
            sleep(1); // Simulate read delay
            flag = 0; // Mark buffer as empty after reading
        }

        // Reader exit section
        pthread_mutex_lock(&mutex1);
        read_count--;
        if (read_count == 0) { // Last reader unlocks wrt
            pthread_mutex_unlock(&wrt);
        }
        pthread_mutex_unlock(&mutex1);
    }
}
dityagawas@adityagawas-VirtualBox:~$ ^[[200~gcc producer.c -o producer
gcc: command not found
adityagawas@adityagawas-VirtualBox:~$ ~gcc read.c -o read
Command '~gcc' not found, did you mean:
  command 'gcc' from deb gcc (4:14.1.0-2ubuntu1)
  command 'cgcc' from deb sparse (0.6.4-4ubuntu3)
Try: sudo apt install <deb name>
adityagawas@adityagawas-VirtualBox:~$ gcc read.c -o read
adityagawas@adityagawas-VirtualBox:~$ ./read
Enter the number to add to buffer: 1
Element read by reader = 1
Element read by reader = 1
Enter the number to add to buffer: 2
Element read by reader = 2
Element read by reader = 2
Enter the number to add to buffer: 3
Element read by reader = 3
Element read by reader = 3
Enter the number to add to buffer: 

