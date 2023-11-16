#ifndef NODE_H_
#define NODE_H_

#include <exception>
using namespace std;

template <typename T> class Node {
  Node<T> **children;
  int size;
  T value;
  char state;

public:
  Node(T v, char s = 'V') {
    value = v;
    children = new Node<T> *[3];
    for (int i = 0; i < 3; i++) {
      children[i] = nullptr;
    }
    size = 0;
    state = s;
  }
  Node() {
    children = new Node<T> *[3];
    for (int i = 0; i < 3; i++) {
      children[i] = nullptr;
    }
    size = 0;
    state = 'N';
  }
  ~Node() { this->killSelf(); }
  void killSelf() {
    for (int i = 0; i < size; i++) {
      if (children[i] != nullptr) {
        children[i]->killSelf();
      }
    }
    delete[] children;
  }
  Node<T> *pop();
  void push(Node<T> *value);
};

template <typename T> class Affix {
protected:
  Node<T> **children;
  int size;

public:
  Affix() {
    children = new Node<T> *[4];
    for (int i = 0; i < 4; i++) {
      children[i] = nullptr;
    }
    size = 0;
  }
  ~Affix() { this->killSelf(); }
  void killSelf() {
    for (int i = 0; i < size; i++) {
      if (children[i] != nullptr) {
        children[i]->killSelf();
      }
    }
    delete[] children;
  }

  virtual Node<T> *top() = 0;
  virtual Node<T> *pop() = 0;
  virtual void push(Node<T> *value) = 0;
};

template <typename T> class Preffix : public Affix<T> {};
template <typename T> class Suffix : public Affix<T> {};

template <typename T> class FingerNode {
  Affix<T> *preffix;
  Affix<T> *suffix;
  FingerNode<T> *next;

public:
  FingerNode() {
    preffix = nullptr;
    suffix = nullptr;
    next = nullptr;
  }
  ~FingerNode() {}

  void push_front(T value) { push_front(new Node<T>(value)); }
  void push_front(Node<T> *value) {
    // The finger tree doesn't have elements, so it becomes a single
    if (preffix == nullptr && suffix == nullptr) {

      // The finger tree is a single
    } else if (next == nullptr) {

      // The preffix is full
    } else if (preffix->size == 4) {
      Node<T> *to_add = new Node<T>();
      to_add->push(preffix->pop());
      to_add->push(preffix->pop());
      to_add->push(preffix->pop());
      next->push_front(to_add);
    } else {
      // The suffix has less than 4 elements
      preffix->push(new Node<T>());
    }
  }

  void push_back(T value) { push_back(new Node<T>(value)); }
  void push_back(Node<T> *value) {
    // The finger tree is a single
    if (preffix == nullptr) {
      // The suffix is full
    } else if (suffix->size == 4) {
      Node<T> *to_add = new Node<T>();
      to_add->push(suffix->pop());
      to_add->push(suffix->pop());
      to_add->push(suffix->pop());
      next->push_front(to_add);
      // The suffix has less than 4 elements
    }
    suffix->push(value);
  }
  Node<T> *pop_front() {
    if (preffix->size == 1) {
      Node<T> *to_add = next->pop_front();
    }
  }
  Node<T> *pop_back() {}
};

#endif // NODE_H_
