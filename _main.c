#include <stdio.h>

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

int main()
{
    struct Tree TreeB;
    TreeB = TreeA;
    TreeB.FPprint();
    return 0;
}
