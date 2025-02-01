#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

/* The world's most inefficient way to generate the sequence
of all the odd integers, from 0..(n*2 - 1)!!! */

int main () {
  int x; int y;

  x = y = 13;

  cout << "Starting at " << x << "\n\n";

  int last_number = x * y;

  for (int going_up = x, going_down = y; going_down > -x; ++going_up, --going_down) {
    int product = going_up * going_down;

    cout << product << " - gap: " << last_number - product << endl;

    last_number = product;
  };

  return 0;
};
