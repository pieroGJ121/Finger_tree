#ifndef NODE_H_
#define NODE_H_

#include <exception>
using namespace std;

template <typename T> class Node {
  Node<T> **children;
  int size;
  T value;

public:
  Node(T v) { value = v; }
  Node() {
    children = new Node<T> *[3];
    for (int i = 0; i < 3; i++) {
      children[i] = nullptr;
    }
    size = 0;
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
};

#endif // NODE_H_
