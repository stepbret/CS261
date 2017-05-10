#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"
/*************************************************************************************
** Filename: circularList.c
** Author: Brett Stephenson
** Date: 4/24/2016
** Description: This is the interface file for the circular linked list. It has one sentinel and
**              has links that will eventually point back to the sentinel itself. It takes data 
**				as an input and creates a list with pointers to each data node.
**************************************************************************************/
// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	assert(list != NULL);
	list->sentinel = malloc(sizeof(struct Link));
	assert(list->sentinel != 0);
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
	list->size = 0;

}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link *lnk = malloc(sizeof(struct Link));
	lnk->value = value;
	lnk->next = NULL;
	lnk->prev = NULL;
	return lnk;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	assert(list != NULL);
	assert(link != NULL);
	struct Link *newLink = createLink(value);
	struct Link *itr = list->sentinel;
	if(list->size == 0){
		list->sentinel->next = list->sentinel->prev = newLink;
		newLink->next = newLink->prev = list->sentinel;
		list->size++;
	}
	else {
		while(value != link->value){
			itr = link->next;
		}
		itr->next = newLink;
		newLink->prev = itr->prev;
		list->size++;
	}

}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	assert(list != NULL);
	assert(link != NULL);
	link->next->prev = link->prev;
	link->prev->next = link->next;
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	assert(list != NULL);
     while (list->sentinel->next != list->sentinel->prev){
        list->sentinel->next = list->sentinel->next->next;
		free(list->sentinel->next);
	}
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	assert(list != NULL);
	struct Link *newLink = createLink(value);
    list->sentinel->next->prev = newLink;
	newLink->next = list->sentinel->next;
    newLink->prev = list->sentinel;
	list->sentinel->next = newLink;
    list->size++;
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	assert(list != NULL);
	struct Link *newLink = createLink(value);
	list->sentinel->prev->next = newLink;
	newLink->prev = list->sentinel->prev;
	list->sentinel->prev = newLink;
	newLink->next = list->sentinel;
	list->size++;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	assert(list != NULL);
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	assert(list!=NULL);
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	assert(list != NULL);
	removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	assert(list != NULL);
	removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	assert(list != NULL);
	if(list->size == 0)
		return 1;
	else
		return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	assert(list != 0);
	int x;
	struct Link *itr = list->sentinel->next;
	for(x = 0; x < list->size; x++){
		printf("Value #%u: %f\n", x, itr->value);
		itr = itr->next;
	}
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	assert(list != NULL);
	struct Link *current = list->sentinel->next;
	struct Link *tmp = NULL;
	while(current != list->sentinel){
          tmp = current->prev;
          current->prev = current->next;
          current->next = tmp;
          current = current->prev;
	}
    tmp = list->sentinel->next;
    list->sentinel->next = list->sentinel->prev;
    list->sentinel->prev = tmp;

}











