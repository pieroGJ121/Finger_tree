#ifndef NODE_H_
#define NODE_H_

#include "circulararray.h"
#include <SFML/Graphics.hpp>
#include <exception>
#include <queue>

using namespace std;

template <typename T> class Node {
  CircularArray<Node<T> *> *children;
  T value;
  char state;

public:
  Node(T v) {
    value = v;
    state = 'V';
  }
  Node() {
    children = new CircularArray<Node<T> *>(3);
    state = 'N';
  }
  ~Node() { this->killSelf(); }
  void killSelf() { this->children->killSelfPointer(); }
  Node<T> *pop_front() { return this->children->pop_front(); }
  Node<T> *pop_back() { return this->children->pop_back(); }
  void push_front(Node<T> *value) { this->children->push_front(value); }
  void push_back(Node<T> *value) { this->children->push_back(value); }
  int size() { return this->children->size(); }
  string toString(string sep) {
    string result = "";
    if (state == 'V') {
      result = to_string(value) + sep;
    } else {
      for (int i = 0; i < children->size(); i++) {
        result += (*children)[i]->toString(sep);
      }
    }
    return result;
  }
};

template <typename T> class Affix {
protected:
  CircularArray<Node<T> *> *children;

public:
  void draw_suffix(sf::RenderWindow &window, Affix<T> *affix);
  Affix() { children = new CircularArray<Node<T> *>(3); }
  ~Affix() { this->killSelf(); }
  void killSelf() { this->children->killSelfPointer(); }

  Node<T> *head() { return (*this->children)[0]; }
  Node<T> *tail() { return (*this->children)[this->children->size() - 1]; }
  Node<T> *pop_front() { return this->children->pop_front(); }
  Node<T> *pop_back() { return this->children->pop_back(); }
  void push_front(Node<T> *value) { this->children->push_front(value); }
  void push_back(Node<T> *value) { this->children->push_back(value); }
  int size() { return this->children->size(); }
  string toString(string sep) {
    string result = "";
    for (int i = 0; i < children->size(); i++) {
      result += (*children)[i]->toString(sep);
    }
    return result;
  }
};

template <typename T> class FingerNode {
  Affix<T> *preffix;
  Affix<T> *suffix;
  FingerNode<T> *next;
  char state;

public:
  friend void draw_finger(sf::RenderWindow &window, FingerNode<T> *root);

  FingerNode() {
    preffix = nullptr;
    suffix = nullptr;
    next = nullptr;
    state = 'E';
  }
  ~FingerNode() {}

  char stateF() { return state; }
  void push_front(T value) { push_front(new Node<T>(value)); }
  void push_front(Node<T> *value) {
    // The finger tree doesn't have elements, so it becomes a single
    if (state == 'E') {
      preffix = new Affix<T>();
      preffix->push_front(value);
      this->state = 'S';
      next = new FingerNode<T>();
      // The finger tree is a single, so it stops being one
    } else if (state == 'S') {
      suffix = new Affix<T>();
      suffix->push_front(preffix->pop_back());
      preffix->push_front(value);
      this->state = 'F';
      // The preffix is full
    } else if (preffix->size() == 4) {
      Node<T> *to_add = new Node<T>();
      to_add->push_front(preffix->pop_back());
      to_add->push_front(preffix->pop_back());
      to_add->push_front(preffix->pop_back());
      next->push_front(to_add);
    } else {
      // The preffix has less than 4 elements
      preffix->push_front(value);
    }
  }

  void push_back(T value) { push_back(new Node<T>(value)); }
  void push_back(Node<T> *value) {
    // The finger tree doesn't have elements, so it becomes a single
    if (state == 'E') {
      preffix = new Affix<T>();
      preffix->push_front(value);
      next = new FingerNode<T>();
      this->state = 'S';
      // The finger tree is a single, so it stops being one
    } else if (state == 'S') {
      suffix = new Affix<T>();
      suffix->push_front(value);
      this->state = 'F';
      // The preffix is full
    } else if (suffix->size() == 4) {
      Node<T> *to_add = new Node<T>();
      to_add->push_back(suffix->pop_front());
      to_add->push_back(suffix->pop_front());
      to_add->push_back(suffix->pop_front());
      next->push_front(to_add);
      suffix->push_back(value);
    } else {
      // The suffix has less than 4 elements
      suffix->push_back(value);
    }
  }
  Node<T> *pop_front() {
    if (state == 'E') {
      return nullptr;
    } else if (state == 'S') {
      Node<T> *temp = this->preffix->pop_back();
      preffix = nullptr;
      state = 'E';
      return temp;
    } else {
      Node<T> *temp = preffix->pop_front();
      if (preffix->size() == 0) {
        Node<T> *to_add = next->pop_front();
        if (to_add == nullptr) {
          // borrow from suffix
          preffix->push_back(suffix->pop_front());

          // if only 1 left in suffix, turn finger node into single
          if (suffix->size() == 0) {
            suffix->killSelf();
            suffix = nullptr;
            state = 'S';
          }
        } else {
          for (int i = 0; i < to_add->size(); i++) {
            preffix->push_back(to_add->pop_front());
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
      Node<T> *temp = this->preffix->pop_back();
      this->preffix->killSelf();
      preffix = nullptr;
      state = 'E';
      return temp;
    } else {
      Node<T> *temp = suffix->pop_back();
      if (suffix->size() == 0) {
        Node<T> *to_add = next->pop_back();
        if (to_add == nullptr) {
          // borrow from suffix
          suffix->push_front(preffix->pop_back());
          // if only 1 left in preffix, turn finger node into single
          if (preffix->size() == 0) {
            preffix->killSelf();
            preffix = nullptr;
            state = 'S';
          }
        } else {
          for (int i = 0; i < to_add->size(); i++) {
            suffix->push_front(to_add->pop_back());
          }
        }
      }
      return temp;
    }
  }

  Node<T> *head() {
    if (state == 'E') {
      throw runtime_error("finger tree is empty");
    } else {
      return this->preffix->head();
    }
  }

  Node<T> *tail() {
    if (state == 'E') {
      throw runtime_error("finger tree is empty");
    } else if (state == 'S') {
      return this->preffix->head();
    } else {
      return this->suffix->tail();
    }
  }

  string toString(string sep) {
    string result = "";
    if (state == 'S') {
      result += preffix->toString(sep);
    } else if (state == 'F') {
      result += preffix->toString(sep);
      result += "|";
      result += next->toString(sep);
      result += "|";
      result += suffix->toString(sep);
    }
    return result;
  }
};

#endif // NODE_H_
