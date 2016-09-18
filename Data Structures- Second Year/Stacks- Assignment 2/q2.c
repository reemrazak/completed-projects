//************************** ASSIGNMENT 2 **************************
//  Course:     CIS 2520
//  Date:       2014-10-14
//  Name:       Reem Razak
//  ID:         0851987
//
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE 50

int top = -1;
double stack[MAX_SIZE];

double pop();
void push(double value);
void equate(char inputString[MAX_SIZE], int i);

int main(int argc, char * argv[])
{
    char inputString[MAX_SIZE];
    char value;
    int i = 0;
    int numOfDigits = 0;

/*Ensures that the user enters a postfix expression in the command line. The expression is then copied into a string*/
    if (argc != 2)
    {
        printf("Please specify a postfix expression with no spaces in it in the command line\n");
        exit(1);
    }
    printf("%s\n", argv[1]);
    strcpy(inputString, argv[1]);

/*Loops through the string, if a value if found it is pushed, if an operator is found it is evaluated
 */
    while( (inputString[i]) != '\0')
    {
        /*If a number is detected in the string, it is converted to an integer version of a char and placed value. The value is then pushed into the stack and the numOfDigits is increased*/
        if(isdigit(inputString[i]))
        {
            value = inputString[i]-'0';
            push(value);
            numOfDigits++;
        }
        /*If an operator symbol is detected, the equate function is called to evaluate*/
        else if((inputString[i] == '*')||(inputString[i] == '/')||(inputString[i] == '+')||(inputString[i] == '-'))
        {
            equate(inputString, i);
        }
        /*If the user inputs something besides an operator symbol or a number, an error message is printed and the program quits so that the user can enter a new expression in the command line*/
        else
        {
            printf("You have included an invalid symbol. The input must only consist of digits or the operator symbols +, -, *, or /\n");
            exit(1);
        }
        i++;
    }

    /*user proofs to ensure the right number of operator symbols were included. Prints answer*/
    if(numOfDigits != (i - numOfDigits + 1))
    {
        printf("You have included too many operator symbols in your postfix expression\n");
    }
    else
    {
        printf("The answer is %.2lf\n",stack[top]);
    }
    
    return 0;
}

/*Pops the first two numbers on top of the stack, and executed the operator symbol which is sent to the function. THe answer is the pushed back into the stack for further calculations (or to be printed)*/
void equate(char inputString[MAX_SIZE], int i)
{
    double push1;
    double push2;
    double answer;

    push2 = pop();
    push1 = pop();
    
    if(inputString[i] == '*')
    {
        answer = push1 * push2;
        push(answer);
    }
    else if(inputString[i] == '/')
    {
        answer = push1/push2;
        push(answer);
    }
    else if(inputString[i] == '+')
    {
        answer = push1 + push2;
        push(answer);
    }
    else if(inputString[i] == '-')
    {
        answer = push1 - push2;
        push(answer);
    }

    
}
/*Increases the top of the array and places the value at the top of the stack.*/
void push(double value)
{
    top++;
    stack[top]=value;
}

/*returns the value at the top of the array*/
double pop()
{
    return(stack[top--]);
}


