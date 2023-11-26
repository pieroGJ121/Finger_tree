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

        // Ajusta las posiciones de las leyendas
        float leyendaY = messageText.getPosition().y + textRect.height + 20;
        float leyendaX = window.getSize().x - 20;  // Alinea a la derecha

        const sf::Color COLOR_PLOMO = sf::Color(91, 91, 88);
        const sf::Color COLOR_ROJO = sf::Color::Red;
        const sf::Color COLOR_AZUL = sf::Color::Blue;
        const sf::Color COLOR_AMARILLO = sf::Color(209, 203, 10);
        const sf::Color COLOR_NEGRO = sf::Color::Black;
        const sf::Color COLOR_VERDE = sf::Color(34, 117, 56);

        float espacioVertical = 10;  // Espacio vertical entre las leyendas

        sf::Text leyendaPLOMO("PLOMO: Finger vacio", font);
        leyendaPLOMO.setCharacterSize(24);
        leyendaPLOMO.setFillColor(COLOR_PLOMO);

        leyendaPLOMO.setPosition(leyendaX - leyendaPLOMO.getLocalBounds().width, leyendaY);
        leyendaY += leyendaPLOMO.getLocalBounds().height + espacioVertical;

        sf::Text leyendaROJO("ROJO: Finger de un solo elemento", font);
        leyendaROJO.setCharacterSize(24);
        leyendaROJO.setFillColor(COLOR_ROJO);

        leyendaROJO.setPosition(leyendaX - leyendaROJO.getLocalBounds().width, leyendaY);
        leyendaY += leyendaROJO.getLocalBounds().height + espacioVertical;

        sf::Text leyendaAZUL("AZUL: Nodo afijo", font);
        leyendaAZUL.setCharacterSize(24);
        leyendaAZUL.setFillColor(COLOR_AZUL);

        leyendaAZUL.setPosition(leyendaX - leyendaAZUL.getLocalBounds().width, leyendaY);
        leyendaY += leyendaAZUL.getLocalBounds().height + espacioVertical;

        sf::Text leyendaAMARILLO("AMARILLO: Nodo", font);
        leyendaAMARILLO.setCharacterSize(24);
        leyendaAMARILLO.setFillColor(COLOR_AMARILLO);

        leyendaAMARILLO.setPosition(leyendaX - leyendaAMARILLO.getLocalBounds().width, leyendaY);
        leyendaY += leyendaAMARILLO.getLocalBounds().height + espacioVertical;

        sf::Text leyendaNEGRO("NEGRO: Valor", font);
        leyendaNEGRO.setCharacterSize(24);
        leyendaNEGRO.setFillColor(COLOR_NEGRO);

        leyendaNEGRO.setPosition(leyendaX - leyendaNEGRO.getLocalBounds().width, leyendaY);
        leyendaY += leyendaNEGRO.getLocalBounds().height + espacioVertical;

        sf::Text leyendaVERDE("VERDE: Finger", font);
        leyendaVERDE.setCharacterSize(24);
        leyendaVERDE.setFillColor(COLOR_VERDE);

        leyendaVERDE.setPosition(leyendaX - leyendaVERDE.getLocalBounds().width, leyendaY);

        window.draw(leyendaPLOMO);
        window.draw(leyendaROJO);
        window.draw(leyendaAZUL);
        window.draw(leyendaAMARILLO);
        window.draw(leyendaNEGRO);
        window.draw(leyendaVERDE);

        window.display();

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::TextEntered) {
        if (in_push > 0) {
          // change status when enter is pressed. until then verify user input
          // to add only numbers
          if (event.text.unicode >= 48 && event.text.unicode <= 57) {
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
