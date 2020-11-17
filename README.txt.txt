Members: Quang Nguyen
	   Vinh Tran
CPSC 351-04
Professor: Kenytt Avery
Project 5: Page Replacement Algorithm

----------------------------------------------------------------------------------------------------------------------------------------------

SUMMARY:
The program is designed to show how page-replacement works with 3 different algorithms. The 3 different algorithms are Second-Chance, 
Least Frequently Use, and OPT. The output will be the random generated page-reference string and the number of page faults that happend
 with each algorithms.

DOCUMENTATION
 * The program will take 2 arguments. The second argument is to declare the number of frame that the user wants.
 * The program will first randomly generate 100 pages of the page-reference string then print it out to the terminal. Each string is different for each algorithm.
 * After that, the function change_victim_frame is created. The main reason for this function is to stop the repetitive code whenever the program need to
change the victim frame for its algorithm, which happends a lot.
 * The first algorithm is Second-Chance algorithm:
	. The function will pass the page-reference string, and the number of frame as arguments
	. The function will go through a while loop until it reaches the length of the page-reference string
	. The function will go through the page-reference string one by one to look if the page is already in the frame or not
	. If the page is already in the frame, the counter for that frame will turn to 1, and it can't be bigger than 1. All other frame will be deducted by 1, if it is bigger than 0.
	. If the page is not in the frame, then that page will be added to the frame, and all the frame counter will be deducted by 1. However, if the counter at the victim frame is 1,
 	the victim frame move on to the next one, and that counter get deducted by 1.
	. The victim frame start at frame 0, and will increase after every loop. However, if it equals to the number of frame, it go back to 0.
* The second algorithm is Least Frequently Use:
	. The function will pass the page-reference string, and the number of frame as arguments
	. The function will go through a while loop until it reaches the length of the page-reference string
	. The function will go through the page-reference string one by one to look if the page is already in the frame or not
	. If the page is already in the frame, the counter for that frame increases by 1.
	. If the page is not in the frame, the frame with the lowest counter get replaced.
	. The victim frame start at frame 0, and will increase after every loop. However, if it equals to the number of frame, it go back to 0.


----------------------------------------------------------------------------------------------------------------------------------------------

"CPSC-351-Project5.tar.gz" Contents:

1. README.txt       // This file