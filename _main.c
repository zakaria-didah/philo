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
t_data	*_data(void)
{
    static t_data	data = {0};

    return (&data);
}

void voo(){
    printf("%lld\n",_data()->start_time);
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

t_data *d = _data();
d->start_time = 1;
voo();



}
