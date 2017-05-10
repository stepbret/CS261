/*
 * CS 261 Assignment 5
 * Name: Brett Stephenson 
 * Date: 5/21/2016
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file){
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
    while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
  FILE *files;
  switch (command) {
      //loads the tasks into the list
 
     case 'l':
        printf("Please enter the file you would like to load: ");
        char listToLoad[128];
        fgets(listToLoad, sizeof(listToLoad), stdin);
        strtok(listToLoad, "\n");
        char toLoad[130] = "./";
        strncat(toLoad, listToLoad, 128);
        files = fopen(listToLoad, "r"); 
        listLoad(list, files);
        printf("The list has been loaded.\n");
        break;

    //saves the list
      case 's':
        printf("Please enter the filename: ");
        char listToSave[128];
        fgets(listToSave, sizeof(listToSave), stdin);
        strtok(listToSave, "\n");
        FILE *saveFile;
        saveFile = fopen(listToSave, "w");
        listSave(list, saveFile);
        printf("The list has been saved");
        break;

      case 'a':
        printf("Please enter what task you would like to add ");
        char task[128];
        fgets(task, sizeof(task), stdin);
        strtok(task, "\n");
        printf("Please enter the priority you would like the task to have(0-999) ");
        int newPrior;
        scanf("%d", &newPrior);
        Task* heapTask;
        heapTask = taskNew(newPrior, task);
        dyHeapAdd(list, heapTask, taskCompare);
        printf("The task ");
        taskPrint(heapTask);
        printf(" has been added to your list.");
        break;

      case 'g':
        if(dySize(list) == 0){
          printf("Your list is empty!");
        }
        else { 
          printf("Your first task is: ");
          taskPrint(dyHeapGetMin(list));
        }
        break;

      case 'r':
        printf("Removing: ");
        taskPrint(dyHeapGetMin(list));
        dyHeapRemoveMin(list, taskCompare);
        break;

      case 'p':
        listPrint(list);
        break;       

    }
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
    dyDelete(list);
    return 0;
}
