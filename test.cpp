#include "finger_tree.h"
#include <iostream>

using namespace std;

int main() {
  Finger_tree<int> *finger = new Finger_tree<int>();
  finger->push_front(2);
  cout << finger->toString(" ") << endl;
  finger->push_front(1);
  cout << finger->toString(" ") << endl;
  finger->push_front(0);
  cout << finger->toString(" ") << endl;
  finger->push_front(-1);
  cout << finger->toString(" ") << endl;
  finger->push_front(-2);
  cout << finger->toString(" ") << endl;
  finger->push_back(3);
  cout << finger->toString(" ") << endl;
  finger->push_back(4);
  cout << finger->toString(" ") << endl;
  finger->push_back(5);
  cout << finger->toString(" ") << endl;
  finger->push_back(6);
  cout << finger->toString(" ") << endl;
  finger->push_front(-3);
  cout << finger->toString(" ") << endl;
  cout << "after push" << endl;
  cout << finger->toString(" ") << endl;
  return 0;
}
