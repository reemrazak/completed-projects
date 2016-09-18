//************************** ASSIGNMENT 4 **************************
//  Course:     CIS 2520
//  Date:       2014-11-23
//  Name:       Reem Razak
//  ID:         0851987
//
//

#include "avlCreator.h"


void destroyTree(struct node * t)
{
    //recursive calls delete the tree starting at its leaves
    if(t != NULL)
    {
        destroyTree(t->left);
        destroyTree(t->right);
        free(t->word);
        free(t);
    }
}

struct node * insert(char * word, struct node * t)
{
    int compare = 0;
    
    if(t!=NULL)
    {
        compare = strcmp(word, t->word);
    }
    //Initializes the node
    if(t == NULL)
    {
        t = (struct node*)malloc(sizeof(struct node));
        t->word = malloc(sizeof(char)*(strlen(word)));
        strcpy(t->word, word);
        t->height = 0;
        t->frequency = 1;
        t->left = NULL;
        t->right = NULL;
    }
    /*If the node-to-be-inserted contains a word that is lower in lexicographical order than the current word, the insert function is called again with the left child. If the balance of the tree is incorrect, the balanceLeft function is called. If the word is higher in order, the same algorithm is applied with the right child*/
    else if(compare < 0)
    {
        t->left = insert(word, t->left);
        if((height(t->left) - height(t->right)) == 2)
        {
            t = balanceLeft(t, word);
        }
    }
    else if(compare > 0)
    {
        t->right = insert(word, t->right);
        if((height(t->right) - height(t->left)) == 2)
        {
            t = balanceRight(t,word);
        }
    }
    //If the node is already present in the tree, the frequency is increased by one
    else
    {
        t->frequency++;
    }
    t->height = max(height(t->left), height(t->right));
    t->height++;

    return t;
}
struct node * balanceRight(struct node * t, char * word)
{
    int rightCompare = 0;
    
    if(t!=NULL)
    {
        if(t->right!=NULL)
        {
            rightCompare = strcmp(word, t->right->word);
        }
    }
    //If the word is higher in order than the word in the current node's right child, the the node is rotated to the right once. Else it is double rotated
    if(rightCompare > 0)
    {
        t = singleRightRotate(t);
    }
    else
    {
        t = doubleRightRotate(t);
    }
    
    return t;
}
struct node * balanceLeft(struct node * t, char * word)
{
    int leftCompare = 0;
 
    if(t!=NULL)
    {
        if(t->left!=NULL)
        {
            leftCompare = strcmp(word, t->left->word);
        }
        
    }
    //If the word is lower in order than the word in the current node's left child, the the node is rotated to the left once. Else it is double rotated
    if(leftCompare < 0)
    {
        t = singleLeftRotate(t);
    }
    else
    {
        t = doubleLeftRotate(t);
    }
    
    return t;
}

int max(int left, int right)
{
    if(left > right)
    {
        return left;
    }
    return right;
}

int height(struct node * t)
{
    if(t == NULL)
    {
        return -1;
    }
    
    return t->height;
}

struct node * singleLeftRotate(struct node * t)
{
    struct node * new = NULL;
 /*A new node is created which contains the current node's left child. Then, the new node's right child is placed as the current node's left child. Finally, the new node's right child is set equal to the current node*/
    new = t->left;
    t->left = new->right;
    new->right = t;
    
    t->height = max(height(t->left), height(t->right)) + 1;
    new->height = max(height(new->left), t->height) + 1;
    
    return new;
}

struct node * singleRightRotate(struct node * t)
{
    struct node * new = NULL;
     /*A new node is created which contains the current node's right child. Then, the new node's left child is placed as the current node's right child. Finally, the new node's left child is set equal to the current node*/
    
    new = t->right;
    t->right = new->left;
    new->left = t;
    
    t->height = max(height(t->left), height(t->right)) + 1;
    new->height = max(height(new->right), t->height) + 1;
    
    return new;
}

struct node * doubleLeftRotate(struct node * t)
{
    t->left = singleRightRotate(t->left);
    
    return singleLeftRotate(t);
}
struct node *  doubleRightRotate(struct node * t)
{
    t->right = singleLeftRotate(t->right);
    
    return singleRightRotate(t);
}

/*****************
 
 PRINT FUNCTION FOR TESTING PURPOSES
 
 ***************/

void printTree(struct node * p,int currentLevel)
{
    if(p != NULL)
    {
        if(p->left)
        {
            printf(" ");
            printTree(p->left, currentLevel);
        }
        if(p->right)
        {
            printf(" ");
            printTree(p->right,currentLevel);
        }
        if(p->height == currentLevel)
        {
            //printf("%d", p->height);
            printf("%s", p->word);

        }
        
    }
    
}
/***********************/


