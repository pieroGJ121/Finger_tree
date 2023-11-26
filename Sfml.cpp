#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(1900, 1070), "Matriz SFML");

    std::vector<int> opciones;
    std::vector<int> valores;
    int opcion_elegida = 0;
    int opcion = 0;
    int valor = 0;
    bool ingresando_opcion = true;

    sf::Font font;
    font.loadFromFile("SulphurPoint-Regular.ttf");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 13) { 
                    if (ingresando_opcion) {
                        opcion_elegida = opcion;
                        opciones.push_back(opcion_elegida);
                        opcion = 0;
                        ingresando_opcion = false;
                        if (opcion_elegida == 5) {
                            std::cout << "Mostrando Finger Tree\n";
                        } else if (opcion_elegida == 6) {
                            window.close();
                        }
                    } else {
                        valores.push_back(valor);
                        valor = 0;
                        ingresando_opcion = true;
                    }
                } else if (event.text.unicode == 8) {  
                    if (ingresando_opcion) {
                        opcion /= 10;
                    } else {
                        valor /= 10;
                    }
                } else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    if (ingresando_opcion) {
                        opcion = opcion * 10 + (event.text.unicode - '0');
                    } else {
                        valor = valor * 10 + (event.text.unicode - '0');
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        sf::Text displayText;
        displayText.setFont(font);
        displayText.setCharacterSize(20);
        displayText.setFillColor(sf::Color::White);

        std::string displayString = "Opciones: ";
        for (int option : opciones) {
            displayString += std::to_string(option) + " ";
        }

        displayString += "\nValores: ";
        for (int value : valores) {
            displayString += std::to_string(value) + " ";
        }

        displayText.setString(displayString);
        displayText.setPosition(20, 20);
        window.draw(displayText);

        sf::Text inputText(
            sf::String("\nIngrese su opcion: " + std::to_string(opcion) + "\n\n"
                       "1. Push front\n"
                       "2. Push back\n"
                       "3. Pop front\n"
                       "4. Pop back\n"
                       "5. Mostrar Finger Tree\n"
                       "6. Cerrar Aplicacion\n\n"
                       "Ingrese valor: " + std::to_string(valor) + "\n"),
            font
        );  

        inputText.setPosition(20, 20 + displayText.getGlobalBounds().height + 10);
        inputText.setCharacterSize(24);
        inputText.setFillColor(sf::Color::White);
        window.draw(inputText);

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
              message = "No se permite la cadena vacía.";
            } else {
              if (in_push == 1) {
                finger->push_front(value);
              } else {
                finger->push_back(value);
              }
              value = "";
              opcion = "";
              // message = finger->message();
              in_push = 0;
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
          } else if (event.text.unicode == '4') {
            finger->pop_back();
          } else if (event.text.unicode == '5') {
            window.close();
          } else {
            message = "Escoje una opción válida";
          }
        }
      }
    }
  }

  return 0;
}
