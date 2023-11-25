#include "draw.h"
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>

using namespace std;

void tree_level1() {
  sf::RenderWindow window(sf::VideoMode(1200, 1200), "Finger Tree",
                          sf::Style::Default);
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
  sf::RenderWindow window(sf::VideoMode(1200, 1200), "Finger Tree",
                          sf::Style::Default);
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
  sf::RenderWindow window(sf::VideoMode(1200, 1200), "Finger Tree",
                          sf::Style::Default);
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

void finger_level0() {
  Finger_tree<int> *finger = new Finger_tree<int>();
  finger->push_front(2);
  finger->push_front(1);
  finger->push_front(0);
  finger->push_front(-1);
  finger->push_front(-2);
  finger->push_back(3);
  finger->push_back(4);
  finger->push_back(5);
  sf::RenderWindow window(sf::VideoMode(1200, 1200), "Finger Tree",
                          sf::Style::Default);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::White);

    draw_finger_tree(window, finger);

    window.display();
  }
}

void finger_level1() {
  Finger_tree<int> *finger = new Finger_tree<int>();
  finger->push_front(2);
  finger->push_front(1);
  finger->push_front(0);
  finger->push_front(-1);
  finger->push_front(-2);
  finger->push_back(3);
  finger->push_back(4);
  finger->push_back(5);
  finger->push_back(6);
  finger->push_front(-3);
  sf::RenderWindow window(sf::VideoMode(1200, 1200), "Finger Tree",
                          sf::Style::Default);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::White);

    draw_finger_tree(window, finger);

    window.display();
  }
}
void finger_level1_s() {
  Finger_tree<int> *finger = new Finger_tree<int>();
  finger->push_front(2);
  finger->push_front(1);
  finger->push_front(0);
  finger->push_front(-1);
  finger->push_front(-2);
  finger->push_back(3);
  finger->push_back(4);
  finger->push_back(5);
  finger->push_back(6);
  sf::RenderWindow window(sf::VideoMode(1200, 1200), "Finger Tree",
                          sf::Style::Default);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::White);

    draw_finger_tree(window, finger);

    window.display();
  }
}
int main() {
  // tree_level1();
  // affix_level0();
  // affix_level1();
  // finger_level0();
  // finger_level1();
  finger_level1_s();
  return 0;
}
