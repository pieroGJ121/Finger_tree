#ifndef FINGER_TREE_H_
#define FINGER_TREE_H_

#include "node.h"
#include <stdexcept>

using namespace std;

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

#endif // FINGER_TREE_H_
