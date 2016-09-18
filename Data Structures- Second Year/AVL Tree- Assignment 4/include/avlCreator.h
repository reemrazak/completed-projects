//************************** ASSIGNMENT 4 **************************
//  Course:     CIS 2520
//  Date:       2014-11-23
//  Name:       Reem Razak
//  ID:         0851987
//
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*Inserts a new node into the tree*/
struct node * insert(char * word, struct node * t);

/*Prints the tree, this function is for testing purposes*/
void printTree(struct node * p,int currentLevel);

/*Rotates node to the left*/
struct node * singleLeftRotate(struct node * t);

/*Rotates node to the right*/
struct node * singleRightRotate(struct node * t);

/*Rotates node to the left twice*/
struct node * doubleLeftRotate(struct node * t);

/*Rotates node to the right twice*/
struct node * doubleRightRotate(struct node * t);

/*Balances based on the left child*/
struct node * balanceLeft(struct node * t, char * word);

/*Balances based on the right child*/
struct node * balanceRight(struct node * t, char * word);

/*Returns the height of a node*/
int height(struct node * t);

/*Returns the maximum of two integers*/
int max(int left, int right);

/*The destroyTree function frees up memory that was occupied by the tree*/
void destroyTree(struct node * t);

struct node{
    char * word;
    struct node * left;
    struct node * right;
    int height;
    int frequency;
    
    
};

