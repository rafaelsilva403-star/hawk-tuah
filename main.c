#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

struct thread {
    pthread_t id;
    long runtime;
    bool running;
};



void value(int* value) { value[0]++; }

void* func(void *arg) {

    int* i = (int*) arg;

    fflush(stdout);
    if(arg == NULL) {
        printf("arg is NULL");
        exit(1);
    }
    
    while(i[0] < 10) {
        fflush(stdout);
        value(i);
        printf("Thread value1: %i\n", i[0]);
    }

    printf("Thread1 finished\n");
    return NULL;
}

void* func2(void *arg) {

    int* i = (int*) arg;

    fflush(stdout);
    if(arg == NULL) {
        printf("arg is NULL");
        exit(1);
    }

    while(i[0] < 20) {
        fflush(stdout);
        value(i);
        printf("Thread2 value: %i\n", i[0]);
    }

    printf("Thread2 finished\n");
    return NULL;
}

void create_thread(struct thread* t, void* (*func)(void*), void* arg) {
    if(t->id) {
        perror("thread already created");
        exit(1);
    }

    pthread_create(&t->id, NULL, func, arg);

    if(!t->id) {
        perror("thread creation failed");
        exit(1);
    }
}

void run_thread(struct thread* t) {
    if(!t->id) {
        perror("thread not created");
        exit(1);
    }

    printf("Throwing thread...\nThread response: \n");
    t->running = true;
    pthread_join(t->id, NULL);
}

int main() {
    
    printf("Hello, World!\n");

    int* meow = malloc(sizeof(int));
    struct thread* t1 = malloc(sizeof(struct thread));
    struct thread* t2 = malloc(sizeof(struct thread));

    create_thread(t1, func, meow);
    create_thread(t2, func2, meow);

    run_thread(t1);
    run_thread(t2);

    int i = 0;

    while(i < 10) {
        printf("Main value: %i\n", i);
        i++;
    }

    printf("Main Thread finished\n");

    free(meow);
    free(t1);
    free(t2);
    
    printf("Goodbye, World!\n");
    return 0;
}