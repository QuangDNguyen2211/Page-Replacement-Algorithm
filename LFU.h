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
//using std::end;

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

  // Vector order is used to remembe the order that the page get into the frame
  vector<int> order;
  // least_frequent is used to find out the frame that is used the least
  int least_frequent;

  for (int index = 0; index < pageReferencesLength; index++) {
	  // Initialized least_frequent with the counter at the victim frame
		least_frequent = counter[victim_frame];
		for (int c = 0; c < number_of_frame; c++) {
			// If least_frequent is bigger than the counter of a frame, change the least_frequent to that counter
			if (least_frequent > counter[c] && first_fill == true) {
				least_frequent = counter[c];
      }
			// If the page is already in the frame, increment the counter at that frame by 1
			if (reference_string[index] == frame[c]) {
				counter[c] = counter[c] + 1;
				dup = true;

				break;
			}
		}

		if (dup == false) {
			// This is for when the frame still empty.
			// The program will move to the next available spot until it reaches the end of the frame
			if (first_fill == false) {
					frame[victim_frame] = reference_string[index];
					counter[victim_frame] = 1;
					order.push_back(victim_frame);
					victimFrame(victim_frame, number_of_frame, first_fill);
				}
			// The program will look for the least frequently	use page by comparing it to least_frequent
				else	{
					for (int c = 0; c < order.size(); c++) {
						// The program will check to see which page is the oldest, and is used the least to replace
						if (counter[order[c]] == least_frequent) {
							victim_frame = order[c];
							frame[victim_frame] = reference_string[index];
							counter[victim_frame] = 1;
							order.erase(order.begin() + c);
							order.push_back(victim_frame);
							break;
						}
					}
				}
      // Print out what is in the frame after each pass
      for (int c = 0; c < number_of_frame; c++) {
        if (frame[c] == -1) {
          continue;
        }
        cout << frame[c] << " ";
      }
      cout << endl;

			// Increment the number of page fault by 1.
			++page_fault_counter;
		}
		// Set dup back to false if the page is already in the frame
		dup = false;
	}
  cout << "Page Faults = " << page_fault_counter << endl;
}
