//************************** ASSIGNMENT 3 ***********************************//
//
//  Name:       Reem Razak
//  ID:         0851987
//
//**************************************************************************//


**Please note that function descriptions are contained within the .c file***

***The following website was used to gain information on the algorithms needed for executing a binary tree properly***

http://www.dreamincode.net/forums/topic/37428-converting-and-evaluating-infix-postfix-and-prefix-expressions-in-c/

/******* RUNNING THE PROGRAM ***********************************************/

To compile the program enter the following command:

make

To run the program for the first question:
./q1 ‘expression’
**note that the expression must be fully parenthesized, and that the terminal will not accept input unless the expression is surrounded by single quotes

To run the program for the second question:
./q2 file

For Example
./q2 f.dat


/************* PROGRAM OUTPUT TESTS ***************************************/

// Q1//////////////////////////////////////////////////////////////

Test 1:

./q1
Please specify a parenthesized expression with no spaces in it in the command line



Test 2:
Welcome to the binary expression tree program
Please select one of the following
1.Display
2.Preorder
3.Inorder
4.PostOrder
5.Update
6.Calculate
7.Exit
9001203012903
Please selection from options 1 through 7
lpopop
Invalid Input. You must input an integer
a
Invalid Input. You must input an integer
7



Test 3:
./a.out '((2*3)/(4-5))'
Welcome to the binary expression tree program
Please select one of the following
1.Display
2.Preorder
3.Inorder
4.PostOrder
5.Update
6.Calculate
7.Exit
1
          /
      *    -
    2  3   4  5




Test 4:
./a.out '((2*3)/(4-5))'
Welcome to the binary expression tree program
Please select one of the following
1.Display
2.Preorder
3.Inorder
4.PostOrder
5.Update
6.Calculate
7.Exit
2
Preorder: / * 2 3 - 4 5 
Please select one of the following
1.Display
2.Preorder
3.Inorder
4.PostOrder
5.Update
6.Calculate
7.Exit
3
Inorder: ((2*3)/(4-5))
Please select one of the following
1.Display
2.Preorder
3.Inorder
4.PostOrder
5.Update
6.Calculate
7.Exit
4
Postorder: 2 3 * 4 5 - / 
Please select one of the following
1.Display
2.Preorder
3.Inorder
4.PostOrder
5.Update
6.Calculate
7.Exit



Test 5:
./a.out '((2*3)/(4-5))'
Welcome to the binary expression tree program
Please select one of the following
1.Display
2.Preorder
3.Inorder
4.PostOrder
5.Update
6.Calculate
7.Exit
5
Please enter which value you would like to change.
2
Please enter the value you would like to change it to.
4
Changing element
Please select one of the following
1.Display
2.Preorder
3.Inorder
4.PostOrder
5.Update
6.Calculate
7.Exit
1
          /
      *    -
    4  3   4  5


//Q2/////////////////////////////////////////////////////////////////
Hello
25 12 17 82 52 53 5 3 68 64 
43 27 20 59 4 84 10 42 43 2 
81 14 42 21 9 69 5 30 20 91 
96 89 75 0 63 24 54 20 20 24 
41 62 82 46 69 42 74 68 79 28 
50 9 6 44 59 87 32 36 36 46 
83 82 43 11 21 4 8 97 93 14 
3 60 76 23 14 81 82 0 38 4 
9 83 22 90 74 56 64 75 67 55 
41 82 53 40 29 84 24 61 87 20 
99 37 50 93 57 6 29 91 92 39 
25 41 11 88 15 39 88 69 31 49 
3 37 97 53 36 54 69 68 38 43 
44 27 68 96 70 98 85 13 25 47 
51 90 37 86 42 44 48 64 41 1 
16 14 27 99 29 99 79 45 59 19 
88 56 59 88 39 30 44 59 49 72 
49 17 44 32 33 54 60 33 51 87 
12 0 68 68 49 68 74 32 9 30 
81 30 16 65 40 39 44 49 32 60 



25 12 17 82 52 53 5 3 68 64 
16 14 27 99 29 99 79 45 59 19 
50 9 6 44 59 87 32 36 36 46 
12 0 68 68 49 68 74 32 9 30 
81 30 16 65 40 39 44 49 32 60 
25 41 11 88 15 39 88 69 31 49 
44 27 68 96 70 98 85 13 25 47 
43 27 20 59 4 84 10 42 43 2 
49 17 44 32 33 54 60 33 51 87 
41 82 53 40 29 84 24 61 87 20 
99 37 50 93 57 6 29 91 92 39 
81 14 42 21 9 69 5 30 20 91 
3 37 97 53 36 54 69 68 38 43 
51 90 37 86 42 44 48 64 41 1 
83 82 43 11 21 4 8 97 93 14 
3 60 76 23 14 81 82 0 38 4 
88 56 59 88 39 30 44 59 49 72 
9 83 22 90 74 56 64 75 67 55 
96 89 75 0 63 24 54 20 20 24 
41 62 82 46 69 42 74 68 79 28 