#include <stdio.h>
#include <iostream>
using namespace std;


bool divisible_by_3 (int i) {
  return i % 3 == 0;
};

bool divisible_by_5 (int i) {
  return i % 5 == 0;
};

bool indivisible_by_3_or_5 (int i) {
  return (!divisible_by_3(i) && !(divisible_by_5(i)));
};

int main() {
  for (int i = 0; i <= 100; i++) {
    if (divisible_by_3(i)) cout << "fizz";
    if (divisible_by_5(i)) cout << "buzz";
    if (indivisible_by_3_or_5(i)) cout << i;

    cout << endl;
  };

  return 0;
}
