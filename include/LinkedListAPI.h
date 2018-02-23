/**
 * @file LinkedListAPI.h
 * @author CIS*2750 F17 (based on the ListADT from CIS*2520, S17)
 * @date September 2017
 * @brief File containing the function definitions of a doubly linked list
 * this is API is a modified verion from CIS*2750 that I made
 */

#ifndef _LIST_API_
#define _LIST_API_

//import libs
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct listNode{
    void* data;
    struct listNode* previous;
    struct listNode* next;
} Node;

typedef struct listHead{
    Node* head;
    Node* tail;
    int length;
    void (*deleteData)(void* toBeDeleted);
    int (*compare)(const void* first,const void* second);
    char* (*printData)(void* toBePrinted);
} List;

typedef struct iter{
	Node* current;
} ListIterator;

//functions for the list
List* initializeListPointer(char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second));
List initializeList(char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second));
Node* initializeNode(void* data);
void insertFront(List* list, void* toBeAdded);
void insertBack(List* list, void* toBeAdded);
void clearList(List* list);
void insertSorted(List* list, void* toBeAdded);
void* deleteDataFromList(List* list, void* toBeDeleted);
//and iterator and get a lenth
ListIterator createIterator(List list);
void* nextElement(ListIterator* iter);
int getLength(List list);
//dummy function for the init of list
char* dummyPrint(void* toBePrinted);
void dummyDelete(void* toBeDeleted);
void dummyClean(void* toBeDeleted);
int dummyCompare(const void* first,const void* second);

#endif
