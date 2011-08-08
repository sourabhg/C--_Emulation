#include "Animals.hpp"


void delet_dog(Animal *a)
{
  free(a);
 // printf("\n Dog died \n");
}
void delet_poodle(Animal *a)
{
  free(a);
  //printf("\n Poodle Died \n");
}
void delet_fish(Animal *a)
{
  free(a);
  //printf("\n Fish Died \n");
}
void fetch_dog(Dog *)
{
  printf("\n Fetching \n");
}
void talk_dog(Animal *)
{
  printf("\n Woof \n");
}
void talk_poodle(Animal *)
{
  printf("\n Yap... \n");
}
void swim_fish(Fish *)
{
  printf("\n Swimming... \n");
}
void talk_fish(Animal *)
{
  printf("\n Gurgle... \n");
}
void primp_poodle(Poodle *)
{
  printf("\n Primping... \n");
}

Dog *Dog_new(const char *name, int tag)
{
  Dog *in_dog = (Dog *)malloc(sizeof (Dog));
  char *temp = (char *) malloc (sizeof(strlen(name)+1));
  strcpy(temp,name);
  printf("\n copied %s \n",temp);
  in_dog->animal.type = 1;
  in_dog->animal.type_name = "dog";
  in_dog->animal.number_of_legs = 4;
  in_dog->dog_tag_number = tag;
  in_dog->name = temp;
  //memcpy(name,in_dog->name,sizeof(strlen(name)+1));
  in_dog->fetch = &fetch_dog;
  //printf("\n Dog born %s %d\n",in_dog->name,in_dog->dog_tag_number);
  in_dog->animal.talk = &talk_dog;
  in_dog->animal.delet = &delet_dog;
  
  return in_dog;
}

Fish *Fish_new()
{
  Fish *in_fish = (Fish *)malloc(sizeof(Fish));
  in_fish->animal.type = 2;
  in_fish->animal.type_name ="fish";
  in_fish->animal.number_of_legs = 0;
  //printf("\n Fish Born \n ");
  in_fish->animal.talk = &talk_fish;
  in_fish->swim = &swim_fish;
  in_fish->animal.delet = &delet_fish;
  return in_fish;

}

Poodle *Poodle_new(const char  *name, int tag,const char *groomer)
{
  Poodle *in_poodle = (Poodle *)malloc(sizeof(Poodle));
  in_poodle->dog.animal.type = 3;
  in_poodle->dog.animal.type_name = "poodle";
  in_poodle->dog.animal.number_of_legs = 4;
  in_poodle->dog.name = name;
  in_poodle->dog.dog_tag_number = tag;
  in_poodle->groomer = groomer;
  //printf("\n Poodle Born \n");
  in_poodle->dog.animal.talk = &talk_poodle;
  in_poodle->primp = &primp_poodle;
  in_poodle->dog.fetch = &fetch_dog;
  in_poodle->dog.animal.delet = &delet_poodle;
  return in_poodle;
}

Dog *Animal_downcast_Dog(Animal *a)
{
  //printf("\n a->type_name %s \n",a->type_name);
  if(a->type_name == "dog")
  {
  return (Dog *) a;
  }
  else if(a->type_name == "poodle")
  {
    printf("\n Here \n");
    return (Dog *) a; 
  }
  else
  { 
   return NULL;
  }
}

Poodle *Animal_downcast_Poodle(Animal *a)
{
  if(a->type_name == "poodle")
  {
  return (Poodle *) a;
  }
  else
  { 
   return NULL;
  }
}

Poodle *Dog_downcast_Poodle(Dog *d)
{
  if(d->animal.type_name == "poodle")
  {
  return (Poodle *) d;
  }
  else
  { 
   return NULL;
  }
}
Fish *Animal_downcast_Fish(Animal *a)
{
  if(a->type_name == "fish")
  {
  return (Fish *) a;
  }
  else
  { 
   return NULL;
  }
}


