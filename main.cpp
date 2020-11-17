/*
  Team Members: Vinh Tran (Email: kimvinh@csu.fullerton.edu)
								Quang Nguyen (Email: quangdnguyen2211@csu.fullerton.edu)
  Course: CPSC 351 - 04
  Professor: Kenytt Avery
  Project 5: Page-replacment Algorithm
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "OptimalPage.h"
#include "SecondChance.h"
#include "LFU.h"
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " number_of_frames\n";
    return EXIT_FAILURE;
  } else {
    srand(time(0));

    // Initialize the length of 'pageReferences' array
    const int length = 20;
    // Intialize 'pageReferences' array with the size of 'length'
    int pageReferences[length];
    // Store 'pageFrames' as the number of page frames from command-line argument
    int pageFrames = atoi(argv[1]);

    // Generate 100 random integers for 'pageReferences' array
    for (int i = 0; i < length; i++) {
      pageReferences[i] = rand() % 10;
    }

    // Show the contents of page-reference string
    cout << "Page-reference Strings:\n";
    for (int i = 0; i < length; i++) {
      cout << pageReferences[i] << " ";
    }
    cout << endl;
    // Do Second Chance Algorithm for Page Replacement
    second_chance(pageReferences, length, pageFrames);
    // Do Least Frequently Use Algorithm for Page Replacement
    LFU(pageReferences, length, pageFrames);
    // Do OPT Algorithm for Page Replacement
    optimalPageAlgorithm(pageReferences, length, pageFrames);
  }
  cout << endl;
  return EXIT_SUCCESS;
}
