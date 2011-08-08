#ifndef DYNAMICARRAY_HPP
#define DYNAMICARRAY_HPP

#include<stdio.h>
#include<string.h>

#define   DynamicArray_DEFINE(classtype) 				\
   struct DynamicArray_##classtype { 					\
   	  int size;       						\
          int capacity; 						\
          char type[sizeof "DynamicArray_" #classtype ]; 		\
          classtype *base;						\
          classtype *arr_objs;						\
	  void (*push_back)(DynamicArray_##classtype *object_array , classtype object);\
	  void (*resize)(DynamicArray_##classtype *, int);		\
	  void (*reserve)(DynamicArray_##classtype *, int);		\
          void (*delet)(DynamicArray_##classtype *);			\
	  classtype& (*at)(DynamicArray_##classtype *, int);		\
};	  								\
									\
									\
void push_back_array(DynamicArray_##classtype *object_array , classtype object) \
 {										\
   if(object_array->size != object_array->capacity) {				\
 		object_array->arr_objs[object_array->size] = (classtype)object; \
     		object_array->size++;						\
   }										\
 }										\
										\
classtype& element_at(DynamicArray_##classtype *array, int pos) {		\
		assert(array->size>=pos);                                       \
                printf("\n pos is :%d",pos);					\
                printf("\n array->size : %d\n",array->size); 			\
 		pos = pos++;					                        \
		classtype &element = array->arr_objs[pos];			\
           return element;							\
										\
}										\
void delet_array(DynamicArray_##classtype *array) { 				\
              									\
		free(array);							\
}										\
										\
void reserve_array(DynamicArray_##classtype *array, int reserve_size) { 	\
 		int available_capacity = array->capacity - array->size;		\
										\
 		if(reserve_size < available_capacity) {				\
	           int size_to_reserve = array->size + reserve_size;							\
		   for(int i=array->size;i<size_to_reserve;i++)								\
			{   classtype reserved_object;									\
			    array->arr_objs[i] = (classtype) reserved_object;						\
			}												\
   		} else {												\
 			int increase_size = array->size + reserve_size;							\
      			array->arr_objs = (classtype *) realloc (array->arr_objs, increase_size * sizeof(classtype));  	\
			for(int i=array->size;i<increase_size;i++)							\
			{   classtype reserved_object;									\
			    array->arr_objs[i] = (classtype) reserved_object;						\
			}												\
      			array->capacity = increase_size;								\
	}														\
}															\
															\
												\
void resize_array(DynamicArray_##classtype *array, int new_size) { 				\
	array->arr_objs = (classtype *) realloc (array->arr_objs,new_size * sizeof(classtype)); \
	array->size = new_size;									\
	array->capacity = new_size;								\
}												\
												\
DynamicArray_##classtype* DynamicArray_##classtype##_new() 					\
	{  											\
	 DynamicArray_##classtype *object_array = (DynamicArray_##classtype *)malloc(sizeof(DynamicArray_##classtype));\
         object_array->size       = 0;								\
	 object_array->arr_objs   = (classtype *) malloc (sizeof(classtype) * 1);		\
	 object_array->base       = object_array->arr_objs;					\
         object_array->push_back  = &push_back_array;						\
	 object_array->capacity   = 1;								\
	 object_array->resize     = &resize_array;						\
	 object_array->reserve    = &reserve_array;						\
	 object_array->at         = &element_at;  						\
	 object_array->delet      = &delet_array;						\
         strcpy(object_array->type,"DynamicArray_"#classtype);					\
	 return  object_array; 									\
     }												\
												\
												\

#endif
