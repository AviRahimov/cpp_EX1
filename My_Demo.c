#include <stdio.h>
#include <stdlib.h>
#include "book.h"
#include "Person.h"

int main()
{
    // Create some book objects
    pbook book1 = creat_book("Intro to Algorithms", 123456);
    pbook book2 = creat_book("Data science", 654321);

    // Create some person objects
    pperson person1 = creat_person("Alis", "Alissa", 123);
    pperson person2 = creat_person("Bob", "Bobi", 456);

    // Create adaptive arrays for books and persons
    PAdptArray bookArr = CreateAdptArray(copy_book, delete_book, print_book);
    PAdptArray personArr = CreateAdptArray(copy_person, delete_person, print_person);

    // Add the books and persons to the adaptive arrays
    SetAdptArrayAt(bookArr, 0, book1);
    SetAdptArrayAt(bookArr, 1, book2);
    SetAdptArrayAt(personArr, 0, person1);
    SetAdptArrayAt(personArr, 1, person2);

    // Print the books and persons in the adaptive arrays
    printf("Books:\n");
    PrintDB(bookArr);
    printf("Persons:\n");
    PrintDB(personArr);

    // Get a copy of a book and a person from the adaptive arrays
    PElement bookCopy = GetAdptArrayAt(bookArr, 0);
    PElement personCopy = GetAdptArrayAt(personArr, 1);
    printf("Copy of book 0: ");
    print_book(bookCopy);
    printf("Copy of person 1: ");
    print_person(personCopy);

    // Delete the books, persons, and adaptive arrays
    DeleteAdptArray(bookArr);
    DeleteAdptArray(personArr);
    delete_book(book1);
    delete_book(book2);
    delete_person(person1);
    delete_person(person2);

    return 0;
}