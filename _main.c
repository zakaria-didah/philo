#include "philo.h"
#include <stddef.h>
#include <string.h>

struct Node {
    int somevar;
};

void print() {
    printf("Hello from an object-oriented C method!");
};

struct Tree {
    struct Node * NIL;
    void (*FPprint)(void);
    struct Node *root;
    struct Node NIL_t;
} TreeA = {&TreeA.NIL_t,print};

pthread_mutex_t A;
pthread_mutex_t B;

void voo(){
    pthread_mutex_lock(&A);
    printf("shit happend\n");
}

void *r(void*s){
    printf("lock A %s\n", (char *)s);
    pthread_mutex_lock(&A);
    usleep(50);
    pthread_mutex_lock(&B);
    printf("shiiiiiiiiiit\n");
    return NULL;
    
}

void rr(void*s){
    

}


void clean(void *f){
    void *p =  *(void **)f;
    free(p);
    p = NULL;
}


int main()
{
    char *s = strdup("hi there");
    char *p;
    printf("%p\n", s);
    p = realloc(s, 20);
    // printf("%p\n", s);
    printf("%p\n", p);
    // strncpy(s, "hi there how are u?", 20);
    strncpy(p, "hi there how are u?", 20);
    printf("%s\n", s);
    printf("%s\n", p);




}
