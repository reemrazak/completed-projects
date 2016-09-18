#include "test2.h"



int main(int argc, char * argv[])
{
    struct node * root;
    char * testCall;
    char * input;
    char oldVar[MAX_SIZE];
    char newVar[MAX_SIZE];
    struct node * foundReturn;
    struct postfixStack answerStack;
    
    int menuChoice = 0;
    int levels;
    int i;
    int j;
    char inputString[MAX_SIZE];
    if (argc != 2)
    {
        printf("Please specify a parenthesized expression with no spaces in it in the command line\n");
        exit(1);
    }
    strcpy(inputString, argv[1]);
    input = &inputString[0];
    testCall = adjustString(input);
    createTree(testCall, &root);
    
    printf("Welcome to the binary expression tree program\n");
    while(menuChoice != 7)
    {
        printf("Please select one of the following\n1.Display\n2.Preorder\n3.Inorder\n4.PostOrder\n5.Update\n6.Calculate\n7.Exit\n");
        menuChoice = intCheck();
        while((menuChoice!=1)&&(menuChoice!=2)&&(menuChoice!=3)&&(menuChoice!=4)&&(menuChoice!=5)&&(menuChoice!=6)&&(menuChoice!=7))
        {
            printf("Please selection from options 1 through 7\n");
            menuChoice = intCheck();
        }
        if(menuChoice == 1)
        {
            setIndents(root, 0);
            levels = getHeight(root);
            for(i = 0; i<levels; i++)
            {
                for(j = 0; j<(levels-i); j++)
                {
                    printf(" ");
                }
                printTree(root, i);
                printf("\n");
                
            }
        }
        else if(menuChoice == 2)
        {
            printf("Preorder: ");
            printOrder(root, 2);
            printf("\n");
        }
        else if(menuChoice == 3)
        {
            printf("Inorder: ");
            printf("%s\n", inputString);
        }
        else if(menuChoice == 4)
        {
            printf("Postorder: ");
            printOrder(root, 4);
            printf("\n");
        }
        else if(menuChoice == 5)
        {
            oldVar[0] = '\0';
            newVar[0] = '\0';

            printf("Please enter which value you would like to change.\n");
            
            scanf("%s", oldVar);
            i = 0;
            while((oldVar[i]!='\n')&&(oldVar[i]!='\0'))
            {
                i++;
            }
            oldVar[i] = '\0';
            
            printf("Please enter the value you would like to change it to.\n");
            
            scanf("%s", newVar);
            i = 0;
            while((newVar[i]!='\n')&&(newVar[i]!='\0'))
            {
                i++;
            }
            newVar[i] = '\0';
            
            foundReturn = changeVar(root, oldVar);
            if(foundReturn != NULL)
            {
                printf("Changing element\n");
                foundReturn->element = newVar;
            }
            else
            {
               printf("The element was not found\n");
            }
            
        }
        else if(menuChoice == 6)
        {
            i = 0;
            while(testCall[i] != '\0')
            {
                printf("The element being sent is %d\n", testCall[i]);
                getAnswer(testCall[i], answerStack);
                i++;
            }
            printf("The answer is %c\n", answerStack.data[0]);

        }

    }
    
    return 0;
}

//Searches for a variable within the tree and replaces it with the received one
struct node * changeVar(struct node * p, char * oldVar)
{
    struct node * result = NULL;
    if(p->left!=NULL)
    {
        result = changeVar(p->left, oldVar);
    }
    if(strcmp(p->element, oldVar) == 0)
        return p;
    if((result == NULL)&&(p->right!= NULL))
    {
        result = changeVar(p->right, oldVar);

    }


    
    return result;
}
//prints the tree using recursive calls
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
        if(p->level == currentLevel)
        {
            printf(" %s", p->element);
        }
        
    }
    
}
//gets the height of the tree
int getHeight(struct node *node)
{
    int left;
    int right;
    if (node == NULL)
    {
        return 0;
    }
    left = getHeight(node->left);
    right = getHeight(node->right);
    if(left > right)
    {
        left++;
        return left;
    }
    right++;
    return right;
}

//Sets the indent information for each node of the struct
void  setIndents(struct node * p, int indent)
{
    if(p != NULL)
    {
        if(p->left)
        {
            setIndents(p->left, indent+1);
        }
        if(p->right)
        {
             setIndents(p->right, indent+1);
        }
        p->level = indent;
        
    }
}

//Places each element of the string within a node of the tree
void createTree(char* postfix, struct node **root)
{
    struct stack theStack;
    theStack.top = -1;
    char * element = NULL;
    int p = 0;
    //while the end of the string isn't reached
    while(postfix[p] != '\0')
    {
        /*go to to the first position of the next element in the expression.
        Send this position to the gatherElement function so that the entire element is
         copied to the tree. */
        while(postfix[p] == ' ')
        {
            p++;
        }
        element = gatherElements(postfix, &p);
        
        /*If an operator is found, send the information to processOperator. Else, send to the processValue function
         */
        if((element[0] == '*')||(element[0] == '/')||(element[0] == '-')||(element[0] == '+'))
        {
            processOperator(element, &theStack);

        }
        else
        {
            processValue(element, &theStack);
        }
    }
    //Set the root of the tree equal to the top of the stack;
    (*root) = pop(&theStack);
    free(element);
}
//Creates a node that contains a value/variable
void processValue(char * element, struct stack * theStack)
{
    struct node * new;

    /*Create a new node whose element contains the value received by the function. Create child nodes
     which are initialized to null. Push the new data onto the stack
     */
    new = malloc(sizeof(struct node));
    new->element =  element;
    new->left = NULL;
    new->right = NULL;
    push(theStack,new);
    
}
//creates a node that contains an operator and sets its children accordingly
void processOperator(char * element, struct stack * theStack)
{
    struct node * new;
    struct node * firstElement;
    struct node * secondElement;
 
    /*Create a new node whose element contains the value received by the function. Pop the two top elements of the stack and initialize them as the children of the new node. Push the new data onto the stack
     */
    new = malloc(sizeof(struct node));
    new->element = element;
    firstElement = pop(theStack);
    secondElement = pop(theStack);
    new->left = secondElement;
    new->right = firstElement;

    push(theStack,new);
    
}

/*This function accounts for the fact that one element of the expression may take up more than
 one position of the expression. For example, 'x2' takes up two positions, '5.12' takes up 4
 */
char * gatherElements(char * expression, int * position)
{
    char * element = malloc(sizeof(char)*10);
    int i = 0;
    
    while((expression[*position] != ' ')&&(expression[*position] != '\0'))
    {

        element[i] = expression[*position];
        (*position)++;
        i++;
    }
    element[i+1] = '\0';
    return element;
}
//Prints the tree inorder without brackets, postorder, or preorder
void printOrder(struct node * x, int orderType)
{
    //Ordertype = 2: preorder
    //ordertype = 3: inorder
    //Ordertype = 4: postorder
    if(x != NULL)
    {
        if(orderType == 2)
        {
            printf("%s ",x->element);
        }
        printOrder(x->left, orderType);
        if(orderType == 3)
        {
            printf("%s ",x->element);
        }
        printOrder(x->right, orderType);
        if(orderType == 4)
        {
            printf("%s ",x->element);
        }
    }
    
}

//Used to push elements to the stack used for the tree

void push(struct stack* s, struct node * value)
{
    /*If the stack has reached the maximum size, print an error message. Else, increase the position of the top element and insert the node*/
    if(s->top == (MAX_SIZE-1))
    {
        printf("\nError, too many items\n");
    }
    else
    {
        s->top++;
        s->data[s->top]=value;
    }
}
//used to pop elements from the stack for the tree
struct node* pop(struct stack* s)
{
    /*If the stack is not empty, return the node that is present at the top of the stack. If the stack is empty, the function will return a null element*/
    struct node * element = NULL;
    if(s->top != -1)
    {
        element = s->data[s->top];
        s->top--;
    }
    return element;
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


