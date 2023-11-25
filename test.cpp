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

    window.clear(sf::Color::White);

    draw_node(window, level1, 1, 100, 100);

    window.display();
  }
}

void affix_level0() {
  sf::RenderWindow window(sf::VideoMode(1200, 1200), "Finger Tree");
  Affix<int> *fixx = new Affix<int>();

  for (int i = 0; i < 4; i++) {
    Node<int> *level0 = new Node<int>(2);
    fixx->push_back(level0);
  }
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::White);

    draw_affix(window, fixx, 0, 200, 200);

    window.display();
  }
}

void affix_level1() {
  sf::RenderWindow window(sf::VideoMode(1200, 1200), "Finger Tree");
  Affix<int> *fixx = new Affix<int>();

  for (int i = 0; i < 4; i++) {
    Node<int> *level1 = new Node<int>();
    for (int i = 0; i < 3; i++) {
      Node<int> *level0 = new Node<int>(2);
      level1->push_back(level0);
    }
    fixx->push_back(level1);
  }
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::White);

    cout << "before draw affix" << endl;
    draw_affix(window, fixx, 1, 500, 500);

    window.display();
  }
}
int main() {
  tree_level1();
  // affix_level0();
  // affix_level1();
  return 0;
}
