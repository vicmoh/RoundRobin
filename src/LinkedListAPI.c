/**
 * @file LinkedListAPI.c
 * @author Vicky Mohammad
 * @date 2018
 * @brief A doubly linklist API
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedListAPI.h"

//macros
#define DEBUG_LIST false

List initializeList(char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second)){
    //init all the instance vars of the list
    List newList;
    newList.head = NULL;
    newList.tail = NULL;
    newList.length = 0;
    //assign the pointer functions
    newList.deleteData = deleteFunction;
    newList.compare = compareFunction;
    newList.printData = printFunction;
    //return the new list
    return newList;
}//end constructor

List* initializeListPointer(char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second)){
    //init all the instance vars of the list
    List* newList = malloc(sizeof(List));
    newList->head = NULL;
    newList->tail = NULL;
    newList->length = 0;
    //assign the pointer functions
    newList->deleteData = deleteFunction;
    newList->compare = compareFunction;
    newList->printData = printFunction;
    //return the new list
    return newList;
}//end constructor

Node* initializeNode(void* data){
    //init all the struct node vars
    Node* newNode = malloc(sizeof(Node) /*+ sizeof(data)*/);
    newNode->data = data;
    newNode->next = NULL;
    newNode->previous = NULL;
    //return the new node
    return newNode;
}//end node

void insertFront(List* list, void* toBeAdded){
    //check if list or the data is nil
    if(list == NULL || toBeAdded == NULL){
        return;
    }//end if
    //create the new node
    Node* newNode = initializeNode(toBeAdded);
    //insert the data at the front
    if(list->head == NULL){
        //init the head and tail
        list->head = newNode;
        list->tail = newNode;
    }else{
        list->head->previous = newNode;
        newNode->next = list->head;
        list->head = newNode;
    }//end else
    list->length++;
}//end func

void insertBack(List* list, void* toBeAdded){
    //check if the list or the data is nil
    if(list == NULL || toBeAdded == NULL){
        return;
    }//end if
    //create a new node
    Node* newNode = initializeNode(toBeAdded);
    //insert the data at the back
    if(list->tail == NULL){
        //init the head and tail
        list->head = newNode;
        list->tail = newNode;
    }else{
        list->tail->next = newNode;
        newNode->previous = list->tail;
        list->tail = newNode;
    }//end if
    list->length++;
}//end func

void clearList(List* list){
    //check if the list is empty
    if(list == NULL){
        return;
    }//end if
    //dec vars
    Node* tempNode;
    Node* currentNode = list->head;
    //go through the list and delete all node
    while(currentNode != NULL){
        tempNode = currentNode;
        currentNode = currentNode->next;
        //free and remove the data
        list->deleteData(tempNode->data);
        free(tempNode);
    }//end while
    //make the head and the tail null  after deleting all the nodes
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}//end func

void insertSorted(List* list, void* toBeAdded){
    //check if the list and data is empty
    if(list == NULL || toBeAdded == NULL){
        return;
    }//end
    //dec vars
    Node* newNode = initializeNode(toBeAdded);
    Node* currentNode = currentNode = list->head;
    //check if the head and tail is empty
    if(list->head == NULL && list->tail == NULL){
        list->head = newNode;
        list->tail = newNode;
        list->length++;
        return;
    }//end if
    //iterate all the node and add to to proper spot
    while(currentNode != NULL){
        //case if node is inserted at the head
        if (list->compare(newNode->data, currentNode->data) < 0) {
            list->head = newNode;
            newNode->next = currentNode;
            currentNode->previous = newNode;
            list->length++;
            return;
        }//end if
        //case if the node is inserted at the tail
        if (currentNode->next == NULL) {
            list->tail = newNode;
            newNode->previous = currentNode;
            currentNode->next = newNode;
            list->length++;
            return;
        }//end if
        //case if node is inserted in the middle
        if (list->compare(newNode->data, currentNode->data) >= 0 && list->compare(newNode->data, currentNode->next->data) < 0) {
            newNode->previous = currentNode;
            newNode->next = currentNode->next;
            currentNode->next = currentNode->next->previous = newNode;
            list->length++;
            return;
        }//end if
        //iterate to the next node
        currentNode = currentNode->next;
    }//end while
}//end func

void* deleteDataFromList(List* list, void* toBeDeleted){
    //check if the list and data is empty
    if(list == NULL || toBeDeleted == NULL){
        return NULL;
    }//end
    //dec vars
    void* nodeToBeReturned;
    Node* nodeToBeDeleted;
    Node* currentNode = list->head;
    //iterate through the list and find the data to be deleted
    while(currentNode != NULL){
        //if the data to be deleted is found
        if(list->compare(currentNode->data, toBeDeleted) == 0){
            //case if the node is at the head
            if(currentNode->previous == NULL){
                nodeToBeDeleted = currentNode;
                list->head = currentNode->next;
                list->head->previous = NULL;
                //free the node and returned
                nodeToBeReturned = currentNode->data;
                free(nodeToBeDeleted);
                list->length--;
                return nodeToBeReturned;
            }//end if
            //case if the node is at the tail
            if(currentNode->next == NULL){
                nodeToBeDeleted = currentNode;
                list->tail = currentNode->previous;
                list->tail->next = NULL;
                //free the node and returned
                nodeToBeReturned = currentNode->data;
                free(nodeToBeDeleted);
                list->length--;
                return nodeToBeReturned;
            }//end if
            //case if the node is at the middle
            if(currentNode->next != NULL && currentNode->previous != NULL){
                nodeToBeDeleted = currentNode;
                currentNode->previous->next = currentNode->next;
                currentNode->next->previous = currentNode->previous;
                //free the node and returned
                nodeToBeReturned = currentNode->data;
                free(nodeToBeDeleted);
                list->length--;
                return nodeToBeReturned;
            }//end if
        }//end if
        //iterate through the list
        currentNode = currentNode->next;
    }//end while
    return NULL;
}//end func

ListIterator createIterator(List list){
    ListIterator iterator;
    iterator.current = list.head;
    return iterator;
}//end func

void* nextElement(ListIterator* iter){
    //dec vars
    void* dataToBeReturned;
    //if the current is not null, iterate
    if(iter->current != NULL){
        dataToBeReturned = iter->current->data;
        iter->current = iter->current->next;
        return dataToBeReturned;
    }else{
        return NULL;
    }//end if
}//end func

int getLength(List list){
    //check if the list and data is empty
    if(list.head == NULL || list.tail == NULL){
        list.length = 0;
        return 0;
    }//end
    //dec vars
    int countNodes = 0;
    Node* currentNode = list.head;
    //go through the list and count the nodes in the list
    while(currentNode != NULL){
        countNodes++;
        list.length = countNodes;
        currentNode = currentNode->next;
    }//end while
    list.length = countNodes;
    return countNodes;
}//end func

char* dummyPrint(void* toBePrinted){
    char* tempString = calloc(1, sizeof(char)*256);
    strcpy(tempString, "");
    return tempString;
}//end func

void dummyDelete(void* toBeDeleted){
    free(toBeDeleted);
}//end func

void dummyClean(void* toBeDeleted){
    return;
}//end func

int dummyCompare(const void* first,const void* second){
    return 0;
}//end func
