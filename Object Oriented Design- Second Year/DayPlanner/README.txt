/*********** ASSIGNMENT 3*************/
//  Reem Razak
//  ID: 0851987
//  CIS*2430
//  28/11/2014


/****** The General Problem ********/

The point of this program is to maintain a DayPlanner which includes one array list of type Activity. The Activity object can either be of type subclass: Other,School, Home
The user can add new activities, or search for old ones.

The program runs off of a GUI, which makes it more user-friendly and easy to visualize. 

The most complex part of the assignment was learning how to use swing and implementing it properly.

/*******References**********/
the following images were altered and used in the implementation of the GUI

plane image:
http://wallpaperswa.com/thumbnails/detail/20120502/minimalistic%20monochrome%20paper%20plane%20flight%201920x1200%20wallpaper_wallpaperswa.com_31.jpg

bird image:
http://icons.iconarchive.com/icons/jozef89/origami-birds/512/bird-red-icon.png


/**** Limitations ******/
None known limitations

/*** Extensions *******/
For this project I have added a preferences option in the toolbar, where the user can change the look of the program. Here they can set the RGB values they would like to use for each main panel in the program

I have also added a check on exit window to confirm whether the user wants to quit

I have also added images

/*** Building and Running the program ****/
Navigate into the main DayPlanner folder
To compile the program:
cd src/a3
javac *.java

to run the program:

type:
java A3


if only one file is specified, it will be used as the output file and there will be no activities loaded into the program.

/***** Improvements ******/

If more time were given for this assignment I would have created more user-proofing methods, to ensure that it is very hard for the program to break. I would also have played around with swing more and tried to make the program look cleaner.

/********************************** Testing **********************************/

///////////////Add Activity Testing////////////

Test 1:
**Input**
Type: School
Title:
Starting Time:
Ending Time:
Comment:

**Result**
Invalid Entry: Please ensure all required fields are filled in. The time input should match the format specified, and the start time should be before the end time


Test 2:
**Input**
Type: Other
Title: One
Starting Time: 12/12/12 12:15
Ending Time: 12/12/12 12:12
Location: lalala
Comment:lalala

**Result**
Invalid Entry: Please ensure all required fields are filled in. The time input should match the format specified, and the start time should be before the end time


Test 3:
**Input**
Type:Home
Title: Three
Start Time: 12/12/12 12:11
Ending Time: 12/12/12 12:12
Comment: asdasd

**Result**
Successfully added Three to DayPlanner

///////////////Search Activity Testing///////////

Test 1:
**Input**
type:
title:
start time:
end time:

**Results**
Now printing search results:
*** one ***
12/12/12 12:12 to 12/12/12 12:12

*** two ***
12/12/12 12:12 to 12/12/12 12:12

*** three ***
location: 
12/12/12 12:12 to 12/12/12 12:12



Test 2:
**Input**
type: Other
title:
start time:
end time:

**Results**
Now printing search results:
*** three ***
location: 
12/12/12 12:12 to 12/12/12 12:12



Test 3:
**Input**
type: School
title:
start time:
end time:

**Result**
Now printing search results:
*** one ***
12/12/12 12:12 to 12/12/12 12:12



Test 4:
**Input**
type: 
title: asdasd
start time:
end time:

**Results**
Now printing search results:










