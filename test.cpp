#include "finger_tree.h"
#include "node.h"
#include <iostream>

using namespace std;

void print_finger() {
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
}

void tree_level1() {
  sf::RenderWindow window(sf::VideoMode(1200, 1200), "Finger Tree");
  Node<int> *right = new Node<int>(4);
  Node<int> *middle = new Node<int>(5);
  Node<int> *left = new Node<int>(6);
  Node<int> *level1 = new Node<int>();
  level1->push_back(right);
  level1->push_back(middle);
  level1->push_back(left);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Black);

    draw_node(window, level1, 1, 100, 100);

    window.display();
  }
}

int main() {
  tree_level1();
  return 0;
}
