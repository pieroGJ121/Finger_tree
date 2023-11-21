#ifndef FINGER_TREE_H_
#define FINGER_TREE_H_

#include "node.h"
#include <stdexcept>

using namespace std;

float circleSize = 35.0f; // calculate for the appropiate
float lineSize = 35.0f;   // calculate for the appropiate

template <typename T> class Finger_tree {
  FingerNode<T> *root;

public:
  Finger_tree() { root = nullptr; }
  ~Finger_tree() { root->killSelf(); }

  void push_front(T value) {
    if (root == nullptr) {
      root = new FingerNode<T>();
    }
    root->push_front(value);
  }
  void push_back(T value) {
    if (root == nullptr) {
      root = new FingerNode<T>();
    }
    root->push_back(value);
  }
  void pop_front() {
    if (root == nullptr) {
      throw std::runtime_error("No elements in finger tree.");
    } else {
      root->pop_front();
    }
  }
  void pop_back() {
    if (root == nullptr) {
      throw std::runtime_error("No elements in finger tree.");
    } else {
      root->pop_back();
    }
  }
  string toString(string sep) { return root->toString(sep); }
};

template <typename T>
void draw_affix(sf::RenderWindow &window, Affix<T> *affix, int depth,
                int offset) {
  for (int i = 0; i < depth; i++) {
  }
}

template <typename T>
void draw_finger(sf::RenderWindow &window, FingerNode<T> *root) {
  // Loop to create and draw rectangles in a grid pattern
  if (root != nullptr) {
    int level = 1;
    while (root->stateF() != 'E') {
      if (root->stateF() == 'S') {
        // special case for when the element is a single.
        // The only element of the single is saved as the first element of the
        // preffix and can be obtained with head of finger tree.
        //
      } else {
        // print preffix and suffix
      }
      root = root->next;
    }
  }
}
#endif // FINGER_TREE_H_
