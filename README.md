# Arreglos-Paginados
GENERATOR

Para hacer uso de la aplicación GENERATOR, es necesario abrir una terminal dentro de la carpeta donde se guardó el archivo. Seguidamente, se debe compilar el código de la siguiente manera:

g++ -o generator generator.cpp

Luego se debe ejecutar el programa con el siguiente comando:

./generator -size "SIZE" -output "OUTPUT FILE PATH"

Por ejemplo:

./generator -size SMALL -output input.bin

Esto creará un archivo de tamaño pequeño (512MB) en "input.bin" de números enteros en binario.

SORTER

Para hacer uso de la aplicación SORTER, es necesario abrir una terminal dentro de la carpeta donde se guardó el archivo. Seguidamente, se debe compilar el código de la siguiente manera:

g++ sorter.cpp pagedarray.cpp -o sorter

Luego se debe ejecutar el programa con el siguiente comando:

./sorter -input "INPUT FILE PATH" -output "OUTPUT FILE PATH" -alg "ALGORITHM"

Por ejemplo:

./sorter -input input.bin -output output.bin -alg QS

Esto tomará el archivo de entrada "input.bin" y lo ordenará, guardándolo en "output.bin".

CONVERT

Para hacer uso de la aplicación CONVERT, es necesario abrir una terminal dentro de la carpeta donde se guardó el archivo. Seguidamente, se debe compilar el código de la siguiente manera:

g++ -o convert convert.cpp

Luego se debe ejecutar el programa con el siguiente comando:

./convert

Esto pasará el archivo ordenado en binario, a números enteros legibles, lo cual permite verificar que se encuentren ordenados de manera correcta.
