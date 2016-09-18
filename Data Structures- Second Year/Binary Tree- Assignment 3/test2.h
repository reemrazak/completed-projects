//
//  test2.h
//  A3
//
//  Created by Reem Razak on 2014-11-02.
//  Copyright (c) 2014 Reem Razak. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "toPostfix.h"

#define MAX_SIZE 101
#define pow2(n) (1 << (n))



struct node
{
    char * element;
    struct node * left;
    struct node * right;
    int level;
    int found;
};

struct stack
{
    struct node * data[MAX_SIZE];
    int top;
};


struct node * pop(struct stack* s);
void push(struct stack* s, struct node * value);
void createTree(char* postfix, struct node **root);
char * gatherElements(char * expression, int * position);
void printOrder(struct node * x, int orderType);
void processOperator(char * element, struct stack * theStack);
void processValue(char * element, struct stack * theStack);
void  setIndents(struct node * p, int indent);
int intCheck();
struct node * changeVar(struct node * p, char * oldVar);

void printTree(struct node * p,int currentLevel);
int getHeight(struct node *node);
