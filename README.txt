# Members: Quang Nguyen
	   Vinh Tran

# CPSC 351-04

# Professor: Kenytt Avery

# Project 5: Page Replacement Algorithm

----------------------------------------------------------------------------------------------------------------------------------------------

## SUMMARY:

The program is designed to show how page-replacement works with 3 different algorithms. 
Three different algorithms for page-replacement are Second-Chance, Least Frequently Use, and OPT. 
The output of the program will contain:
 * The contents of 100 random pages in the page-reference strings
 * The processes of replacing pages at the appropriate index of the page frame
 * The number of page faults that happend with each algorithms.

## DOCUMENTATION

The program will take 2 arguments. The second argument is to declare the number of page frames that
the user wants.

The program will first randomly generate 100 pages which range from 0 to 9 for the page-reference string
then print it out to the terminal.

After that, the function and victimeFrame() in "LFU.h" is created. 
The main reason for this function is to stop the repetitive code whenever the program need to change 
the victim frame for its algorithm, which happends a lot.
 * The first algorithm is Second-Chance algorithm:
   . The function will pass the page-reference string, the length of the page-reference string and the number of frame as arguments
   . The function will go through a for loop until it reaches the length of the page-reference string
   . The function will go through the page-reference string one by one to look if the page is already in the frame or not
   . If the page is already in the frame, the reference bit for that frame will turn to 1.
   . If the page is not in the frame and the page frames are not full, then that page will be added to
     the frame, and the reference bit for that frame will be 1.
   . If the page is not in the frame but the page frames are full, then check the reference bit at each index
     of the frame.
     If the bit is 1, then set it to 0 and move to the next frame.
     If the bit is 0, then assign the new page into that index of the frame and set the bit to 1.
   . The victim frame starts at frame 0, and will increase after every loop. However, if it is greater or equal to the number of frame,
     it go back to 0.

  * The second algorithm is Least Frequently Use (LFU):
   . The function will pass the page-reference string, the length of the page-reference string and the number of frame as arguments
   . The function will go through a for loop until it reaches the length of the page-reference string
   . The function will go through the page-reference string one by one to look if the page is already in the frame or not
   . There will be a vector order to remember the order of which the page get assigned to the frame.
   . If the page is already in the frame, the counter for that frame increases by 1.
   . If the page is not in the frame, the oldest page with the lowest counter get replaced.

 * The third algorithm is Optimal Page-replacement (OPT):
   . The function will pass the page-reference string, the length of the page-reference string and the number of frame as arguments
   . The function will go through a for loop until it reaches the length of the page-reference string
   . The function will go through the page-reference string one by one to look if the page is already in the frame or not
   . If the page is not in the frame and the page frames are not full, put that page into the frame.
     If the page is not in the frame but the page frames are full, then find the appropriate index of the frame,
     and assign the new page into the frame at that index containing the page that will not be used for the longest period of time.
   . If the page is already in the frame, then move to the next page in the page-reference string.

----------------------------------------------------------------------------------------------------------------------------------------------

## "CPSC-351-Project5.tar.gz" Contents:

1. README.txt       // This file

2. main.cpp         // main program that run page-replacement algorithms

3. OptimalPage.h    // header file containing OPT Algorithm

4. SecondChance.h   // header file containing Second Chance Algorithm

5. LFU.h            // header file containing Least Frequently Used (LFU) Algorithm

## Compile and Run The Program

1. To compile the source code, command:
$ c++ -o PageReplacement -std=c++ -Wall main.cpp        // "PageReplacement" is created as the executive file

2. To run the program, command:
$ ./PageReplacement [number_of_frames]

For example, if you want to set up number of frames which are 3, then command:
$ ./PageReplacement 3

Or, if you want to set up number of frames which are 4, then command:
$ ./PageReplacement 4
