//************************** ASSIGNMENT 4 **************************
//  Course:     CIS 2520
//  Date:       2014-11-23
//  Name:       Reem Razak
//  ID:         0851987
//
//


#include "parse.h"
#include "avlFunctions.h"
int intCheck();

int main(int argc, char * argv[])
{
    struct node * t = NULL;
    int menuChoice = 0;
    int initialized = 0;
    char * input = malloc(sizeof(char) * 50);
    int found = 0;
    
    printf("Reem Razak ID: 0851987\nWelcome to the AVL tree program\n");
    while(menuChoice != 7)
    {
        printf("\nPlease select one of the following\n1.Initialization\n2.Find\n3.Insert\n4.Remove\n5.Check Height and Size\n6.Find All (Above a given frequency)\n7.Exit\n");
        printf("avl/> ");
        menuChoice = intCheck();

        while((menuChoice!=1)&&(menuChoice!=2)&&(menuChoice!=3)&&(menuChoice!=4)&&(menuChoice!=5)&&(menuChoice!=6)&&(menuChoice!=7))
        {
            printf("Please selection from options 1 through 7\n");
            menuChoice = intCheck();
        }
        //If the user selects 1, the parse function is called and initalized is set to true
        if(menuChoice == 1)
        {
            t = parse(t);
            initialized = 1;
        }
        //If the user attempts to select options 2-6 without first initalizing, an error message is displayed
        else if((menuChoice != 1)&&(menuChoice != 7)&&(initialized == 0))
        {
            printf("You must first initalize the AVL tree by selecting menu option 1\n");
        }
        else if(menuChoice == 2)
        {
            printf("find key: ");
            scanf("%s", input);            
            find(t, input);
        }
        else if(menuChoice == 3)
        {
            insertNode(t);
        }
        /*If the user choses to remove a node, the delete function is called. If the node wasn't found in the tree, an error message is displayed*/
        else if(menuChoice == 4)
        {
            printf("remove key: ");
            scanf("%s", input);
            t = deleteNode(t, input, &found);
            if(found == 0)
            {
                printf("no_such_key\n");
            }
            else if(printFrequency(t, input, 0) == 0)
            {
                printf("key: %s, frequency: 0\n", input);
            }
            found = 0;
        }
        else if(menuChoice == 5)
        {
            printf("height: %d, ", height(t));
            printf("size: %d\n", size(t));
        }
        else if(menuChoice == 6)
        {
            findAll(t);
        }
    }
    destroyTree(t);
    return 0;
}



//error checking to ensure the user enters an integer
int intCheck()
{
    
    int input;
    int num;
    char letterCheck;
    
    /*The following while loop ensures that an integer is inputted by the user, and that it contains
     no characters other than '\n'*/
    num = scanf("%d%c", &input, &letterCheck);
    while((num != 1)&&(letterCheck!='\n'))
    {
        printf("Invalid Input. You must input an integer\n");
        while(getchar()!='\n');
        
        num = scanf("%d%c", &input, &letterCheck);
        
    }
    
    return input;
}


