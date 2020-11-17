/*
  Team Members: Vinh Tran (Email: kimvinh@csu.fullerton.edu)
								Quang Nguyen (Email: quangdnguyen2211@csu.fullerton.edu)
  Course: CPSC 351 - 04
  Professor: Kenytt Avery
  Project 5: Page-replacment Algorithm
*/

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void second_chance(int reference_string[], int pageReferencesLength, int number_of_frame) {
  cout << "\nSecond Chance Algorithm\n";

  vector<int> frame;
  int referenceBit[number_of_frame];
  // Initialize the value of referecne bit of each frame to 0 as default
	for (int i = 0; i < number_of_frame; i++) {
		referenceBit[i] = 0;
  }

  int victim_frame = 0;
  int page_fault_counter = 0;

  bool dup = false;

  // The loop will go until it reaches the end of the page-reference string
  for (int index = 0; index < pageReferencesLength; index++) {
    // The for loop is used to look if the page is already in the frame
    for (size_t c = 0; c < frame.size(); c++) {
      if (reference_string[index] == frame[c]) {
	      // It increases the bit at that frame by 1
        referenceBit[c] = 1;
	      // Because the step when the page is in frame and not in frame is different
	      // Therefore, dup is used to skip the steps of when the page is not in the frame
        dup = true;
        break;
      }
    }
    // If the page is not in the frame
    if (dup == false) {
      // Check if the capacity of 'frame' is full
      // If no, then put the page into 'frame'
      // Set the reference bit at the index of 'frame' to 1
			if ((int) frame.size() < number_of_frame) {
				frame.push_back(reference_string[index]);
				for (size_t c = 0; c < frame.size(); c++) {
					if (referenceBit[c] == 0) {
						referenceBit[c] = 1;
					}
				}
				page_fault_counter++;
				// Print out what is in the frame after each pass
      	for (size_t c = 0; c < frame.size(); c++) {
        	cout << frame[c] << " ";
      	}
      	cout << endl;
			} else {
        // If yes, then apply Second Chance Algorithm

        // Check the reference bit at each index of 'frame'
        // If it is 1, then set it to 0 and move to the next frame
        // If it is 0, then assign the new page into that index
				while (referenceBit[victim_frame] == 1) {
					referenceBit[victim_frame] = 0;
					victim_frame++;
					if (victim_frame >= number_of_frame) {
						victim_frame = 0;
					}
				}
      	// Making the replacement
      	frame[victim_frame] = reference_string[index];
				referenceBit[victim_frame] = 1;
				victim_frame++;
				if (victim_frame >= number_of_frame) {
					victim_frame = 0;
				}

      	// Print out what is in the frame after each pass
      	for (size_t c = 0; c < frame.size(); c++) {
        	cout << frame[c] << " ";
      	}
      	cout << endl;

      	page_fault_counter++;
    	}
		}
		// Set dup back to false if the page is already in the frame
		dup = false;
  }
  cout << "Page Faults = " << page_fault_counter << endl;
}
