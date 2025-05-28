#include <stdlib.h>
#include <stdio.h>

typedef struct Animal Animal;

typedef struct AnimalVTable {
    void (*speak)(Animal* self);
    void (*destroy)(Animal* self);
} AnimalVTable;

struct Animal {
    AnimalVTable* vtable;
};

void Animal_speak(Animal* self);
void Animal_destroy(Animal* self);


static void animal_speak(Animal* self) {
    printf("Animal makes a sound\n");
}

static void animal_destroy(Animal* self) {
    free(self);
}

static AnimalVTable animal_vtable = {
    .speak = animal_speak,
    .destroy = animal_destroy
};

Animal* Animal_new() {
    Animal* a = malloc(sizeof(Animal));
    a->vtable = &animal_vtable;
    return a;
}

void Animal_speak(Animal* self) {
    self->vtable->speak(self);
}

void Animal_destroy(Animal* self) {
    self->vtable->destroy(self);
}


typedef struct Dog {
    Animal base;   // Inheritance via composition
    char* name;
} Dog;

Dog* Dog_new(const char* name);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void dog_speak(Animal* self) {
    Dog* dog = (Dog*)self;Dog_new
    printf("%s says Woof!\n", dog->name);
}

static void dog_destroy(Animal* self) {
    Dog* dog = (Dog*)self;
    free(dog->name);
    free(dog);
}

static AnimalVTable dog_vtable = {
    .speak = dog_speak,
    .destroy = dog_destroy
};

Dog* Dog_new(const char* name) {
    Dog* d = malloc(sizeof(Dog));
    d->base.vtable = &dog_vtable;
    d->name = strdup(name);
    return d;
}

typedef struct Cat {
    Animal base;
    char *name;
}Cat;


static void cat_speak(Animal *self){
    Cat *cat = (Cat *)self;
    printf("%s say moew\n", cat->name);
}
static void cat_destroy(Animal*self){
    Cat *cat = (Cat *)self;
    free(cat->name);
    free(cat);
}
static AnimalVTable cat_vtable = {
    .speak = cat_speak,
    .destroy = cat_destroy
};

Cat *cat_new(const void *name){
    Cat * c=malloc(sizeof(Cat));
    c->base.vtable = &cat_vtable;
    c->name = strdup(name);
    return c;
}


int main() {
    Animal* a = Animal_new();
    Animal* d = (Animal*)Dog_new("Rex");
    Animal *c = (Animal *)cat_new("lucy");
    Animal_speak(a); // Output: Animal makes a sound
    Animal_speak(d); // Output: Rex says Woof!
    Animal_speak(c); // Output: Rex says Woof!

    Animal_destroy(a);
    Animal_destroy(d);
    Animal_destroy(c);
    return 0;
}
