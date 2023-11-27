# Finger_tree
## Integrantes
- Piero Jesús Guerrero Jiménez.
- Mauricio Rivera Cerron
- Leonardo Fabian Huaman Casma

## Detalles de la APP.
Esta app fue creada con SFML, esta diseñada para poder apreciar de una manera más sencilla el funcionamiento de un Finger Tree.
Cuenta con una leyenda para saber los sgignificados de cada una de los colores y un mensaje en la parte superior dercha para saber que se esta realizando o un mensaje de error.

### ¿Como instalamos el SFML?

#### En Windows

El siguiente video mostrará paso a paso como instalar el SFML en Windows usando Visual Studio Code.

- [Video instalación SFML](https://youtu.be/Ptw1KKI9_Sg)

- Comandos para crear el app.exe

```sh
g++ -IC:/SFML-2.6.1/include -c Sfml.cpp -o Sfml.o
g++ -LC:/SFML-2.6.1/lib Sfml.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -mwindows
```

#### En Linux

Se usa el instalador de paquetes para instalar sfml. En la siguiente pagina se indica otras opciones si es que no se tiene el paquete disponible. [Link hacia página](https://www.sfml-dev.org/tutorials/2.5/start-linux.php)

En secuencia se ejecuta los siguientes comandos en el terminal:

```sh
g++ -c Sfml.cpp
g++ Sfml.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-qpp
```


## Instrucciones de Uso.
1. Abrir el app.exe
2. Insertar la operacion que desea realizar
3. En el caso de un push, se ingresa el valor.
4. En el caso de un pop se muestra el Finger con el elemento eliminado.
