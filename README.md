# Finger_tree
## Integrantes
- Piero Jesús Guerrero Jiménez.
- Mauricio Rivera Cerron
- Leonardo Fabian Huaman Casma

## Detalles de la aplicación
Esta aplicación fue creada con SFML. Esta es una librería diseñada para dar una interfaz sinple a aplicaciones multimedia. 

Para poder apreciar de una manera más sencilla el funcionamiento de un Finger Tree.
Cuenta con una leyenda para saber los sgignificados de cada uno de los colores y un mensaje en la parte superior derecha para saber lo que se hizo en la última operación o un mensaje de error.

### ¿Cómo instalamos el SFML?

#### En Windows

El siguiente video mostrará paso a paso como instalar el SFML en Windows usando Visual Studio Code.

- [Video instalación SFML](https://youtu.be/Ptw1KKI9_Sg)

- Comandos para crear el app.exe

```sh
g++ -IC:/SFML-2.6.1/include -c Sfml.cpp -o Sfml.o
g++ -LC:/SFML-2.6.1/lib Sfml.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -mwindows
```

#### En Linux

Se usa el instalador de paquetes de Linux para instalar SFML. En la siguiente página se indica otras opciones si es que el paquete no está disponible. [Link hacia página](https://www.sfml-dev.org/tutorials/2.5/start-linux.php)

En secuencia se ejecuta los siguientes comandos en el terminal:

```sh
g++ -c Sfml.cpp
g++ Sfml.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-qpp
```

## Detalles de la APP

## Instrucciones de Uso.
1. Abrir el app.exe.
2. Insertar la operacion que desea realizar. Las posibles operaciones son: Push front, Push back, Pop front, Pop back y Cerrar aplicación. Luego de realizar una operación, se muestra el finger tree con los útlimos cambios.
3. En el caso de un push, luego se pide ingresar el valor.
