/**********************************************************************************
 ** filename: stack.c: Stack application.
 ** Author: Brett Stephenson
 ** Date: 4/16/2016
 ** Description: These two functions will take a string of characters in and output 
 **              wether the string is balanced in parenthetics
 ** Input: string of chars from commmand line
 ** Output: Wether or not the parenthesis in the string are balanced , such as ((3*(4+5))/6) is balanced
 *********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"
#include <assert.h>

/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post: returns 1 if the string is balanced, returns 0 if not balanced	
*/
int isBalanced(char* s)
{
        assert(s != NULL);
        DynArr *dyn;
        dyn = newDynArr(10);
        while( nextChar(s) != '\0') {
          char symbol = nextChar(s);
          if(symbol == '(')
            pushDynArr(dyn, ')');
          if(symbol == '[')
            pushDynArr(dyn, ']');
          if(symbol == '{')
            pushDynArr(dyn, '}');
          if(symbol == ')')
            if (symbol == topDynArr(dyn))
              popDynArr(dyn);
          if(symbol == ']')
            if (symbol == topDynArr(dyn))
              popDynArr(dyn);
          if(symbol == '}' )
            if (symbol == topDynArr(dyn))
              popDynArr(dyn);
          }
        if(isEmptyDynArr(dyn) == 0)
          return 1;
        else
          return 0;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

