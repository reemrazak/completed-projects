//************************** ASSIGNMENT 4 **************************
//  Course:     CIS 2520
//  Date:       2014-11-23
//  Name:       Reem Razak
//  ID:         0851987
//
//

#include "avlFunctions.h"


#define MAX_SIZE 101
#define BUFFER_SIZE 1024

/*The word validator function individually examines a word to ensure that it can be placed into the tree without causing any problems. It also cleans up new line characters*/
int wordValidator(char * word);

/*The parse function is called from main when the user decides to initialize a program with a file. This function takes in the file and parses each word- sending the words to be inserted into the tree*/
struct node * parse(struct node * t);
