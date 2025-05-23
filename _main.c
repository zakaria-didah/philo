#include "philo.h"

typedef union _main
{
    int x;
    char y;
    float z;
} t_main;



int main(int argc, char **argv)
{
    t_main main;
    main.x = 42;
    main.y = 'A';
    main.z = 3.14;
    printf("x: %d\n", main.x);
    printf("y: %c\n", main.y);
    printf("z: %f\n", main.z);
    return (0);


}