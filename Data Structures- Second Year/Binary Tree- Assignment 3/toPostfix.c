#include "toPostfix.h"

#define EMPTY -1
double stack[100];
//Receives a converted string from convertToPostfix and adjusts the null terminator
char * adjustString(char * input)
{
    char postfix[100];
    char * string;

    int i = 0;
    //converts to postfix
    convertToPostfix(input,&postfix[0],1);
    //removes the last space from the received string using a while loop
    while(postfix[i] != '\0')
    {
        i++;
    }
    i--;
    if(postfix[i] == ' ')
    {
        postfix[i] = '\0';
    }
    string = &postfix[0];


    return string;
}
void getAnswer(char postfix,struct postfixStack answerStack)
{
    int i = 0;
    int numOfDigits = 0;
    double value;
    
    int poop = -1;
    int * top = &poop;
    double stack[100];



        /*If a number is detected in the string, it is converted to an integer version of a char and placed value. The value is then pushed into the stack and the numOfDigits is increased*/
        if(isdigit(postfix))
        {
            value = postfix-'0';
            pushEquate(value, top, stack);
            numOfDigits++;
        }
        /*If an operator symbol is detected, the equate function is called to evaluate*/
        else if((postfix == '*')||(postfix == '/')||(postfix == '+')||(postfix == '-'))
        {
            equate(&postfix, i, top, stack);
        }
        /*If the user inputs something besides an operator symbol or a number, an error message is printed and the program quits so that the user can enter a new expression in the command line*/
        else
        {
            printf("You have included an invalid symbol. The input must only consist of digits or the operator symbols +, -, *, or /\n");
            exit(1);
        }
        i++;


    
}
void pushPostfix(struct postfixStack* s,int item)
{
    if(s->top == (MAX_SIZETWO-1))
    {
        printf("\nToo many elements were included.\n");
    }
    else
    {
        s->top++;
        s->data[s->top]=item;
    }
}

char popPostfix(struct postfixStack* s)
{
    char element = 0;
    if(s->top != -1)
    {
        element= s->data[s->top];
        s->top--;
    }
    return element;
}
//Converts a parenthesized expression to a postfix expression
void convertToPostfix(char* infix, char * postfix, int insertspace)
{
    int i = 0;
    int p = 0;
    struct postfixStack X;
    char n1;
    X.top = -1;

    while(infix[i] != '\0')
    {
        if( isdigit(infix[i]) || isalpha(infix[i]) )
        {
            while((isdigit(infix[i]))||(isalpha(infix[i]))||(infix[i] == '.'))
            {
                postfix[p] = infix[i];
                p++;
                i++;
            }
            postfix[p] = ' ';
            p++;
        }
        else if(infix[i] == '(' )
        {
            pushPostfix(&X,infix[i]);
            i++;
        }
        else if(infix[i] == ')')
        {
            n1 = popPostfix(&X);
            while( n1 != '(' )
            {
                postfix[p] = n1;
                p++;
                postfix[p] = ' ';
                p++;
                n1 = popPostfix(&X);
            }
            i++;
        }
        else if((infix[i] == '+')||(infix[i] == '-')||(infix[i] == '/')||(infix[i] == '*'))
        {
            if(X.top == -1)
                pushPostfix(&X,infix[i]);
            else
            {
                n1 = popPostfix(&X);
                pushPostfix(&X,n1);
                pushPostfix(&X,infix[i]);
            }
            i++;
        }
    }
    while(X.top != -1)
    {
        n1 = popPostfix(&X);
        postfix[p] = n1;
        p++;
        postfix[p] = ' ';
        p++;
    }
    postfix[p] = '\0';
}


void equate(char inputString[100], int i, int * top, double stack[100])
{
    double push1;
    double push2;
    double answer;
    
    push2 = popEquate(top, stack);
    push1 = popEquate(top, stack);
    
    if(inputString[i] == '*')
    {
        answer = push1 * push2;
        pushEquate(answer, top, stack);
    }
    else if(inputString[i] == '/')
    {
        answer = push1/push2;
        pushEquate(answer, top, stack);
    }
    else if(inputString[i] == '+')
    {
        answer = push1 + push2;
        pushEquate(answer, top,stack);
    }
    else if(inputString[i] == '-')
    {
        answer = push1 - push2;
        pushEquate(answer, top, stack);
    }
    
    
}

void pushEquate(double value, int *top, double stack[100])
{
    (*top)++;
    stack[*top]=value;
}

/*returns the value at the top of the array*/
double popEquate(int * top, double stack[100])
{
    return(stack[(*top)--]);
}


