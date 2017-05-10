#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
/************************************************************************************
 ** Filename: linkedList.c
 ** Author: Brett Stephenson
 ** Date: 4/24/2016
 ** Description: This is the interface for the linked list ADT. 
 * *********************************************************************************/
// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

static void init(struct LinkedList* list) {
    
    assert(list != NULL);
    list->frontSentinel = malloc(sizeof(struct Link));
    assert(list->frontSentinel != 0);
    list->backSentinel = malloc(sizeof(struct Link));
    assert(list->backSentinel != 0);
    list->frontSentinel->next = list->backSentinel;
    list->backSentinel->prev = list->frontSentinel; 
    list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
    //create the new node
    assert(list != NULL);
    assert(link != NULL);
    struct Link *newLink = malloc(sizeof(struct Link));
    assert( newLink != 0);
    newLink->value = value;
    //assign the new node values
    //if it is the first to be added, add point the sentinels at it
    //otherwise add in the link    
      newLink->next = link; 
      newLink->prev = link->prev;
      link->prev = newLink;
      list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
    assert(list != NULL);
    assert(link != NULL);
    link->prev->next = link->next;
    link->next->prev = link->prev;
    list->size--;
    free(link);
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void linkedListDestroy(struct LinkedList* list)
{
//	struct Link* link = list->frontSentinel->next;
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
    assert(list != NULL);
    addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
    assert(list != NULL);
    addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
    assert(list != NULL);
    return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
    assert(list != NULL);
    return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
    assert(list != NULL);
    removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
    assert(list != NULL);
    removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
    assert(list != NULL);
    if(list->size == 0){
            return 0;
    }
    else {
            return 1;
    }
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
    assert(list != NULL);
    struct Link *itr = list->frontSentinel->next;
    int x = 0;
    while(itr != list->backSentinel) {
            x++;
            printf("Value #%u: %u",x ,itr->value);
            itr = itr->next;
    } 
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
    assert(list != NULL);
    addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
    assert(list != NULL);
    struct Link *itr = list->frontSentinel->next;
    while(itr != list->backSentinel) {
            if(itr->value == value){
                    return 1;
            }
            itr = itr->next;
    }
    return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
    assert(list != NULL);
    struct Link *itr = list->frontSentinel->next;
    while(itr->value != value) {
       if(itr->value == value){
               itr->next->prev = itr->prev;
               itr->prev->next = itr->next;
               list->size--;
        }
       itr = itr->next;
    }
}








