#ifndef FINGER_TREE_H_
#define FINGER_TREE_H_

#include "node.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>
#include <stdexcept>

using namespace std;

float circle_radius = 30.0f; // calculate for the appropiate

template <typename T> class Finger_tree {
  FingerNode<T> *root;

public:
  friend void draw_finger_tree(sf::RenderWindow &window, Finger_tree<T> *root);
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
void draw_node(sf::RenderWindow &window, Node<T> *node, int level, int pos_x,
               int pos_y) {
  sf::CircleShape circle(circle_radius);
  circle.setPosition(pos_x, pos_y);

  int x = pos_x;
  int y = pos_y + circle_radius * 3;
  int step = pow(circle_radius, level) * 3;
  // The starting position of x works according to the level
  if (node->size() == 2) {
    x -= pow(circle_radius, level);
  } else if (node->size() == 3) {
    x -= pow(circle_radius, level) + circle_radius * (level + 1);
  }

  for (int i = 0; i < node->size(); i++) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(pos_x + circle_radius, pos_y + circle_radius),
                   sf::Color::Black),
        sf::Vertex(sf::Vector2f(x + circle_radius, y + circle_radius),
                   sf::Color::Black)};
    window.draw(line, 2, sf::Lines);

    draw_node(window, (*node)[i], level - 1, x, y);
    x += step;
  }

  if (node->node_state() == 'V') {
    circle.setFillColor(sf::Color::Black);
    // needs to draw the value
  } else {
    circle.setFillColor(sf::Color::Yellow);
  }

  window.draw(circle);
}

template <typename T>
void draw_affix(sf::RenderWindow &window, Affix<T> *affix, int level, int pos_x,
                int pos_y) {
  sf::CircleShape circle(circle_radius);
  circle.setPosition(pos_x, pos_y);
  circle.setFillColor(sf::Color::Blue);

  int x = pos_x;
  int y = pos_y + circle_radius * 3;
  int step = pow(3, level + 1) * circle_radius;

  cout << "size: " << affix->size() << endl;
  cout << "step: " << step << endl;

  // The starting position of x works according to the size of values and level
  if (affix->size() == 2) {
    x -= pow(3, level) * circle_radius + circle_radius * 1.5 * level;
  } else if (affix->size() == 3) {
    x -= pow(3, level + 1) * circle_radius;
  } else if (affix->size() == 4) {
    x -= pow(3, level + 1.3) * circle_radius;
  }
  // Iterates over each children to draw the children until the end
  for (int i = 0; i < affix->size(); i++) {
    cout << "i: " << i << endl;
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(pos_x + circle_radius, pos_y + circle_radius),
                   sf::Color::Black),
        sf::Vertex(sf::Vector2f(x + circle_radius, y + circle_radius),
                   sf::Color::Black)};
    window.draw(line, 2, sf::Lines);

    draw_node(window, (*affix)[i], level, x, y);
    x += step;
  }
  window.draw(circle);
}

template <typename T>
void draw_finger(sf::RenderWindow &window, FingerNode<T> *root) {
  // Loop to create and draw rectangles in a grid pattern
  int level = 0;
  if (root != nullptr) {
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
        // dibujar linea hacia abajo. L distancia es de acuerdo al nivel
      }
      level++;
      root = root->next;
    }
  }
}
template <typename T>
void draw_finger_tree(sf::RenderWindow &window, Finger_tree<T> *tree) {
  draw_finger(window, tree->root);
}
#endif // FINGER_TREE_H_
