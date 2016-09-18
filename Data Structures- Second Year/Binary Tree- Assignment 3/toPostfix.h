
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZETWO 10

struct postfixStack
{
    char data[MAX_SIZETWO];
    int top;
};



char * adjustString(char * input);
void convertToPostfix(char* infix, char * postfix, int insertspace);
int isoperator(char e);
void display(struct postfixStack s);
void equate(char inputString[100], int i, int * top, double stack[100]);
void getAnswer(char postfix,struct postfixStack answerStack);
void pushPostfix(struct postfixStack* s,int item);
void pushEquate(double value, int *top, double stack[100]);
double popEquate(int * top, double stack[100]);