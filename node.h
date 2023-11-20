#ifndef NODE_H_
#define NODE_H_

#include "queue.h"
#include <exception>
#include <queue>

using namespace std;

template <typename T> class Node {
  Queue<Node<T> *> *children;
  T value;
  char state;

public:
  Node(T v) {
    value = v;
    state = 'V';
  }
  Node() {
    children = new Queue<Node<T> *>(3);
    state = 'N';
  }
  ~Node() { this->killSelf(); }
  void killSelf() { this->children->killSelfPointer(); }
  Node<T> *pop() { return this->children->dequeue(); }
  void push(Node<T> *value) { this->children->enqueue(value); }
  int size() { return this->children->size(); }
};

template <typename T> class Affix {
protected:
  Queue<Node<T> *> *children;

public:
  Affix() { children = new Queue<Node<T> *>(3); }
  ~Affix() { this->killSelf(); }
  void killSelf() { this->children->killSelfPointer(); }

  Node<T> *top() { return this->children->top(); }
  Node<T> *pop() { return this->children->dequeue(); }
  void push(Node<T> *value) { this->children->enqueue(value); }
  int size() { return this->children->size(); }
};

template <typename T> class FingerNode {
  Affix<T> *preffix;
  Affix<T> *suffix;
  FingerNode<T> *next;
  char state;

public:
  FingerNode() {
    preffix = nullptr;
    suffix = nullptr;
    next = new FingerNode<T>();
    state = 'E';
  }
  ~FingerNode() {}

  void push_front(T value) { push_front(new Node<T>(value)); }
  void push_front(Node<T> *value) {
    // The finger tree doesn't have elements, so it becomes a single
    if (state == 'E') {
      preffix = new Affix<T>();
      preffix->push(value);
      this->state = 'S';
      // The finger tree is a single, so it stops being one
    } else if (state == 'S') {
      suffix = new Affix<T>();
      suffix->push(preffix->pop());
      preffix->push(value);
      this->state = 'F';
      // The preffix is full
    } else if (preffix->size == 4) {
      Node<T> *to_add = new Node<T>();
      to_add->push(preffix->pop());
      to_add->push(preffix->pop());
      to_add->push(preffix->pop());
      next->push_front(to_add);
    } else {
      // The preffix has less than 4 elements
      preffix->push(value);
    }
  }

  void push_back(T value) { push_back(new Node<T>(value)); }
  void push_back(Node<T> *value) {
    // The finger tree doesn't have elements, so it becomes a single
    if (state == 'E') {
      preffix = new Affix<T>();
      preffix->push(value);
      this->state = 'S';
      // The finger tree is a single, so it stops being one
    } else if (state == 'S') {
      suffix = new Affix<T>();
      suffix->push(value);
      this->state = 'F';
      // The preffix is full
    } else if (preffix->size == 4) {
      Node<T> *to_add = new Node<T>();
      to_add->push(suffix->pop());
      to_add->push(suffix->pop());
      to_add->push(suffix->pop());
      next->push_front(to_add);
      suffix->push(value);
    } else {
      // The suffix has less than 4 elements
      suffix->push(value);
    }
  }
  Node<T> *pop_front() {
    if (state == 'E') {
      return nullptr;
    } else if (state == 'S') {
      Node<T> *temp = this->preffix->pop();
      preffix = nullptr;
      state = 'E';
      return temp;
    } else {
      Node<T> *temp = preffix->pop();
      if (preffix->size == 0) {
        Node<T> *to_add = next->pop_front();
        if (to_add == nullptr) {
          // borrow from suffix
          preffix->push(suffix->pop());

          // if only 1 left in suffix, turn finger node into single
          if (suffix->size() == 0) {
            suffix->killSelf();
            suffix = nullptr;
            state = 'S';
          }
        } else {
          for (int i = 0; i < to_add->size(); i++) {
            preffix->push(to_add->pop());
          }
        }
      }
      return temp;
    }
  }
  Node<T> *pop_back() {
    if (state == 'E') {
      return nullptr;
    } else if (state == 'S') {
      Node<T> *temp = this->preffix->pop();
      preffix = nullptr;
      state = 'E';
      return temp;
    } else {
      Node<T> *temp = suffix->pop();
      if (suffix->size == 0) {
        Node<T> *to_add = next->pop_back();
        if (to_add == nullptr) {
          // borrow from suffix
          suffix->push(preffix->pop());
          // if only 1 left in preffix, turn finger node into single
          if (preffix->size() == 0) {
            preffix->killSelf();
            preffix = nullptr;
            state = 'S';
          }
        } else {
          for (int i = 0; i < to_add->size(); i++) {
            suffix->push(to_add->pop());
          }
        }
      }
      return temp;
    }
  }
};

#endif // NODE_H_
