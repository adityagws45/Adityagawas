#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 20

// Function declarations
void *producer(void *arg);
void *consumer(void *arg);

// Shared buffer structure with necessary semaphores and index counters
typedef struct {
    int buffer[BUFFER_SIZE];
    sem_t full, empty;     // Counting semaphores for buffer slots
    int in, out;           // Buffer index positions for producer/consumer
} shared_data;

shared_data sh;
sem_t mutex;               // Mutex for critical section

int main() {
    pthread_t ptid1, ptid2, ctid1;
    sh.in = 0;
    sh.out = 0;

    // Initialize semaphores
    sem_init(&sh.empty, 0, BUFFER_SIZE); // All slots empty initially
    sem_init(&sh.full, 0, 0);            // No slots full initially
    sem_init(&mutex, 0, 1);              // Mutex for critical section

    // Create producer and consumer threads
    pthread_create(&ptid1, NULL, producer, NULL);
    pthread_create(&ptid2, NULL, producer, NULL);
    pthread_create(&ctid1, NULL, consumer, NULL);

    // Wait for threads to complete
    pthread_join(ptid1, NULL);
    pthread_join(ptid2, NULL);
    pthread_join(ctid1, NULL);

    // Destroy semaphores
    sem_destroy(&sh.empty);
    sem_destroy(&sh.full);
    sem_destroy(&mutex);

    return 0;
}

// Producer function
void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100;        // Generate random item
        sem_wait(&sh.empty);         // Wait for empty slot
        sem_wait(&mutex);            // Lock critical section

        // Insert item into buffer
        sh.buffer[sh.in] = item;
        printf("PRODUCER Thread id = %ld produced Item = %d at index %d\n", pthread_self(), item, sh.in);
        sh.in = (sh.in + 1) % BUFFER_SIZE;

        sem_post(&mutex);            // Unlock critical section
        sem_post(&sh.full);          // Signal item produced

        sleep(1);                    // Simulate time to produce
    }
}

// Consumer function
void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&sh.full);          // Wait for full slot
        sem_wait(&mutex);            // Lock critical section

        // Remove item from buffer
        item = sh.buffer[sh.out];
        printf("\tCONSUMER Thread id = %ld consumed Item = %d from index %d\n", pthread_self(), item, sh.out);
        sh.out = (sh.out + 1) % BUFFER_SIZE;

        sem_post(&mutex);            // Unlock critical section
        sem_post(&sh.empty);         // Signal item consumed

        sleep(2);                    // Simulate time to consume
    }
}
adityagawas@adityagawas-VirtualBox:~$ gcc producer.c -o producer
adityagawas@adityagawas-VirtualBox:~$ ./producer
PRODUCER Thread id = 129265240639168 produced Item = 83 at index 0
PRODUCER Thread id = 129265230153408 produced Item = 86 at index 1
	CONSUMER Thread id = 129265219667648 consumed Item = 83 from index 0
PRODUCER Thread id = 129265230153408 produced Item = 77 at index 2
PRODUCER Thread id = 129265240639168 produced Item = 15 at index 3
PRODUCER Thread id = 129265230153408 produced Item = 93 at index 4
	CONSUMER Thread id = 129265219667648 consumed Item = 86 from index 1
PRODUCER Thread id = 129265240639168 produced Item = 35 at index 5
PRODUCER Thread id = 129265230153408 produced Item = 86 at index 6
PRODUCER Thread id = 129265240639168 produced Item = 92 at index 7
PRODUCER Thread id = 129265230153408 produced Item = 49 at index 8
PRODUCER Thread id = 129265240639168 produced Item = 21 at index 9
	CONSUMER Thread id = 129265219667648 consumed Item = 77 from index 2
PRODUCER Thread id = 129265230153408 produced Item = 62 at index 10
PRODUCER Thread id = 129265240639168 produced Item = 27 at index 11
PRODUCER Thread id = 129265230153408 produced Item = 90 at index 12
PRODUCER Thread id = 129265240639168 produced Item = 59 at index 13
	CONSUMER Thread id = 129265219667648 consumed Item = 15 from index 3
PRODUCER Thread id = 129265230153408 produced Item = 63 at index 14
PRODUCER Thread id = 129265240639168 produced Item = 26 at index 15
PRODUCER Thread id = 129265230153408 produced Item = 40 at index 16
PRODUCER Thread id = 129265240639168 produced Item = 26 at index 17
	CONSUMER Thread id = 129265219667648 consumed Item = 93 from index 4
PRODUCER Thread id = 129265230153408 produced Item = 72 at index 18
PRODUCER Thread id = 129265240639168 produced Item = 36 at index 19
PRODUCER Thread id = 129265230153408 produced Item = 11 at index 0
PRODUCER Thread id = 129265240639168 produced Item = 68 at index 1



if u face problem then 
gcc filename.c -o filename -pthread -lrt
./filename
