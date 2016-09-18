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
#include <math.h>

#define BUFFER_SIZE 1024


struct car * addCar(int mileage, int returnDate, char * plate);
struct car * orderByMileage(struct car *  theList, struct car * toBeAdded);
void printList(struct car *  theList, char printType, FILE * playlist);
char * printRecord(struct car * toPrint, char printType);
void  freeList(struct car * theList);
void destroyRecord(struct car * theRecord);
struct car * removeFromList(struct car **  theList, char * plate);
struct car * orderByReturn(struct car *  theList, struct car * toBeAdded);
double transactionCalculator(int mileage);
int intCheck();

struct car{
    int mileage;
    int returnDate;
    char * plate;
    struct car * next;
    
};

int main(int argc, char * argv[])
{
    
    int choice = 0;
    int forRentEmpty = 1;
    int rentedEmpty = 1;
    int repairEmpty = 1;
    char * plate;
    //printType is either (a)vailable for rent, (b)rented, (c)in repair, or (e)mpty
    char printType = 'e';
    int mileage;
    int returnDate;
    int numOfDigits;
    int day;
    int month;
    double total = 0;
    double subTotal = 0;
    struct car * firstForRent = NULL;
    struct car * nextForRent = NULL;
    struct car * firstRented = NULL;
    struct car * nextRented = NULL;
    struct car * firstInRepair = NULL;
    struct car * nextInRepair = NULL;
    struct car * listChange = NULL;
    
    FILE * playlist;
    char * theString;
    
    char * theTypeToken;
    char theType;
    
    char line[BUFFER_SIZE];



/*Opens the file and strtoks each section of each line into the corresponding variable. For example, the bit of data that preceeds the first comma will be copied into mileage as an integer. The program then sorts each car into the appropriate list (available for rent, rented, and in repair)
 */
 
    if (argc != 2)
    {
        printf("Please specify a file\n");
        exit(1);
    }
    playlist = fopen(argv[1], "r+");
    if(playlist == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    while((fgets(line, sizeof(line), playlist))!=NULL)
    {
        theString = malloc(sizeof(char)*(strlen(line)+1));
        
        strcpy(theString, line);
        mileage = atoi(strtok(theString, ","));
        returnDate = atoi(strtok(NULL, ","));
        plate = strtok(NULL, ",");
        theTypeToken = strtok(NULL, ",");
        theType = theTypeToken[0];
        
        /* a = available for rent
         b = rented
         c = in repair
         */
        if((forRentEmpty == 1)&&(theType == 'a'))
        {
            firstForRent = addCar(mileage, returnDate, plate);
            forRentEmpty = 0;

        }
        else if((rentedEmpty == 1)&&(theType == 'b'))
        {
            firstRented = addCar(mileage, returnDate, plate);
            rentedEmpty = 0;
        }
        
        else if((repairEmpty == 1)&&(theType == 'c'))
        {
            firstInRepair = addCar(mileage, returnDate, plate);
            repairEmpty = 0;
        }
        
        else if((forRentEmpty == 0)&&(theType == 'a'))
        {
            nextForRent = addCar(mileage, returnDate, plate);
            firstForRent = orderByMileage(firstForRent, nextForRent);
        }
        else if((rentedEmpty == 0)&&(theType == 'b'))
        {
            nextRented = addCar(mileage, returnDate, plate);
            firstRented = orderByReturn(firstRented, nextRented);
        }
        else if((repairEmpty == 0)&&(theType == 'c'))
        {
            nextInRepair = addCar(mileage, returnDate, plate);
            firstInRepair = orderByMileage(firstInRepair, nextInRepair);
        }
        
    }


    
    printf("Hello.");
    while(choice != 7)
    {
        printf("\nPlease enter a transaction code (1-7) from below.\n");
        printf("(1)Add a new car to the available-for-rent list\n(2)Add a returned car to the available-for-rent list\n(3)Add a returned car to the repair list\n(4)Transfer a car from the repair list to the available-for-rent list\n(5)Rent the first available car\n(6)Print all the lists\n(7)Quit\n");
        /*The following ensures that the user selects an integer between 1 & 7, and executes accordingly*/
        choice = intCheck();
        while((choice!=1)&&(choice!=2)&&(choice!=3)&&(choice!=4)&&(choice!=5)&&(choice!=6)&&(choice!=7))
        {
            printf("Please selection from options 1 through 7\n");
            choice = intCheck();
        }
        /*For choice 1 the user inputs a plate and a mileage, and the information is stored into the available for rent list*/
        if(choice == 1)
        {
            returnDate = 0;
            printf("Please enter in a plate number\n");
            scanf("%s", plate);
            printf("Please enter a mileage\n");
            mileage = intCheck();
            
            if(forRentEmpty == 1)
            {
                firstForRent = addCar(mileage, returnDate, plate);
                forRentEmpty = 0;
                
            }
            else
            {
                nextForRent = addCar(mileage, returnDate, plate);
                firstForRent = orderByMileage(firstForRent, nextForRent);
            }
            printf("The new car with the plate %s was added to the available-for-rent list\n", plate);
        }
        /*Transfers a rented car to the available for rent list. The user enters a plate, the plate is searched for in the rented list, and removed if found. The information for the car with that plate is then entered into the available for rent list. The total and subtotal are calculated and the subtotal is printed*/
        else if(choice == 2)
        {
            if(firstRented == NULL)
            {
                printf("The rented list is empty. There are no cars to return\n");
            }
            else
            {
                printf("Please enter in a plate number\n");
                scanf("%s", plate);
                printf("Please enter a mileage\n");
                mileage = intCheck();
                
                
                listChange = removeFromList(&firstRented, plate);
                if(firstRented == NULL)
                {
                    rentedEmpty = 1;
                }
                
                if(listChange == NULL)
                {
                    printf("The plate does not exist in the rented list\n");
                }
                else if(forRentEmpty == 1)
                {
                    firstForRent = addCar(listChange->mileage, listChange->returnDate,listChange->plate);
                    firstForRent->mileage = mileage;
                    firstForRent->returnDate = 0;
                    forRentEmpty = 0;
                }
                else
                {
                    nextForRent = addCar(listChange->mileage, listChange->returnDate, listChange->plate);
                    nextForRent->mileage = mileage;
                    nextForRent->returnDate = 0;
                    firstForRent = orderByMileage(firstForRent, nextForRent);
                    
                }
                if(listChange != NULL)
                {
                    subTotal = transactionCalculator(mileage);
                    total = total + subTotal;
                    printf("The  car with the plate %s was move from the rented list to the available-for-rent list\n", plate);
                    printf("The total for your transaction is $%.2lf\n", subTotal);
                }
            }

        }
        /*Transfers a rented car to the repair list. The user enters a plate, the plate is searched for in the rented list, and removed if found. The information for the car with that plate is then entered into the available for rent list. The total and subtotal are calculated and the subtotal is printed*/
        else if(choice == 3)
        {
            if(firstRented == NULL)
            {
                printf("The rented list is empty. There are no cars to return\n");
            }
            else
            {
                printf("Please enter in a plate number\n");
                scanf("%s", plate);
                printf("Please enter a mileage\n");
                mileage = intCheck();

                
                listChange = removeFromList(&firstRented, plate);
                if(firstRented == NULL)
                {
                    rentedEmpty = 1;
                }
                
                if(listChange == NULL)
                {
                    printf("The plate does not exist in the rented list\n");
                }
                else if(repairEmpty == 1)
                {
                    firstInRepair = addCar(listChange->mileage, listChange->returnDate,listChange->plate);
                    firstInRepair->mileage = mileage;
                    firstInRepair->returnDate = 0;
                    repairEmpty = 0;
                }
                else
                {
                    nextInRepair = addCar(listChange->mileage, listChange->returnDate, listChange->plate);
                    nextInRepair->mileage = mileage;
                    nextInRepair->returnDate = 0;
                    firstInRepair = orderByMileage(firstInRepair, nextInRepair);
                    
                }
                if(listChange != NULL)
                {
                    subTotal = transactionCalculator(mileage);
                    total = total + subTotal;
                    printf("The  car with the plate %s was move from the rented list to the repair list\n", plate);
                    printf("The total for your transaction is $%.2lf\n", subTotal);
                }
                
            }


        }
        /*Transfers a car in the repair list to the available for rent list. The user enters a plate, the plate is searched for in the repair list, and removed if found. The information for the car with that plate is then entered into the available for rent list.*/
        else if(choice  == 4)
        {
            if(firstInRepair == NULL)
            {
                printf("The repair list is empty\n");
            }
            else
            {
                printf("Please enter a plate number\n");
                scanf("%s", plate);


                listChange = removeFromList(&firstInRepair, plate);
                if(firstInRepair == NULL)
                {
                    repairEmpty = 1;
                }

                if(listChange == NULL)
                {
                    printf("The plate does not exist in the repair list\n");
                }
                else if(forRentEmpty == 1)
                {
                    firstForRent = addCar(listChange->mileage, listChange->returnDate,listChange->plate);
                    forRentEmpty = 0;
                }
                else
                {
                    nextForRent = addCar(listChange->mileage, listChange->returnDate, listChange->plate);
                    firstForRent = orderByMileage(firstForRent, nextForRent);

                }
                if(listChange != NULL)
                {
                    printf("The  car with the plate %s was move from the repair list to the available-for-rent list\n", plate);
                }
            }


        }
        /*Transfers the car at the head of the available-for-rent list to the rented list. The user is prompted for the return date, which must have 6 digits and be in the form yymmdd. If the user enters a month or day-of-the-month which doesn't exist (ex. month 13), and error message pops up and the user is re-prompted*/
        else if(choice == 5)
        {
            if(firstForRent == NULL)
            {
                printf("There are no available cars for rent\n");
                
            }
            else
            {
                printf("Please enter a transaction date (yymmdd)\n");
                returnDate = intCheck();
                numOfDigits = floor(log10(abs(returnDate))) + 1;
                day = returnDate % 100;
                month = returnDate % 10000;
                month = month - day;
                while((numOfDigits != 6)||(month > 31000)||(month < 100)||(day > 31)||(day < 0 ))
                {
                    printf("Your input must be 6 digits long in the form of [yymmd]\nThe month must be between 01-12 and the day must be between 01-31\n");
                    returnDate = intCheck();
                    numOfDigits = floor(log10(abs(returnDate))) + 1;
                    day = returnDate % 100;
                    month = returnDate % 10000;
                    month = month - day;
                }
                printf("%d\n%d\n", day, month);

                firstForRent->returnDate = returnDate;
                listChange = removeFromList(&firstForRent, firstForRent->plate);
                
                if(firstForRent == NULL)
                {
                    forRentEmpty = 1;
                }

                if(rentedEmpty == 1)
                {
                    firstRented = addCar(listChange->mileage, listChange->returnDate,listChange->plate);
                    rentedEmpty = 0;
                    
                }
                else
                {
                    nextRented = addCar(listChange->mileage, listChange->returnDate, listChange->plate);
                    firstRented = orderByReturn(firstRented, nextRented);
                }
                if(listChange != NULL)
                {
                    printf("The car with the plate %s was move from the available-for-rent list to the rented list\n", plate);
                }
            }

            
        }
        /*Prints all the lists*/
        else if(choice == 6)
        {
            
            if(forRentEmpty == 0)
            {
                printf("\n\n**Now printing the available-to-rent list**\n");
                printList(firstForRent, printType, playlist);
            }
            else
            {
                printf("The available-to-rent list is empty\n");
            }
            if(rentedEmpty == 0)
            {
                printf("\n\n**Now printing the rented list**\n");
                printList(firstRented, printType, playlist);
            }
            else
            {
                printf("The rented list is empty\n");
            }
            if(repairEmpty == 0)
            {
                printf("\n\n**Now printing the repair list**\n");
                printList(firstInRepair, printType, playlist);
            }
            else
            {
                printf("The repair list is empty\n");
            }
        }

    }
    
/*Writes all the car list information back to the file*/
    printf("Your total comes to: $%.2lf\n", total);
    playlist = fopen(argv[1], "wt");

    if(forRentEmpty == 0)
    {
        printList(firstForRent, 'a', playlist);
    }
    if(rentedEmpty == 0)
    {
        printList(firstRented, 'b', playlist);
    }

    if(repairEmpty == 0)
    {
        printList(firstInRepair, 'c', playlist);
    }
    
    
    free(theString);
    if(forRentEmpty == 0)
    {
        freeList(firstForRent);
    }
    if(repairEmpty == 0)
    {
        freeList(firstInRepair);

    }
    if(rentedEmpty == 0)
    {
        freeList(firstRented);

    }
    return 0;
    
    fclose(playlist);

}

//Other functions


/*Calculates total based on mileage*/
double transactionCalculator(int mileage)
{
    double total = 40;
    
    if(mileage > 100)
    {
        total = total + ((mileage - 100) * (0.15));
    }
    

    return total;
}
/*removes a car from a list. The list is sent a plate, which the functions searches for in the received list. If the plate is found, the car with that plate is removed from the list*/
struct car * removeFromList(struct car **  theList, char * plate)
{
    struct car * second;
    struct car * first;

    if((*theList) == NULL)
    {
        printf("NULLLLL\n\n");
        return NULL;
    }

    
    if(strcmp((*theList)->plate,plate) == 0)
    {
        first = *theList;
        *theList = (*theList)->next;
        first->next = NULL;
        return first;
        
    }
    
    else
    {
        first = *theList;
        second = (*theList)->next;

        /*Loop until you reach the end or you reach the plate*/

        while(second != NULL && strcmp(second->plate , plate) != 0)
        {
            second = second->next;
            first = first->next;
        }
        if(second == NULL)
        {
            return NULL;
        }
        first->next = second->next;
    }
    return second;
    
}


/*creates a new car struct with mileage returnDate and plate sent to function*/

struct car * addCar(int mileage, int returnDate, char * plate)
{
    struct car * newCar;
    newCar = malloc(sizeof(struct car));
    newCar->plate = malloc(sizeof(char)*(strlen(plate)+1));
    strcpy(newCar->plate, plate);
    newCar->mileage = mileage;
    newCar->returnDate = returnDate;
    newCar->next = NULL;
    if(newCar == NULL)
    {
        return NULL;
    }
    
    return newCar;
}

/*Orders the sent list by mileage. The lowest mileage is place at the head of the list*/
struct car * orderByMileage(struct car *  theList, struct car * toBeAdded)
{
    struct car * temp;
    struct car * temp1;
    struct car * second;
    temp = theList;
    second = theList->next;
    int i;
    int position = 1;


    while(((temp->mileage) < (toBeAdded->mileage))&&(temp->next != NULL))
    {
        temp = temp->next;
        position++;
    }
    if((temp->next == NULL)&&(temp->mileage < toBeAdded->mileage))
    {
        position++;
    }
    if(position == 1)
    {
        temp = theList;
        theList = toBeAdded;
        toBeAdded->next = temp;
        return theList;
    }
    temp = theList;
    for(i=1; i < (position-1) ; i++)
    {
        temp = temp->next;
    }
    
    temp1=temp->next;
    temp->next = toBeAdded;
    toBeAdded->next=temp1;
    
    return theList;
}

/*Orders the sent list by returnDate. The lowest returnDate is place at the head of the list*/

struct car * orderByReturn(struct car *  theList, struct car * toBeAdded)
{
    struct car * temp;
    struct car * temp1;
    struct car * second;
    temp = theList;
    second = theList->next;
    int i;
    int position = 1;
    
    
    while(((temp->returnDate) < (toBeAdded->returnDate))&&(temp->next != NULL))
    {
        temp = temp->next;
        position++;
    }
    if((temp->next == NULL)&&(temp->returnDate < toBeAdded->returnDate))
    {
        position++;
    }
    
    if(position == 1)
    {
        temp = theList;
        theList = toBeAdded;
        toBeAdded->next = temp;
        return theList;

    }
    temp = theList;
    for(i=1; i < (position-1) ; i++)
    {
        temp = temp->next;
    }
    
    temp1=temp->next;
    temp->next = toBeAdded;
    toBeAdded->next=temp1;
    
    return theList;
}

/*Prints the list by cycling through and calling the print record function. The printRecord function returns a string with the info of the individal record, which is then printed by the printList function*/
void printList(struct car *  theList, char printType, FILE * playlist)
{
    char * theString;
    struct car * temp;
    temp = theList;
    if(printType == 'e')
    {
        while(temp != NULL)
        {
            theString = printRecord(temp, printType);
            printf("%s\n", theString);
            temp = temp->next;
           // free(theString);
        }
    }
    else
    {

        while(temp != NULL)
        {
            theString = printRecord(temp, printType);
            fprintf(playlist,"%s", theString);
            temp = temp->next;
            // free(theString);
        }
    }
}
/*Prints an individual record of a list into a string.*/
char * printRecord(struct car * toPrint, char printType)
{
    int length = (strlen(toPrint->plate) + 2000);
    char * printString = malloc(sizeof(char) * length);
    if(printType == 'e')
    {
        char * date = malloc(sizeof(int)*length);
        if(toPrint->returnDate == 0)
        {
            sprintf(date, "None");
        }
        else
        {
            sprintf(date, "%d", toPrint->returnDate);
        }
        sprintf(printString, "License: %s Return Date: %s Mileage:%d", toPrint->plate, date, toPrint->mileage);
        free(date);
    }
    else
    {
        if(printType == 'a')
        {
            sprintf(printString,"%d,%d,%s,a,\n", toPrint->mileage, toPrint->returnDate, toPrint->plate);
        }
        else if(printType == 'b')
        {
            sprintf(printString,"%d,%d,%s,b,\n", toPrint->mileage, toPrint->returnDate, toPrint->plate);
        }
        else if(printType == 'c')
        {
            sprintf(printString,"%d,%d,%s,c,\n", toPrint->mileage, toPrint->returnDate, toPrint->plate);

        }
    }
    return printString;
}

/*Frees the list by cycling through and calling destroyRecord for each individual record*/
void  freeList(struct car * theList)
{
    struct car * current;
    struct car * next;
    current = theList;
    next = theList->next;
    while(current->next!=NULL)
    {
        next = current->next;
        destroyRecord(current);
        free(current);
        current = next;
    }
    theList = NULL;
}

void destroyRecord(struct car * theRecord)
{
    free(theRecord->plate);
}

/*userProofs to ensure an integer is ented by the user.*/
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

