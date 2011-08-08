#ifndef Animals_hpp
#define Animals_hpp
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

struct Animal{
 int type;
 const char *type_name;
 int number_of_legs;
 void (*talk) (Animal*);
 void (*delet) (Animal*);
};

struct Dog{
  Animal animal;
  int dog_tag_number;
  const char *name;
  void (*fetch) (Dog*);
};

struct Fish{
  Animal animal;
  void (*swim) (Fish *);
};

struct Poodle{
  Dog dog;
  const char *groomer;
  void (*primp) (Poodle *);
};

void delet_dog(Animal *a);

void delet_poodle(Animal *a);
void delet_fish(Animal *a);
void fetch_dog(Dog *);
void talk_dog(Animal *);
void talk_poodle(Animal *);
void swim_fish(Fish *);
void talk_fish(Animal *);
void primp_poodle(Poodle *);
Dog *Dog_new(const char *name, int tag);

Fish *Fish_new();

Poodle *Poodle_new(const char  *name, int tag,const char *groomer);

Dog *Animal_downcast_Dog(Animal *a);

Poodle *Animal_downcast_Poodle(Animal *a);

Poodle *Dog_downcast_Poodle(Dog *d);
Fish *Animal_downcast_Fish(Animal *a);

#endif
