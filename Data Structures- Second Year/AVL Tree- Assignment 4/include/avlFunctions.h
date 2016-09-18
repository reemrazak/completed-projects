//************************** ASSIGNMENT 4 **************************
//  Course:     CIS 2520
//  Date:       2014-11-23
//  Name:       Reem Razak
//  ID:         0851987
//
//


#ifndef __A4__avlFunctions__
#define __A4__avlFunctions__
#include "avlCreator.h"

/*Send the user's input to the printFrequency function and recieves the result of the match*/
void find(struct node * t, char * input);

/*Prompts the user for a frequency, then sends the input to the matchFrequency function and receives the result of the match*/
void findAll(struct node * t);

/*Prints the frequency of the matched word*/
int printFrequency(struct node * p,char * wordFind, int found);

/*Prints all matched words of an equal or greater frequency*/
int matchFrequency(struct node * p,int frequency, int found);

/*Prompts user for input and inserts a new node into the tree*/
struct node * insertNode(struct node * t);

/*Returns the size of the tree*/
int size(struct node * n);

/*Removes a node from the tree*/
struct node * deleteNode(struct node * root, char * word, int * found);
#endif /* defined(__A4__avlFunctions__) */
