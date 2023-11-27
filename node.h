#ifndef NODE_H_
#define NODE_H_

#include "circulararray.h"
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
    children = nullptr;
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
  int size() { return children == nullptr ? 0 : this->children->size(); }
  char node_state() { return this->state; }
  T val() { return this->value; }
  Node<T> *&operator[](int index) { return (*children)[index]; }
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
  Affix() { children = new CircularArray<Node<T> *>(4); }
  ~Affix() { this->killSelf(); }
  void killSelf() { this->children->killSelfPointer(); }

  Node<T> *head() { return (*this->children)[0]; }
  Node<T> *tail() { return (*this->children)[this->children->size() - 1]; }
  Node<T> *pop_front() { return this->children->pop_front(); }
  Node<T> *pop_back() { return this->children->pop_back(); }
  void push_front(Node<T> *value) { this->children->push_front(value); }
  void push_back(Node<T> *value) { this->children->push_back(value); }
  Node<T> *&operator[](int index) { return (*children)[index]; }
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
  char state;
  string last_act;

public:
  Affix<T> *preffix;
  Affix<T> *suffix;
  FingerNode<T> *next;

  FingerNode() {
    preffix = nullptr;
    suffix = nullptr;
    next = nullptr;
    state = 'E';
    last_act = "Finger Tree creado";
  }
  ~FingerNode() { this->killSelf(); }

  char stateF() { return state; }
  void push_front(T value) { push_front(new Node<T>(value)); }
  void push_front(Node<T> *value) {
    last_act = "Push front. ";
    // The finger tree doesn't have elements, so it becomes a single
    if (state == 'E') {
      preffix = new Affix<T>();
      preffix->push_front(value);
      this->state = 'S';
      next = new FingerNode<T>();
      last_act +=
          "Caso 1. El finger tree estaba vacio, asi que se convirtio en "
          "un single";
      // The finger tree is a single, so it stops being one
    } else if (state == 'S') {
      suffix = new Affix<T>();
      suffix->push_front(preffix->pop_back());
      preffix->push_front(value);
      this->state = 'F';
      last_act +=
          "Caso 2. El finger tree era un single, asi que se creo el prefijo y "
          "el sufijo";
      // The preffix is full
    } else if (preffix->size() == 4) {
      Node<T> *to_add = new Node<T>();
      to_add->push_front(preffix->pop_back());
      to_add->push_front(preffix->pop_back());
      to_add->push_front(preffix->pop_back());
      next->push_front(to_add);
      last_act += "Caso 3. El prefijo estaba lleno, asi que se hace llamada "
                  "recursiva de push front al siguiente nivel";
      preffix->push_front(value);
    } else {
      // The preffix has less than 4 elements
      last_act += "Caso 4. El prefijo con espacio, asi que solo se aniade";
      preffix->push_front(value);
    }
  }

  void push_back(T value) { push_back(new Node<T>(value)); }
  void push_back(Node<T> *value) {
    last_act = "Push back. ";
    // The finger tree doesn't have elements, so it becomes a single
    if (state == 'E') {
      preffix = new Affix<T>();
      preffix->push_front(value);
      next = new FingerNode<T>();
      this->state = 'S';
      last_act +=
          "Caso 1. El finger tree estaba vacio, asi que se convirtio en "
          "un single";
      // The finger tree is a single, so it stops being one
    } else if (state == 'S') {
      suffix = new Affix<T>();
      suffix->push_front(value);
      this->state = 'F';
      last_act +=
          "Caso 2. El finger tree era un single, asi que se creo el prefijo y "
          "el sufijo";
      // The preffix is full
    } else if (suffix->size() == 4) {
      Node<T> *to_add = new Node<T>();
      to_add->push_back(suffix->pop_front());
      to_add->push_back(suffix->pop_front());
      to_add->push_back(suffix->pop_front());
      next->push_back(to_add);
      suffix->push_back(value);
      last_act += "Caso 3. El sufijo estaba lleno, asi que se hace llamada "
                  "recursiva de push back al siguiente nivel";
    } else {
      // The suffix has less than 4 elements
      suffix->push_back(value);
      last_act += "Caso 4. El sufijo con espacio, asi que solo se aniade";
    }
  }
  Node<T> *pop_front() {
    last_act = "Pop front. ";
    if (state == 'E') {
      last_act += "Caso 1. El finger tree no tiene elementos";
      return nullptr;
    } else if (state == 'S') {
      Node<T> *temp = this->preffix->pop_back();
      preffix->killSelf();
      preffix = nullptr;
      state = 'E';
      last_act += "Caso 2. Es un single, asi que se convierte en vacio";
      return temp;
    } else {
      Node<T> *temp = preffix->pop_front();
      if (preffix->size() == 0) {
        Node<T> *to_add = next->pop_front();
        if (to_add == nullptr) {
          last_act += "Caso 3. Se presta del sufijo";
          // borrow from suffix
          preffix->push_back(suffix->pop_front());
          if (suffix->size() == 0) {
            last_act += " pero este solo tiene 1 elemento, asi que se "
                        "convierte en single";
            // if only 1 left in suffix, turn finger node into single
            suffix->killSelf();
            suffix = nullptr;
            state = 'S';
          }
        } else {
          // this works because the nodes of deeper levels must be full
          last_act += "Caso 5. Se presta del siguiente nivel";
          for (int i = 0; i < 3; i++) {
            preffix->push_back(to_add->pop_front());
          }
        }
      }
      return temp;
    }
  }
  Node<T> *pop_back() {
    last_act = "Pop back. ";
    if (state == 'E') {
      last_act += "Caso 1. El finger tree no tiene elementos";
      return nullptr;
    } else if (state == 'S') {
      Node<T> *temp = this->preffix->pop_back();
      this->preffix->killSelf();
      preffix = nullptr;
      state = 'E';
      last_act += "Caso 2. Es un single asi que se convierte en vacio";
      return temp;
    } else {
      Node<T> *temp = suffix->pop_back();
      if (suffix->size() == 0) {
        Node<T> *to_add = next->pop_back();
        if (to_add == nullptr) {
          // borrow from suffix
          last_act += "Caso 3. Se presta del prefijo";
          if (preffix->size() == 1) {
            last_act += " pero este solo tiene 1 elemento, asi que se "
                        "convierte en single";
            suffix->killSelf();
            suffix = nullptr;
            state = 'S';
          } else {
            suffix->push_front(preffix->pop_back());
          }
          // if only 1 left in preffix, turn finger node into single
        } else {
          last_act += "Caso 5. Se presta del siguiente nivel";
          // this works because the nodes of deeper levels must be full
          for (int i = 0; i < 3; i++) {
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

  string message() { return this->last_act; }

  void killSelf() {
    if (preffix != nullptr) {
      preffix->killSelf();
    }
    if (suffix != nullptr) {
      suffix->killSelf();
    }
    if (next != nullptr) {
      next->killSelf();
    }
  }
};

#endif // NODE_H_
