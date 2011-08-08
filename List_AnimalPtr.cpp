#include "List_AnimalPtr.hpp"

void iterator_inc(List_AnimalPtr_Iterator *new_it)
{
    node *temp;
    temp = new_it->new_node;
    new_it->new_node = temp->next;
	//new_it->new_node = new_it->new_node->next;
    //printf("\n inc is :%s \n",new_it->new_node->node_animal->type_name);
}

void iterator_dec(List_AnimalPtr_Iterator *new_it)
{
//  static int count = 0;
 // count++;
  node *temp;
  //if(count > 1)
//	{
  temp = new_it->new_node;
  new_it->new_node = temp->prev;
//	}
  //new_it->new_node = new_it->new_node->prev;
  //printf("\n dec is :%s \n",new_it->new_node->node_animal->type_name);
 // printf("\n the count is : %d \n",count);
}

void list_insert(List_AnimalPtr *l,List_AnimalPtr_Iterator new_it,Animal *a)
{
  node *temp;
  temp = (node *)malloc(sizeof(node));
  temp->node_animal = a;
  temp->next = NULL;
  temp->prev = NULL;
  if(l->start->next == l->start)
	{
           l->start->next = temp;
           l->start->prev = temp;
           temp->next = l->start;
           temp->prev = l->start;
    //       printf("\n only one node \n");
     //      printf("\n Animal Added only one%s \n",a->type_name);
	}
  else  
  if(l->start->next == new_it.new_node)
	{
	//  printf("\n added at start called \n");
          
          l->start->next->prev = temp;
	  temp->next = l->start->next;
          l->start->next = temp;
          temp->prev = l->start;
          
	  //printf("\n Animal Added at start%s \n",a->type_name);
	}
  else if(l->start == new_it.new_node)
	{ 
	   //printf("\n added at end called \n");
           temp->prev = l->start->prev;
           l->start->prev = temp;
           temp->next = l->start;
           temp->prev->next = l->start;
           //printf("\n Animal Added at end%s \n",a->type_name);
	}
 
}

Animal* my_deref(List_AnimalPtr_Iterator *it) {
         Animal *animal = it->new_node->node_animal; 
         return (Animal *)animal;
      }

List_AnimalPtr_Iterator list_begin(List_AnimalPtr *l)
{ 
 //printf("going here");
  List_AnimalPtr_Iterator new_it;
  new_it.new_node = l->start->next;
  new_it.inc = &iterator_inc;
  new_it.dec = &iterator_dec;
  new_it.deref = &my_deref;
  //printf("\n Start is :%s \n",new_it.new_node->node_animal->type_name);
  return new_it;
}

List_AnimalPtr_Iterator list_end(List_AnimalPtr *l)
{ 
 //printf("going here");
  List_AnimalPtr_Iterator new_it;
  new_it.new_node = l->start;
  new_it.inc = &iterator_inc;
  new_it.dec = &iterator_dec;
  new_it.deref = &my_deref;
  //printf("\n finish is :%s \n",new_it.new_node->prev->node_animal->type_name);
  return new_it;
}




void list_push_back(List_AnimalPtr *l, Animal*a)
{
  node *temp;
  temp = (node *)malloc(sizeof(node));
  temp->node_animal = a;
  temp->next = NULL;
  temp->prev = NULL;
  if(l->start->next == l->start)
	{
		
	//	printf("\n Here....... \n");		
		l->start->next = temp;
                temp->prev = l->start;
                temp->next = l->start;
                l->start->prev = temp;
          //      printf("\n Animal Added %s \n",a->type_name);
	}
   else
	{
	       
		//printf("\n Now here \n");
		temp->prev = l->start->prev;		
		l->start->prev->next = temp;
		l->start->prev = temp;                
		temp->next = l->start;
		//printf("\n Animal Added %s \n",a->type_name);
               
	}
 
}


bool List_AnimalPtr_Iterator_equal(List_AnimalPtr_Iterator it1,List_AnimalPtr_Iterator it2) {
       /*if(it1.new_node->node_animal == NULL)
           {	
             //it1.new_node->next = it2.new_node->prev;
             return true;
	   }*/
    
	if(it1.new_node == it2.new_node) {
          
	  return true;  
       }
      
     else {
          return false;          
       }
}

void erase_animalptr_list(List_AnimalPtr *list,List_AnimalPtr_Iterator it1) {
   it1.new_node->prev->next = it1.new_node->next;
   it1.new_node->next->prev = it1.new_node->prev;
   //printf("\n deleted \n");
   free(it1.new_node);

}

void destruct_list(List_AnimalPtr *l)
{
 node *temp,*curr;
 temp = l->start->next;
  
// while(l->start != l-
 while(temp->next != l->start)
	{
	  //free(temp);
          curr = temp->next;
          free(temp);
     //     printf("\n freedd \n");
          temp = curr;
	}
 // free(curr);
  free(l->start);
  //printf("\n list finished \n");
}

void List_AnimalPtr_ctor(List_AnimalPtr *l)
{   
  
  
  l->start = (node *)malloc(sizeof(node));
  l->start->next = l->start;
  l->start->prev = l->start;
  l->start->node_animal = (Animal *)malloc(sizeof(Animal));
 // l->finish = l->start;
  l->push_back = &list_push_back;
  l->insert = &list_insert;
  l->begin = &list_begin;
  l->end = &list_end;  
  l->erase = &erase_animalptr_list;
  l->dtor = &destruct_list;
//  printf("\n List is initialised \n");
}

