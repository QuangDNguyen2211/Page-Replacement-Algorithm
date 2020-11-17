/*
  Team Members: Vinh Tran (Email: kimvinh@csu.fullerton.edu)
								Quang Nguyen (Email: quangdnguyen2211@csu.fullerton.edu)
  Course: CPSC 351 - 04
  Professor: Kenytt Avery
  Project 5: Page-replacment Algorithm
*/

#include <iostream>

using std::cout;
using std::endl;

// The function is used to change the position of the victime frame
void change_victim_frame(int& victim_frame, int number_of_frame, bool &first_fill) {
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

void second_chance(int reference_string[], int pageReferencesLength, int number_of_frame) {
  cout << "\nSecond Chance Algorithm\n";

  int frame[number_of_frame];
  for (int i = 0; i < number_of_frame; i++) {
    frame[i] = -1;
  }
  int counter[number_of_frame] = {};

  int victim_frame = 0;
  int page_fault_counter = 0;

  bool first_fill = false;
  bool dup = false;

  // The loop will go until it reaches the end of the reference string
  for (int index = 0; index < pageReferencesLength; index++) {
    // The for loop is used to look if the page is already in the frame
    for (int c = 0; c < number_of_frame; c++) {
      if (reference_string[index] == frame[c]) {
	      // If it is increase the counter at that frame, but it cannot be bigger than 1
        if(counter[c] < 1) {
          counter[c] = counter[c] + 1;
        }

	      // Decrement the counter of other frames by 1, but it cannot be smaller than 1
        for (int i = 0; i < number_of_frame; i++) {
          if (i == c) {
            continue;
          }
          if(counter[i] > 0) {
            counter[i] = counter[i] - 1;
          }
        }
	      // Because the step when the page is in frame and not in frame is different
	      // Therefore, dup is used to skip the steps of when the page is not in the frame
        dup = true;

	      // Change the position of the victim frame if it is at where the page is at.
        if (c == victim_frame) {
          change_victim_frame(victim_frame, number_of_frame, first_fill);
        }
        break;
      }
    }
    // If the page is not in the frame
    if (dup == false) {
      // If the victim frame has the counter at 1, move the victim frame to another next frame
      // Decrement the counter of that frame by 1
      if (counter[victim_frame] > 0) {
        counter[victim_frame] = counter[victim_frame] - 1;
        change_victim_frame(victim_frame, number_of_frame, first_fill);
      }

      // Making the replacement
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
      // If the frames have been filled for the first time, all the other frame will start be deducted by 1
      if (first_fill == true) {
        for (int c = 0; c < number_of_frame; c++) {
          if (c == victim_frame) {
            continue;
          }
          if (counter[c] > 0) {
            counter[c] = counter[c] - 1;
          }
        }
      }

      // Change the position of the victim frame
      // Move to the next page, and increment the number of page fault by 1.
      change_victim_frame(victim_frame, number_of_frame, first_fill);
      ++page_fault_counter;
    }
    // Set dup back to false if the page is already in the frame
    dup = false;
  }
  cout << "Page Faults = " << page_fault_counter << endl;
}
