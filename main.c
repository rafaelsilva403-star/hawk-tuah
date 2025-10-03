#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct thread {
    pthread_t id;
    long runtime;
};



void value(int* var) {
    var++;
}

void func(void *arg) {
    fflush(stdout);
    value((int*)arg);
    printf("value: %i\n", *(int*)arg);
}
void create_thread(struct thread* t, void* (*func)(void*), void* arg) {
    pthread_create(&t->id, NULL, func, arg);
}

void run_thread(struct thread* t) {
    pthread_join(t->id, NULL);
}

int main() {
    
    int* meow = malloc(sizeof(int));
    struct thread* t = malloc(sizeof(struct thread));
    create_thread(t, (void* (*)(void*))value, meow);
    run_thread(t);
    free(meow);
    free(t);

    return 0;
}