/*
  Team Members: Vinh Tran (Email: kimvinh@csu.fullerton.edu)
								Quang Nguyen (Email: quangdnguyen2211@csu.fullerton.edu)
  Course: CPSC 351 - 04
  Professor: Kenytt Avery
  Project 5: Page-replacment Algorithm
*/

#include <iostream>

using std::cout;
using std::end;

// The function is used to change the position of the victime frame
void victimFrame(int& victim_frame, int number_of_frame, bool &first_fill) {
	// If victime frame reaches the end, it will go back to the beginning
	if (victim_frame == number_of_frame - 1) {
		// First fill indicate that the frame has been fully filled for the first time
		first_fill = true;
		victim_frame = 0;
	}
	else {
		++victim_frame;
  }
}

void LFU(int reference_string[], int pageReferencesLength, int number_of_frame) {
  cout << "\nLeast Frequently Used (LFU) Algorithm\n";

  int frame[number_of_frame];
  int counter[number_of_frame];
	for (int i = 0; i < number_of_frame; i++) {
    frame[i] = -1;
		counter[i] = 0;
  }

  int victim_frame = 0;
  int page_fault_counter = 0;

  bool first_fill = false;
  bool dup = false;

  // Min is used to find out the frame that is used the least
  int min;

  for (int index = 0; index < pageReferencesLength; index++) {
	  // Initialized min with the counter at the victim frame
		min = counter[victim_frame];
		for (int c = 0; c < number_of_frame; c++) {
			// If min is bigger than the counter of a frame, change the victime frame to that frame
			if (min > counter[c] && first_fill == true) {
				victim_frame = c;
      }
			// If the page is already in the frame, increment the counter at that frame by 1
			if (reference_string[index] == frame[c]) {
				counter[c] = counter[c] + 1;
				dup = true;

				if (c == victim_frame) {
					victimFrame(victim_frame, number_of_frame, first_fill);
        }
				break;
			}
		}

		if (dup == false) {
			// Making the replacement and set the counter for that frame back to 0
			frame[victim_frame] = reference_string[index];
      // Print out what is in the frame after each pass
      for (int c = 0; c < number_of_frame; c++) {
        if (frame[c] == -1) {
          continue;
        }
        cout << frame[c] << " ";
      }
      cout << endl;
			counter[victim_frame] = 0;

			// Change the position of the victim frame
      			// Move to the next page, and increment the number of page fault by 1.
			victimFrame(victim_frame, number_of_frame, first_fill);
			++page_fault_counter;
		}
		// Set dup back to false if the page is already in the frame
		dup = false;
	}
  cout << "Page Faults = " << page_fault_counter << endl;
}
