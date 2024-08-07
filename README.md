# Arreglos-Paginados
GENERATOR

Para hacer uso de la aplicación GENERATOR, es necesario abrir una terminal dentro de la carpeta donde se guardó el archivo. Seguidamente, se debe compilar el código de la siguiente manera:

g++ -o generator generator.cpp

Luego se debe ejecutar el programa con el siguiente comando:

./generator -size <size> -output <output file path>

Por ejemplo:

./generator -size SMALL -output output.bin

Esto creará un archivo de tamaño pequeño (512MB) en output.bin de números enteros en binario.
