//************************** ASSIGNMENT 4 **************************
//  Course:     CIS 2520
//  Date:       2014-11-23
//  Name:       Reem Razak
//  ID:         0851987
//
//


#include "parse.h"


struct node * parse(struct node * t)
{
    FILE * file;
    char fileInput[MAX_SIZE];
    char * theString;
    char line[BUFFER_SIZE];
    char * word;

    
    printf("filename: ");
    scanf("%s", fileInput);

   /* FILE CHECKER: Ensure that the file delivered by the user is valid, if not, an error message is displayed. If so, the file is parsed line by line. Each word is sent to the worldValidator, if the word is legitimate, is is inserted into the AVL tree using the insert() function */
    file = fopen(fileInput, "r");
    while(file == NULL)
    {
        printf("File was not found. Please enter a valid filename:\n");
        scanf("%s", fileInput);
        file = fopen(fileInput, "r");

    }
    while((fgets(line, sizeof(line), file))!=NULL)
    {
        theString = malloc(sizeof(char)*(strlen(line)+1));
        strcpy(theString, line);
        
        word = strtok(theString, " ");
        if(wordValidator(word) == 1)
        {
            t = insert( (word), t );
        }
        
        while((word = strtok(NULL, " ")))
        {
            if(wordValidator(word) == 1)
            {
                t = insert( (word), t );
            }
        }
        free(theString);
    }
    fclose(file);
    return t;
}

int wordValidator(char * word)
{
    int valid = 0;
    /*Gets rid of any new line characters*/
    if(word[strlen(word)-1]=='\n')
    {
        word[strlen(word)-1] = '\0';
    }
    /*Ensures there is at least one characted/int contained in the word*/
    if((strcmp(word, "\n")!=0)&&(strcmp(word, "\0")!=0))
    {
        valid = 1;
    }
    
    return valid;
}
