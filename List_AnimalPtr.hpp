#ifndef List_AnimalPtr_hpp
#define List_AnimalPtr_hpp
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Animals.hpp"

typedef struct node{
   Animal *node_animal;
   struct node *next,*prev; 
}node;

typedef struct my_iterator
{
 node *new_node;
 void (*inc)(my_iterator *);
 void (*dec)(my_iterator *);
 Animal* (*deref)(my_iterator *);
 
}List_AnimalPtr_Iterator;

typedef struct List_AnimalPtr{
 node *start;
 node *finish;
 void (*push_back) (List_AnimalPtr *,Animal *);
 List_AnimalPtr_Iterator (*begin) (List_AnimalPtr *);
 void (*insert) (List_AnimalPtr *,List_AnimalPtr_Iterator ,Animal *);
 void (*erase) (List_AnimalPtr *,List_AnimalPtr_Iterator);
 List_AnimalPtr_Iterator (*end) (List_AnimalPtr *); 
 void (*dtor) (List_AnimalPtr *);
}List_AnimalPtr;


void iterator_inc(List_AnimalPtr_Iterator *new_it);


void iterator_dec(List_AnimalPtr_Iterator *new_it);


void list_insert(List_AnimalPtr *l,List_AnimalPtr_Iterator new_it,Animal *a);

  


Animal* my_deref(List_AnimalPtr_Iterator *it);
 
List_AnimalPtr_Iterator list_begin(List_AnimalPtr *l);

List_AnimalPtr_Iterator list_end(List_AnimalPtr *l);




void list_push_back(List_AnimalPtr *l, Animal*a);


bool List_AnimalPtr_Iterator_equal(List_AnimalPtr_Iterator it1,List_AnimalPtr_Iterator it2);
   

void erase_animalptr_list(List_AnimalPtr *list,List_AnimalPtr_Iterator it1);
  

void destruct_list(List_AnimalPtr *l);

void List_AnimalPtr_ctor(List_AnimalPtr *l);



#endif 
