#ifndef FINGER_TREE_H_
#define FINGER_TREE_H_

#include "node.h"
#include <stdexcept>

using namespace std;

float circleSize = 35.0f; // calculate for the appropiate

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
void draw_affix(sf::RenderWindow &window, Affix<T> *affix, int level,
                int offsety, bool suffix) {
  // if the center of the finger tree is in the middle of the screen, the affix
  // is to the left or to the right. The right indicates whether the it's suffix
  // when true, otherwise false is for preffix

  // First, draw the affix node. Calculate it's x position either dinamically to
  // have it as close to the finger as possible or harcode it into the middle of
  // the free space and build the children divding the space evenly in the free
  // space

  // Iterates over each children to draw the children until the end
  for (int i = 0; i < affix->size(); i++) {
    // Level 1 only has the elements directly in the affix. They are saved as
    // nodes for ease of use. Level 2 has nodes holding more values
    for (int i = 0; i < level; i++) {
      int posx,
          posy; // The pos x is gonna depend of the level of affix, because
                // the first level only needs to hold the affix and the
                // maximun 4 children while the second level can hold up to
                // 4 nodes and each node can have up to 3 children. Test the
                // size of the circle to make it adequate. It exists as a
                // variable now.
                // pos y is gonna depend on the level and the size of the circle
                // and lines. Try for the appropiate
    }
  }
}

template <typename T>
void draw_finger(sf::RenderWindow &window, FingerNode<T> *root) {
  // Loop to create and draw rectangles in a grid pattern
  if (root != nullptr) {
    int level = 1;
    while (root->stateF() != 'E') {
      // The distance between the finger node and the next depends on the level,
      // and the size of the circle
      if (root->stateF() == 'S') {
        // special case for when the element is a single.
        // The only element of the single is saved as the first element of the
        // preffix and can be obtained with head of finger node. After that,
        // only display it normally
        //
      } else {
        int offsety; // where the affix should go vertically. It depends on the
                     // level and the size of the circle
        // print preffix and suffix
        draw_affix(window, root->preffix, level, offsety, false);
        draw_affix(window, root->suffix, level, offsety, true);
      }
      level++;
      root = root->next;
    }
  }
}
#endif // FINGER_TREE_H_
