#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

struct thread {
    pthread_t id;
    long runtime;
    bool running;
};



void value(int* var) {
    if(var == NULL) {
        printf("var is NULL");
        exit(1);
    }

    var[0]++;
}

void* func(void *arg) {
    fflush(stdout);
    if(arg == NULL) {
        printf("arg is NULL");
        exit(1);
    }
    
    while(*((int*)arg) < 10) {
        fflush(stdout);
        value((int*)arg);
        printf("Thread value: %i\n", *((int*)arg));
    }

    printf("Thread finished\n");
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
    struct thread* t = malloc(sizeof(struct thread));
    create_thread(t, (void* (*)(void*))func, meow);
    run_thread(t);
   
    int i = 0;

    while(i < 10) {
        printf("Main value: %i\n", i);
        i++;
    }

    printf("Main Thread finished\n");

    free(meow);
    free(t);
    
    printf("Goodbye, World!\n");
    return 0;
}