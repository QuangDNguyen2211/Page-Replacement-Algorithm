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

void optimalPageAlgorithm(int [], int, int);
bool avaliable(int, vector<int>);
int replacePage(int [], int, vector<int>, int);

int replacePage(int pageReferences[], int pageReferencesLength, vector<int> frames, int position) {
  int notUsedLongest = position;

  // Initialize 'victim' to indicate the appropriate index of 'frames'
  int victim;

  // Find the appropriate index of 'frames'
  // containing page-reference string that will not be used for the longest period of time
  for (size_t i = 0; i < frames.size(); i++) {
    int indexReference = position;
    while (indexReference < pageReferencesLength) {
      if (frames[i] == pageReferences[indexReference]) {
        if (indexReference > notUsedLongest) {
          notUsedLongest = indexReference;
          victim = i;
        }
        break;
      }
      indexReference++;
    }
    // If there is a page-reference string at the index of 'frames' is no longer used
    // then return that index
    if (indexReference == pageReferencesLength) {
      victim = i;
      return victim;
    }
  }
  return victim;
}

// Check if the page-reference string exists in the frames
// If yes, then return 'true' to indicate that the page-reference string was already existed
// Otherwise, return 'false' to indicate that the page-reference string does not exist
bool available(int reference, vector<int> frames) {
  for (size_t i = 0; i < frames.size(); i++) {
    if (frames[i] == reference) {
      return true;
    }
  }
  return false;
}

void optimalPageAlgorithm(int pageReferences[], int pageReferencesLength, int pageFrames) {
  vector<int> frames;
  int pageFault = 0;

  cout << "\nOptimal Page Algorithm\n";

  for (int i = 0; i < pageReferencesLength; i++) {
    if (available(pageReferences[i], frames)) {
      continue;
    } else {
      // Check if the capacity of 'frames' is full
      // If no, then put the page-reference string into 'frames'
      if ((int) frames.size() < pageFrames) {
        frames.push_back(pageReferences[i]);
        pageFault++;
        for (size_t i = 0; i < frames.size(); i++) {
          cout << frames[i] << " ";
        }
        cout << endl;
      } else {
        // If yes, call function 'replacePage()' to find the appropriate index of 'frames'
        // Then assign the new page-reference string into 'frames' at that index
        int victim = replacePage(pageReferences, pageReferencesLength, frames, i + 1);
        frames[victim] = pageReferences[i];
        pageFault++;
        for (size_t i = 0; i < frames.size(); i++) {
          cout << frames[i] << " ";
        }
        cout << endl;
      }
    }
  }
  // Display the number of page faults
  cout << "Page Faults = " << pageFault;
}
