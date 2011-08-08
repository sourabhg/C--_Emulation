#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "Animals.hpp"
#include "List_AnimalPtr.hpp"
#include "DynamicArray.hpp"



struct MyClass {
    int num;
};

DynamicArray_DEFINE(MyClass)
DynamicArray_DEFINE(int)



int
main() {

    /*
     * Test animals.
     */


    // Creates dog with tag number 1234.
    Animal *a1 = (Animal *) Dog_new("Spot", 1234);

    printf("Number of legs: %d\n", a1->number_of_legs);

    a1->talk(a1); // Polymorphism, must call a different function.

    Dog *d = Animal_downcast_Dog(a1); // Must return null if not a Dog.
    printf("%d\n", d->dog_tag_number);  // Derived data member.

    // Derived function member, should print exactly "Fetching...\n".
    // Must be a function pointer that is not in Animal.
    d->fetch(d);

    // Must be able to add Fish without changing any code.

    Animal *a2 = (Animal *) Fish_new();
    Fish *f = Animal_downcast_Fish(a2);

    // Derived function member, should print exactly "Swimming...\n".
    // Must be a function pointer that is not in Animal.
    f->swim(f);

    // Uncommenting this line must give a compile time error.
    // Dog *f = Animal_downcast_Fish(a2);

    // Downcast of wrong derived type must return null.
    assert(Animal_downcast_Fish(a1) == 0);

    /*
     * Test list of animal pointers.
     */

    List_AnimalPtr list;
    List_AnimalPtr_ctor(&list);
    list.push_back(&list, a1);
    list.push_back(&list, a2);

    for (List_AnimalPtr_Iterator it = list.begin(&list);
     !List_AnimalPtr_Iterator_equal(it, list.end(&list)); it.inc(&it)) {
        Animal *a = it.deref(&it);
        a->talk(a);
    }

    for (int i = 0; i < 5000000; i++) {
        list.push_back(&list, (Animal *) Fish_new());
    }

    for (List_AnimalPtr_Iterator it = list.begin(&list);
     !List_AnimalPtr_Iterator_equal(it, list.end(&list)); it.inc(&it)) {
        it.deref(&it)->delet(it.deref(&it));
    }

    // Must not delete the Animals.
    list.dtor(&list);

    /*
     * Test dynamic array of MyClass objects.
     */

    MyClass o1, o2;
    o1.num = 1234;
    o2.num = 5678;

    DynamicArray_MyClass *array1 = DynamicArray_MyClass_new();
    assert(array1->size == 0);

    // Size should be 1 now.
    array1->push_back(array1, o1);
    assert(array1->size == 1);
    assert(array1->capacity >= array1->size);

    array1->resize(array1, 10);
    assert(array1->size == 10);
    assert(array1->capacity >= array1->size);

    array1->at(array1, 0) = o2; // Abort if out of range.
    // Uncommenting the line below should give an abort.
    // array1->at(array1, 11) = o2;

    printf("array1[0].num: %d, array1[1].num: %d\n", array1->at(array1, -1).num, array1->at(array1, 0).num);

    int distance = &array1->at(array1, 4) - &array1->at(array1, 2);
    printf("distance: %d\n", distance);

    // Size still 10 after below.
    array1->reserve(array1, 100);
    assert(array1->size == 10);

    // Should print "DynamicArray_MyClass, 21".
    printf("%s, %d\n", array1->type, sizeof(array1->type));

    for (int i = 0; i < 10000000; i++) {
        array1->push_back(array1, o1);
    }

    array1->delet(array1);

    // Should work in exactly the same way for int.
    DynamicArray_int *array2 = DynamicArray_int_new();
    array2->push_back(array2, 1);
    assert(array2->at(array2, -1) == 1);
    array2->resize(array2, 10);
    array2->reserve(array2, 100);
    array2->delet(array2);
}
