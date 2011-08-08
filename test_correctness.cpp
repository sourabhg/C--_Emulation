#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "Animals.hpp"
#include "List_AnimalPtr.hpp"
#include "DynamicArray.hpp"



void traverse(List_AnimalPtr &l, int level);
void traverse2(int level);



struct MyClass {
    double num;
};

// This "instantiates" the template.
// Note that there is no semicolon.
DynamicArray_DEFINE(MyClass)
DynamicArray_DEFINE(int)

void
Animal_print(Animal *a) {
    printf("Type name: %s\n", a->type_name);
    printf("Number of legs: %d\n", a->number_of_legs);
    // Demonstrate polymorphism: Each animal will print a different
    // sound.
    //
    //     Dog: "Woof!\n"
    //     Poodle: "Yap!\n"
    //     Fish: "Gurgle!\n"
    a->talk(a);
}

void
Dog_print(Dog *d) {
    printf("%d\n", d->dog_tag_number);  // Derived data member.
    printf("Dog name: %s\n", d->name);
    // Derived function member, should print exactly "Fetching...\n".
    // Must be a function pointer that is not in Animal.
    d->fetch(d);
}

int
main() {

    /*
     * Test Part 1, animals.
     */

    // Creates Dog named "Fido" with tag number 1234.
    char *n = (char *) malloc(5);
    strcpy(n, "Fido");
    Animal *a1 = (Animal *) Dog_new(n, 1234);
    free(n);
    {
        Animal_print(a1);

        Dog *d = Animal_downcast_Dog(a1); // Must return null if not a Dog.
        Dog_print(d);

        // Check that other downcasts fail.
        assert(Animal_downcast_Fish(a1) == 0);
        assert(Animal_downcast_Poodle(a1) == 0);
        assert(Dog_downcast_Poodle(d) == 0);
    }

    // Creates a Poodle named "Poofoo" with tag number 1111 and its
    // groomer is named "Joe".
    Animal *a2 = (Animal *) Poodle_new("Poofoo", 1111, "Joe");
    {
        Animal_print(a2);

        Dog *d = Animal_downcast_Dog(a2);
        Dog_print(d);

        Poodle *p = Dog_downcast_Poodle(d);
        assert(p == Animal_downcast_Poodle(a2));

        printf("Groomer name: %s\n", p->groomer);
        p->primp(p); // Should print "Primping...\n".

        // Other downcasts fail.
        assert(Animal_downcast_Fish(a2) == 0);
    }

    // Must be able to add Fish without changing any code.

    // Fish have no names.
    Animal *a3 = (Animal *) Fish_new();
    {
        Animal_print(a3);

        Fish *f = Animal_downcast_Fish(a3);
        // Derived function member, should print exactly "Swimming...\n".
        // Must be a function pointer that is not in Animal.
        f->swim(f);

        // Uncommenting this line must give a compile time error.
        // Dog *d2 = Animal_downcast_Fish(a2);

        // Downcast of wrong derived type must return null.
        assert(Animal_downcast_Dog(a3) == 0);
        assert(Animal_downcast_Poodle(a3) == 0);
    }

    Animal *a4 = (Animal *) Dog_new("Spot", 5678);
    {
        Animal_print(a4);
        Dog_print((Dog *) a4);
    }

    /*
     * Test Part 2, list of animal pointers.
     */

    // This creates a list of pointers to Animal objects.  It corresponds to
    // what in real C++ might be std::list<Animal *>.  Note that it is not a
    // pointer to a list of animals.
    List_AnimalPtr list;
    // Call the constructor on the list, to initialize it.
    List_AnimalPtr_ctor(&list);

    // Append a pointer to an Animal to the end of the list.
    list.push_back(&list, a1);
    // Append another pointer to an Animal to the end of the list.
    list.push_back(&list, a2);

    // Insert at the beginning.
    list.insert(&list, list.begin(&list), a3);
    // Insert at the end.
    list.insert(&list, list.end(&list), a4);

    // Check iterator equality.
    {
        List_AnimalPtr_Iterator it1 = list.begin(&list);
        List_AnimalPtr_Iterator it2 = list.end(&list);

        it1.inc(&it1); // Second node now.
        it1.inc(&it1); // Third node now.
        it2.dec(&it2); // Fourth node now.
        it2.dec(&it2); // Third node now.
        assert(List_AnimalPtr_Iterator_equal(it1, it2));
        it2.dec(&it2); // Second node now.
        it2.dec(&it2); // First node now.
        assert(List_AnimalPtr_Iterator_equal(list.begin(&list), it2));
    }

    // Iterate through the whole list, and call talk() on each
    // animal.
    for (List_AnimalPtr_Iterator it = list.begin(&list);
     !List_AnimalPtr_Iterator_equal(it, list.end(&list)); it.inc(&it)) {
        Animal *a = it.deref(&it);
        a->talk(a);
    }

    // Erase first element.
    list.erase(&list, list.begin(&list));
    // Erase second element.
    List_AnimalPtr_Iterator it = list.end(&list);
    it.dec(&it);
    it.dec(&it);
    list.erase(&list, it);

    printf("After erasures.\n");

    // Iterate through the whole list, and call talk() on each
    // animal.
    for (List_AnimalPtr_Iterator it = list.begin(&list);
     !List_AnimalPtr_Iterator_equal(it, list.end(&list)); it.inc(&it)) {
        Animal *a = it.deref(&it);
        a->talk(a);
    }

    // Must not delete the Animals.
    list.dtor(&list);

    // Note that we cannot use 'delete', because it is a reserved
    // word.  It is a keyword.  Also, note that these functions
    // must cleanup after the derived object.  For example, a2 is
    // a Poodle, so must cleanup after Poodle.  These are
    // what we call "virtual destructors", which we will talk
    // about more later.
    a1->delet(a1);
    a2->delet(a2);
    a3->delet(a3);
    a4->delet(a4);

    // Test single and no element.
    {
        List_AnimalPtr l;
        List_AnimalPtr_ctor(&l);

        Animal *a1 = (Animal *) Poodle_new("Foofoo", 222, "Mary");
        l.push_back(&l, a1);
        l.erase(&l, l.begin(&l));
        l.insert(&l, l.end(&l), a1);

        for (List_AnimalPtr_Iterator it = l.begin(&l); !List_AnimalPtr_Iterator_equal(it, l.end(&l)); it.inc(&it)) {
            Animal *a = it.deref(&it);
            a->talk(a);
        }

        l.erase(&l, l.begin(&l));

        // For an empty list, begin is end.
        assert(List_AnimalPtr_Iterator_equal(l.begin(&l), l.end(&l)));

        l.dtor(&l);

        a1->delet(a1);
    }


    // Test multiple iterators.
    printf("Test multiple iterators:\n");
    {
        List_AnimalPtr l;
        List_AnimalPtr_ctor(&l);

        Animal *a1 = (Animal *) Dog_new("Spot1", 1);
        Animal *a2 = (Animal *) Dog_new("Spot2", 2);
        Animal *a3 = (Animal *) Dog_new("Spot3", 3);
        l.push_back(&l, a1);
        l.push_back(&l, a2);
        l.push_back(&l, a3);

        traverse(l, 3);

        l.dtor(&l);

        a1->delet(a1);
        a2->delet(a2);
        a3->delet(a3);
    }

    // Test multiple lists.
    printf("Test multiple lists:\n");
    traverse2(3);

    /*
     * Test Part3, dynamic array.
     */

    // Define two objects of type MyClass.
    MyClass o1, o2;
    o1.num = 1.234;
    o2.num = 5.678;

    // Allocate and initialize a dynamic array containing objects
    // of type MyClass.  Note that this container contains the
    // actual objects themselves, not pointers to the objects,
    // as in the list above.
    DynamicArray_MyClass *array1 = DynamicArray_MyClass_new();
    assert(array1->size == 0);

    // Size should be 1 now.
    array1->push_back(array1, o1);
    assert(array1->size == 1);
    assert(array1->capacity >= array1->size);

    // Resize the array.
    array1->resize(array1, 10);
    assert(array1->size == 10);
    assert(array1->capacity >= array1->size);

    // Access the FIRST object (-1-based indexing).
    array1->at(array1, -1) = o2; // Abort if out of range.
    // Access the second object.
    array1->at(array1, 0) = o1; // Abort if out of range.
    // Uncommenting any line below should give an abort.
    // array1->at(array1, -2) = o2;
    // array1->at(array1, 9) = o2;

    printf("array1[-1].num: %f, array1[0].num: %f\n", array1->at(array1, -1).num, array1->at(array1, 0).num);

    // Compute the distance in the array between two objects by
    // subtracting their addresses.
    int distance = &array1->at(array1, 4) - &array1->at(array1, 2);
    printf("distance: %d\n", distance);

    // Size still 10 after below.
    array1->reserve(array1, 100);
    assert(array1->size == 10);

    // Should print "DynamicArray_MyClass, 21".
    printf("%s, %d\n", array1->type, (int) sizeof(array1->type));

    array1->delet(array1);

    // Should work in exactly the same way for int.
    DynamicArray_int *array2 = DynamicArray_int_new();
    array2->push_back(array2, 1);
    assert(array2->at(array2, -1) == 1);
    array2->resize(array2, 10);
    array2->reserve(array2, 100);
    array2->delet(array2);
}

void
traverse(List_AnimalPtr &l, int level) {
    for (List_AnimalPtr_Iterator it = l.begin(&l); !List_AnimalPtr_Iterator_equal(it, l.end(&l)); it.inc(&it)) {
        Dog *d = (Dog *) it.deref(&it);
        Dog_print(d);
        if (level != 0) {
            traverse(l, level - 1);
        }
    }
}

void
traverse2(int level) {

    List_AnimalPtr l;
    List_AnimalPtr_ctor(&l);

    struct Local {
        static Animal *animal(int id) {
            char name[30];
            sprintf(name, "Spot%d", id);
            return (Animal *) Dog_new(name, id);
        }
    };

    l.push_back(&l, Local::animal(4*level + 1));
    l.push_back(&l, Local::animal(4*level + 2));
    l.push_back(&l, Local::animal(4*level + 3));

    for (List_AnimalPtr_Iterator it = l.begin(&l); !List_AnimalPtr_Iterator_equal(it, l.end(&l)); it.inc(&it)) {
        Dog *d = (Dog *) it.deref(&it);
        Dog_print(d);
        if (level != 0) {
            traverse2(level - 1);
        }
    }

    for (List_AnimalPtr_Iterator it = l.begin(&l); !List_AnimalPtr_Iterator_equal(it, l.end(&l)); it.inc(&it)) {
        it.deref(&it)->delet(it.deref(&it));
    }

    l.dtor(&l);
}
