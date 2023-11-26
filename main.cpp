#include "draw.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  sf::RenderWindow window(sf::VideoMode(1900, 1070), "Matriz SFML");
  window.setKeyRepeatEnabled(false);

  string opcion = "";
  string message = "";
  int in_push = 0;
  string value = "";

  int ytext = 30;
  sf::Font font;
  font.loadFromFile("SulphurPoint-Regular.ttf");

  Finger_tree<string> *finger = new Finger_tree<string>();

  while (window.isOpen()) {
    sf::Event event;

    window.clear(sf::Color::White);

    sf::Text inputText;
    if (in_push == 0) {
      inputText = sf::Text(sf::String("1. Push front, "
                                      "2. Push back, "
                                      "3. Pop front, "
                                      "4. Pop back, "
                                      "5. Cerrar Aplicacion. "
                                      "Ingrese su opcion: "),
                           font);
    } else {
      inputText =
          sf::Text(sf::String(opcion + "Ingrese su valor: " + value), font);
    }

    inputText.setPosition(20, ytext);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::Black);
    window.draw(inputText);

    draw_finger_tree(window, finger, ytext + 45);

    // Display message in the upper right corner
    sf::Text messageText(message, font);
    messageText.setCharacterSize(18);
    messageText.setFillColor(sf::Color::Red);
    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setPosition(window.getSize().x - textRect.width - 20, 10);
    window.draw(messageText);

    const sf::Color COLOR_PLOMO = sf::Color(128, 128, 128);   // Gris (plomo)
    const sf::Color COLOR_ROJO = sf::Color::Red;
    const sf::Color COLOR_AZUL = sf::Color::Blue;
    const sf::Color COLOR_AMARILLO = sf::Color::Yellow;

    // Leyendas
    sf::Text leyendaPLOMO("PLOMO: Finger vacio", font);
    leyendaPLOMO.setCharacterSize(24);
    leyendaPLOMO.setFillColor(COLOR_PLOMO);
    leyendaPLOMO.setPosition(20, window.getSize().y - 20);

    sf::Text leyendaROJO("   ROJO: Finger de un solo elemento", font);
    leyendaROJO.setCharacterSize(24);
    leyendaROJO.setFillColor(COLOR_ROJO);
    leyendaROJO.setPosition(leyendaPLOMO.getPosition().x + leyendaPLOMO.getLocalBounds().width + 20, window.getSize().y - 20);

    sf::Text leyendaAZUL("   AZUL: Nodo sufijo o prefijo", font);
    leyendaAZUL.setCharacterSize(24);
    leyendaAZUL.setFillColor(COLOR_AZUL);
    leyendaAZUL.setPosition(leyendaROJO.getPosition().x + leyendaROJO.getLocalBounds().width + 20, window.getSize().y - 20);

    sf::Text leyendaAMARILLO("   AMARILLO: Nodo", font);
    leyendaAMARILLO.setCharacterSize(24);
    leyendaAMARILLO.setFillColor(COLOR_AMARILLO);
    leyendaAMARILLO.setPosition(leyendaAZUL.getPosition().x + leyendaAZUL.getLocalBounds().width + 20, window.getSize().y - 20);

    window.draw(leyendaPLOMO);
    window.draw(leyendaROJO);
    window.draw(leyendaAZUL);
    window.draw(leyendaAMARILLO);

    window.display();

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::TextEntered) {
        if (in_push > 0) {
          // change status when enter is pressed. until then verify user input
          // to add only numbers
          if ((event.text.unicode == 48 &&
               ((value[0] == 45 && value.size() >= 2) ||
                (value[0] != 45 && value.size() >= 1))) ||
              (event.text.unicode >= 49 && event.text.unicode <= 57) ||
              (event.text.unicode == 45 && value.empty())) {
            value += (char)event.text.unicode;
          } else if (event.text.unicode == 13) {
            if (value == "") {
              message = "No se permite la cadena vacia.";
            } else {
              if (in_push == 1) {
                finger->push_front(value);
              } else {
                finger->push_back(value);
              }
              value = "";
              opcion = "";
              message = finger->message();
              in_push = 0;
            }
          } else if (event.text.unicode == 8) {
            if (!value.empty()) {
              value.pop_back();
            }
          } else {
            message = "Ingresa un digito.";
          }
        } else {
          if (event.text.unicode == '1') {
            opcion = "Push Front. ";
            in_push = 1;
          } else if (event.text.unicode == '2') {
            opcion = "Push Back. ";
            in_push = 2;
          } else if (event.text.unicode == '3') {
            finger->pop_front();
            message = finger->message();
          } else if (event.text.unicode == '4') {
            finger->pop_back();
            message = finger->message();
          } else if (event.text.unicode == '5') {
            window.close();
          } else {
            message = "Escoje una opcion valida";
          }
        }
      }
    }
  }

  return 0;
}
