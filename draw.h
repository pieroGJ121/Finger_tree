#ifndef DRAW_H_
#define DRAW_H_

#include "finger_tree.h"
#include "node.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>

using namespace std;

float circle_radius = 30.0f; // calculate for the appropiate

template <typename T>
void draw_node(sf::RenderWindow &window, Node<T> *node, int level, int pos_x,
               int pos_y) {
  sf::CircleShape circle(circle_radius);
  circle.setPosition(pos_x, pos_y);

  int x = pos_x;
  int y = pos_y + circle_radius * 3;
  int step = pow(3, level) * circle_radius;
  // The starting position of x works according to the level
  if (node->size() == 2) {
    x -= pow(3, level) * circle_radius - circle_radius * 1.5 * level;
  } else if (node->size() == 3) {
    x -= pow(3, level) * circle_radius;
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
    window.draw(circle);
    sf::Font font;
    font.loadFromFile("SulphurPoint-Regular.ttf");
    sf::Text text(node->val(), font);

    // Centrar el texto en la ventana
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(x + circle_radius, y - circle_radius * 2);

    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Green);
    window.draw(text);

  } else {
    circle.setFillColor(sf::Color::Yellow);
    window.draw(circle);
  }
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
void draw_finger(sf::RenderWindow &window, FingerNode<T> *root, int pos_y) {
  // Loop to create and draw rectangles in a grid pattern
  if (root != nullptr) {
    int level = 0;
    int x = window.getSize().x / 2;
    int y = pos_y;
    while (root->stateF() != 'E') {
      sf::CircleShape circle(circle_radius);
      circle.setPosition(x, y);
      int next_y = y + circle_radius * 9 + 3 * level * circle_radius;
      if (root->stateF() == 'S') {
        int yaff = y + circle_radius * 3;
        // special case for when the element is a single.
        // The only element of the single is saved as the first element of the
        // preffix and can be obtained with head of finger node
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + circle_radius, y + circle_radius),
                       sf::Color::Black),
            sf::Vertex(sf::Vector2f(x + circle_radius, y + circle_radius * 4),
                       sf::Color::Black)};

        window.draw(line, 2, sf::Lines);
        draw_node(window, root->head(), level, x, yaff);
        break;
      } else {
        int xpre = window.getSize().x / 4;
        int yaff = y + circle_radius * 3;
        int xsu = window.getSize().x - window.getSize().x / 4;

        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + circle_radius, y + circle_radius),
                       sf::Color::Black),
            sf::Vertex(sf::Vector2f(xpre + circle_radius, yaff + circle_radius),
                       sf::Color::Black)};
        window.draw(line, 2, sf::Lines);
        line[0] = sf::Vertex(sf::Vector2f(x + circle_radius, y + circle_radius),
                             sf::Color::Black);
        line[1] =
            sf::Vertex(sf::Vector2f(xsu + circle_radius, yaff + circle_radius),
                       sf::Color::Black);
        window.draw(line, 2, sf::Lines);

        // print preffix and suffix
        draw_affix(window, root->preffix, level, xpre, yaff);
        draw_affix(window, root->suffix, level, xsu, yaff);

        circle.setFillColor(sf::Color::Green);
        line[0] = sf::Vertex(sf::Vector2f(x + circle_radius, y + circle_radius),
                             sf::Color::Black);
        line[1] =
            sf::Vertex(sf::Vector2f(x + circle_radius, next_y + circle_radius),
                       sf::Color::Black);
        window.draw(line, 2, sf::Lines);
      }

      level++;
      y = next_y;
      root = root->next;

      window.draw(circle);
    }
    sf::CircleShape circle(circle_radius);
    circle.setPosition(x, y);
    if (root->stateF() == 'S') {
      circle.setFillColor(sf::Color::Red);
    } else {
      circle.setFillColor(sf::Color{209, 211, 212});
    }
    window.draw(circle);
  }
}

template <typename T>
void draw_finger_tree(sf::RenderWindow &window, Finger_tree<T> *tree,
                      int pos_y) {
  draw_finger(window, tree->top(), pos_y);
}

#endif // DRAW_H_