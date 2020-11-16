#include <iostream>

using namespace std;

void chage_victim_frame(int& victim_frame, int number_of_frame, bool &first_fill)
{
	if (victim_frame == number_of_frame - 1)
	{
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

  while (true)
  {
    for (int c = 0; c < number_of_frame; c++)
    {
      if (reference_string[string_position] == frame[c])
      {
        if(counter[c] < 1)
          counter[c] = counter[c] + 1;

        for (int i = 0; i < number_of_frame; i++)
        {
          if (i == c)
            continue;
          if(counter[i] > 0)
            counter[i] = counter[i] - 1;
        }

        dup = true;

        if (c == victim_frame)
          chage_victim_frame(victim_frame, number_of_frame, first_fill);
        ++string_position;

        break;
      }
    }

    if (dup == false)
    {
      if (counter[victim_frame] > 0)
      {
        counter[victim_frame] = counter[victim_frame] - 1;
        chage_victim_frame(victim_frame, number_of_frame, first_fill);
      }

      frame[victim_frame] = reference_string[string_position];
      counter[victim_frame] = 0;

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

      chage_victim_frame(victim_frame, number_of_frame, first_fill);
      ++string_position;
      ++page_fault_counter;
    }

    dup = false;

    for (int c = 0; c < number_of_frame; c++)
      cout << frame[c];
    cout << endl;

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

  int least;

  while (true)
	{
		least = counter[victim_frame];
		for (int c = 0; c < number_of_frame; c++)
		{

			if (least > counter[c] && first_fill == true)
				victim_frame = c;
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
			frame[victim_frame] = reference_string[string_position];
			counter[victim_frame] = 0;

			chage_victim_frame(victim_frame, number_of_frame, first_fill);
			++string_position;
			++page_fault_counter;
		}

		dup = false;

		for (int c = 0; c < number_of_frame; c++)
			cout << frame[c];
		cout << endl;

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
