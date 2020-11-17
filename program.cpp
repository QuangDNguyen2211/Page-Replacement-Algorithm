#include <iostream>

using namespace std;

// The function is used to change the position of the victime frame
void chage_victim_frame(int& victim_frame, int number_of_frame, bool &first_fill)
{
	// If victime frame reaches the end, it will go back to the beginning
	if (victim_frame == number_of_frame - 1)
	{
		// First fill indicate that the frame has been fully filled for the first time
		first_fill = true;
		victim_frame = 0;
	}
	else
		++victim_frame;
}

void second_chance(int reference_string[], int number_of_frame)
{
  int frame[number_of_frame];
  int counter[number_of_frame] = {};

  int victim_frame = 0;
  int string_position = 0;
  int page_fault_counter = 0;

  bool first_fill = false;
  bool dup = false;
	
  // The loop will go until it reaches the end of the reference string
  while (true)
  {
    // The for loop is used to look if the page is already in the frame
    for (int c = 0; c < number_of_frame; c++)
    {
      if (reference_string[string_position] == frame[c])
      {
	// If it is increase the counter at that frame, but it cannot be bigger than 1
        if(counter[c] < 1)
          counter[c] = counter[c] + 1;

	// Decrement the counter of other frames by 1, but it cannot be smaller than 1      
        for (int i = 0; i < number_of_frame; i++)
        {
          if (i == c)
            continue;
          if(counter[i] > 0)
            counter[i] = counter[i] - 1;
        }
	// Because the step when the page is in frame and not in frame is different
	// Therefore, dup is used to skip the steps of when the page is not in the frame
        dup = true;
	
	// Change the position of the victim frame if it is at where the page is at.
        if (c == victim_frame)
          chage_victim_frame(victim_frame, number_of_frame, first_fill);
	// Move on to the next page
        ++string_position;

        break;
      }
    }
    // If the page is not in the frame			
    if (dup == false)
    {
      // If the victim frame has the counter at 1, move the victim frame to another next frame
      // Decrement the counter of thaat frames by 1
      if (counter[victim_frame] > 0)
      {
        counter[victim_frame] = counter[victim_frame] - 1;
        chage_victim_frame(victim_frame, number_of_frame, first_fill);
      }
	
      // Making the replacement    
      frame[victim_frame] = reference_string[string_position];
      counter[victim_frame] = 0;
      // If the frames have been filled for the first time, all the other frame will start be deducted by 1
      if (first_fill == true)
      {
        for (int c = 0; c < number_of_frame; c++)
        {
          if (c == victim_frame)
            continue;
          if (counter[c] > 0)
            counter[c] = counter[c] - 1;
        }
      }
	    
      // Change the position of the victim frame
      // Move to the next page, and increment the number of page fault by 1.
      chage_victim_frame(victim_frame, number_of_frame, first_fill);
      ++string_position;
      ++page_fault_counter;
    }
    // Set dup back to false if the page is already in the frame
    dup = false;

    // Print out what is in the frame after each pass
    for (int c = 0; c < number_of_frame; c++)
      cout << frame[c];
    cout << endl;

    // If it reaches the length of the page reference string, it will exit and print out the number of page fault	  
    if (string_position == 12)
    {
      cout << "Number of times that page fault happended: " << page_fault_counter << endl;
      break;
    }
  }
}

void LFU(int reference_string[], int number_of_frame)
{
  int frame[number_of_frame];
  int counter[number_of_frame] = {};

  int victim_frame = 0;
  int string_position = 0;
  int page_fault_counter = 0;

  bool first_fill = false;
  bool dup = false;

  // Min is used find out the frame that is used the least
  int min;

  while (true)
	{
	        // Initialized min with the counter at the victim frame
		min = counter[victim_frame];
		for (int c = 0; c < number_of_frame; c++)
		{
			// If min is bigger than the counter of a frame, change the victime frame to that frame
			if (min > counter[c] && first_fill == true)
				victim_frame = c;
			// If the page is already in the frame, increment the counter at that frame by 1
			if (reference_string[string_position] == frame[c])
			{
				counter[c] = counter[c] + 1;
				dup = true;

				if (c == victim_frame)
					chage_victim_frame(victim_frame, number_of_frame, first_fill);
				++string_position;

				break;
			}
		}

		if (dup == false)
		{
			// Making the replacement and set the counter for that frame back to 0
			frame[victim_frame] = reference_string[string_position];
			counter[victim_frame] = 0;
				
			// Change the position of the victim frame
      			// Move to the next page, and increment the number of page fault by 1.
			chage_victim_frame(victim_frame, number_of_frame, first_fill);
			++string_position;
			++page_fault_counter;
		}
		// Set dup back to false if the page is already in the frame
		dup = false;
	  
		 // Print out what is in the frame after each pass
		for (int c = 0; c < number_of_frame; c++)
			cout << frame[c];
		cout << endl;
		// If it reaches the length of the page reference string, it will exit and print out the number of page fault	  
		if (string_position == 12)
    {
      cout << "Number of times that page fault happended: " << page_fault_counter << endl;
			break;
    }
	}
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    // Display the error message
    perror("The number of argument(s) is not right in the command line.\n");
    return EXIT_FAILURE;
  }
  else
  {
    char *p;
    long conv = strtol(argv[1], &p, 10);
  	const int number_of_frame = conv;

  	int reference_string[12] = {7,0,1,2,0,3,0,4,2,3,0,3};

    second_chance(reference_string, number_of_frame);
    cout << endl << endl;
    LFU(reference_string, number_of_frame);
  }
	return EXIT_SUCCESS;
}
