# Proyecto2-Modelado
## Modelado y Programación. Proyecto 2: Estenografía LSB

### Integrantes:
 - Carlos Daniel Cortés Jiménez.
 - Víctor Emiliano Cruz Hernández.

### Descripción del proyecto: 

El propósito del sistema es dado una imagen de entrada (específicamente en formato png) y un archivo de texto (cuyo contenido se quiere ocultar), se genere una imagen que contenga el contenido del archivo de texto que a simple vista sea igual a la imagen inicial, pero que con un proceso aparte de develado, se pueda obtener el texto original. 

### Limitaciones

El proceso de Estenografía por el método LSB lo limitamos a únicamente imágenes png, por lo que la imagen de entrada y de salida deben de ser imágenes en formato png.

Por el proceso de estenografía la imagen de entrada debe de tener al menos el doble de pixeles que el número de caracteres del texto a ocultar.

## Requisitos, compilación y ejecución:

Utilizamos C++ como lenguaje para nuestro sistema. Nos apoyamos en el proyecto OpenCV para manipular las imágenes y en CMake como plataforma para el desarrollo de nuestro proyecto.

Es necesario tener instalado un complidador de c++, las bibliotecas de openCV y CMake. Todo esto se puede hacer siguiendo las instrucciones en : 
https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html


Una vez con lo anterior instalado y clonado este repositorio, crear una carpeta llamada build:

```
$ mkdir build
$ cd build
```
Después ejecutar:

```
$ cmake ..
$ make
```
Esto generará un ejcutable llamado Esteno. 

Para usar el sistema se utilizan dos banderas: -h y -u. Esconder y develar, respectivamente. 

Si tenemos nuestra imagen "Cat.png" y nuestro archivo de texto "texto.txt", para ocultar el contenido del archivo en la imagen llamada "Salida.png":

```
$ ./Esteno -h Cat.png texto.txt Salida.png
```

Esto nos regresa una imagen llamada Salida.png con el contenido del archivo de texto oculto.

Si tenemos nuestro archivo con texto oculto "Salida.png" para develar el contenido en el archivo "salidaTexto.txt" ejectuamos:


```
$ ./Esteno -u Salida.png salidaTexto.txt
```
Y nos genera el archivo "salidaTexto.txt" con el contenido develado.
Cabe aclarar que el nombre de los archivo son sus rutas dentro de la computadora.


