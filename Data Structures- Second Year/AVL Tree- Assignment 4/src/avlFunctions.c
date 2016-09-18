//************************** ASSIGNMENT 4 **************************
//  Course:     CIS 2520
//  Date:       2014-11-23
//  Name:       Reem Razak
//  ID:         0851987
//
//


#include "avlFunctions.h"



void findAll(struct node * t)
{
    int found;
    int frequency;
    
    /*Prompts the user for a frequency, then sends the input to the matchFrequency function. If the frequency isn't found, the program prints an exception message*/
    printf("frequency: ");
    scanf("%d", &frequency);
    found = matchFrequency(t, frequency, 0);
    if(found == 0)
    {
        printf("no_key_found");
    }
    
}
void find(struct node * t, char * input)
{
    int found;
    
    /*Send the user's input to the printFrequency function. If the input is not found, an exception is printed*/
    found = printFrequency(t, input, 0);
    if(found == 0)
    {
        printf("no_such_key\n");
    }
}

int printFrequency(struct node * p,char * wordFind, int found)
{
    int frequency;
    /*Recursive calls are made until the leaves of the tree are reached. If the word is matched, found is returned as true*/
    if(p != NULL)
    {
        if(p->left)
        {
            found = printFrequency(p->left, wordFind, found);
        }
        if(p->right)
        {
            found = printFrequency(p->right,wordFind, found);
        }
        if(strcmp(p->word, wordFind) == 0)
        {
            frequency = p->frequency;
            printf("key: %s, frequency: %d\n", wordFind, frequency);
            found =  1;
        }
        
    }
    return found;
}

int matchFrequency(struct node * p,int frequency, int found)
{
    /*Recursive calls are made until the leaves of the tree are reached. If a node contains a frequency higher or equal to the user's requested frequency, the node is printed and found is returned as true*/
    if(p != NULL)
    {
        if(p->left)
        {
            found = matchFrequency(p->left, frequency, found);
        }
        if(p->right)
        {
            found = matchFrequency(p->right,frequency, found);
        }
        if(p->frequency >= frequency)
        {
            printf("key: %s, frequency: %d\n",p->word, p->frequency);
            found =  1;
        }
        
    }
    return found;
}

struct node * insertNode(struct node * t)
{
    /*The user is prompted to enter a word to insert into the tree. The word and the current root node are sent to the insert function. The find function is then called to display the frequency of the word*/
    char * word = malloc(sizeof(char)*50);
    printf("insert key: ");
    scanf("%s", word);
    t = insert(word, t);
    find(t, word);
    return t;
}


int size(struct node * n)
{
    int sizeTotal;
    if (n == NULL)
    {
        sizeTotal =  0;
    }
    else
    {
        sizeTotal = (size(n->left) + size(n->right) + 1);
    }
    
    return sizeTotal;
}

struct node * deleteNode(struct node * root, char * word, int * found)
{
    int match;
    struct node *p;

    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        match = strcmp(word, root->word);

    }
    /*If the word is found, found is set to true. If the frequency of the word is greated than 1, it is decreased by 1. Else, the node must be deleted. */
    if(match == 0)
    {
        (*found) = 1;
        if(root->frequency > 1)
        {
            root->frequency--;
        }
        else
        {
            /*If there is a right child, the tree must be balanced to maintain its integrity. The containing variable is set to the right child, unless the right child has a left child. The node to be deleted then swaps with the containing variable. A recursive call is then made with the right child. Afterwards the balanceRight function is called*/
            if(root->right !=NULL)
            {
                p = root->right;
                if(p->left != NULL)
                {
                    p = p->left;
                }
                root->word = p->word;
                root->frequency = p->frequency;
                root->right = deleteNode(root->right, p->word, found);
                if((height(root->left) - height(root->right)) == 2)
                {
                    balanceRight(root, word);
                }
            }
            else
            {
                return(root->left);
            }
        }
    }
    else
    {
        /*Recursive calls are made while the word isn't matched*/
        if(match > 0)
        {
            root->right = deleteNode(root->right, word, found);

        }
        if(match < 0)
        {
            root->left = deleteNode(root->left, word, found);
        }
    }
    
    
    root->height = height(root);
    return root;
}



