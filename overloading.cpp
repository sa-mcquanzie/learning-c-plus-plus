#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;


int multiply (int x, int y) {
  return x * y;
};

string multiply (string x, int y) {
  string result = "";

  for (int i = 0; i < y; i++) {
    result.append(x);
  };

  return result;
};

int main () {
  cout << multiply(2, 5) << endl;
  cout << multiply("boing", 3) << endl;

  return 0;
};
