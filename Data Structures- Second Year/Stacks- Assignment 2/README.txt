//************************** ASSIGNMENT 1 ***********************************//
//
//  Name:       Reem Razak
//  ID:         0851987
//
//**************************************************************************//


**Please note that function descriptions are contained within the .c file***

***The following website was used to gain information on push pop functions in stacks for question 2***

http://cis.stvincent.edu/html/tutorials/swd/stacks/stacks.html

/******* RUNNING THE PROGRAM ***********************************************/

To compile the program enter the following command:

make

To run the program for the first question:
./q1 carlist.csv

To run the program for the second question:
./q2 postfix expression

For Example
./q2 23*5+


/************* PROGRAM OUTPUT TESTS ***************************************/

// Q1//////////////////////////////////////////////////////////////
Test 1:

Hello.
Please enter a transaction code (1-7) from below.
(1)Add a new car to the available-for-rent list
(2)Add a returned car to the available-for-rent list
(3)Add a returned car to the repair list
(4)Transfer a car from the repair list to the available-for-rent list
(5)Rent the first available car
(6)Print all the lists
(7)Quit
1
Please enter in a plate number
123
Please enter a mileage
=-=-=-==
Invalid Input. You must input an integer
200000
The new car with the plate 123 was added to the available-for-rent list


Test 2:
Hello.
Please enter a transaction code (1-7) from below.
(1)Add a new car to the available-for-rent list
(2)Add a returned car to the available-for-rent list
(3)Add a returned car to the repair list
(4)Transfer a car from the repair list to the available-for-rent list
(5)Rent the first available car
(6)Print all the lists
(7)Quit
=-==-==-== -==-21
Invalid Input. You must input an integer
8
Please selection from options 1 through 7
2
Please enter in a plate number
123
Please enter a mileage
123123
The plate does not exist in the rented list

Test 3:
Please enter a transaction code (1-7) from below.
(1)Add a new car to the available-for-rent list
(2)Add a returned car to the available-for-rent list
(3)Add a returned car to the repair list
(4)Transfer a car from the repair list to the available-for-rent list
(5)Rent the first available car
(6)Print all the lists
(7)Quit
6


**Now printing the available-to-rent list**
License: 1 Return Date: None Mileage:100
License: 2 Return Date: None Mileage:200
License: 3 Return Date: None Mileage:300
License: 4 Return Date: None Mileage:400
License: 5 Return Date: None Mileage:500
License: 123 Return Date: None Mileage:200000


**Now printing the rented list**
License: 7 Return Date: 120101 Mileage:1000
License: 8 Return Date: 120202 Mileage:11000
License: 8 Return Date: 120203 Mileage:12000
License: 9 Return Date: 120404 Mileage:13000
License: 6 Return Date: 140602 Mileage:900


**Now printing the repair list**
License: 1 Return Date: None Mileage:100
License: 2 Return Date: None Mileage:200
License: 3 Return Date: None Mileage:300
License: 4 Return Date: None Mileage:400
License: 5 Return Date: None Mileage:1000

//Q2/////////////////////////////////////////////////////////////////
input:
./q2 23*5+
answer:
The answer is 11.00

input:
./q2 15+6*
answer:
The answer is 36.00

input:
./q2 18*2+3-
answer:
The answer is 7.00