#include "finger_tree.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main() {
  sf::RenderWindow window(sf::VideoMode(1200, 1200), "Finger Tree");
  sf::Font font;
  font.loadFromFile("SulphurPoint-Regular.ttf");

  Finger_tree<int> *finger = new Finger_tree<int>();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::White);
    draw_finger_tree(window, finger);
    window.display();

    // Put menu at the bottom. Options for the 4 operations.
    // The pushs need an aditional number. If push, print below for the
    // option to insert a numer
    // Complete
    sf::Text text("Menu and the rest ", font); // complete
    sf::FloatRect textRect = text.getLocalBounds();
    int x, y; // calcualte where is the bottom
    text.setPosition(x, y);

    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    window.draw(text);

    // Chain of conditionals to use the operations of the finger tree. Examples
    // of how the methods are called is in test

    window.display();
  }
  return 0;
}
