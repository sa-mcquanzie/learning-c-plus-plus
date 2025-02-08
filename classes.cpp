#include <stdio.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

string AppendIfExists(string left, string right) {
  return right.length() > 0 ? left + " " + right : left;
}

class Counter {
  private:
    int num;
    int step;

  public:
    Counter(int i = 0, int s = 1) {
      num = i;
      step = s;
    };

    int Value() {
      return num;
    }

    int Next(int iterations = 1) {
      for (int i = 0; i < iterations; i++) {
        num += step;
      }

      return num;
    }

    int Prev(int iterations = 1) {
      for (int i = 0; i < iterations; i++) {
        num -= step;
      }

      return num;
    }
};

struct NamePart {
  string value;
  int position;
};

class Name {
  public:
    NamePart first;
    NamePart middle;
    NamePart last;

    Name(string f = "", string m = "", string l = "") {
      first.value = f;
      first.position = 0;
      middle.value = m;
      middle.position = 1;
      last.value = l;
      last.position = 2;
    }
};

class Person {
  private:
    Name name;
    Counter age;

  public:
    Person(Name n, Counter a) {
      name = n;
      age = a;
    };

    string GetName() {
      string full_name = AppendIfExists(
        AppendIfExists(name.first.value, name.middle.value), name.last.value
      );

      return full_name;
    }

    string ChangeName(int name_position, string new_name) {
      switch (name_position) {
        case 0:
          return name.first.value = new_name;
        case 1:
          return name.middle.value = new_name;
        case 2:
          return name.last.value = new_name;
        default:
          return "Invalid name position";
      }     
    }

    int GetAge() {
      return age.Value();
    }

    int AgeBy(int num) {
      return age.Next(num);
    }
};

int main() {
  Counter my_age;
  Name my_name;
  Person me(my_name, my_age);

  cout << me.GetName() << endl;
  cout << me.GetAge() << endl;

  me.ChangeName(0, "Amelia");
  me.ChangeName(1, "Beatrice Cecily");
  me.ChangeName(2, "Scott");

  cout << me.GetName() << endl;

  me.AgeBy(42);
  
  cout << me.GetAge() << endl;
}
