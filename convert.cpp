#include <iostream>
#include <fstream>
#include <vector>

//Función para convertir un archivo binario a un archivo .csv
void convertBinToCSV(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream inputFile(inputPath, std::ios::binary); //Abre el archivo binario de entrada
    std::ofstream outputFile(outputPath); //Abre el archivo .csv de salida

    //Verifica que el archivo de entrada se haya abierto correctamente
    if (!inputFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << inputPath << std::endl;
        return;
    }

    //Verifica que el archivo de salida se haya abierto correctamente
    if (!outputFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << outputPath << std::endl;
        return;
    }

    //Crea un buffer para leer el archivo binario
    std::vector<int> buffer(1024); //Tamaño del buffer para la lectura
    bool first = true; //Indicador para la primera coma

    //Lee el archivo binario en bloques
    while (inputFile.read(reinterpret_cast<char*>(buffer.data()), buffer.size() * sizeof(int))) {
        std::streamsize bytesRead = inputFile.gcount(); //Cantidad de bytes leídos
        std::streamsize elementsRead = bytesRead / sizeof(int); //Cantidad de enteros leídos

        //Escribe los enteros leídos en el archivo .csv
        for (std::streamsize i = 0; i < elementsRead; ++i) {
            if (!first) {
                outputFile << ","; //Agrega una coma si no es el primer número
            }
            outputFile << buffer[i]; //Escribe el entero en el archivo .csv
            first = false; //Marca que no es el primer número
        }
    }

    //Procesa los posibles elementos restantes en el buffer
    std::streamsize bytesRead = inputFile.gcount(); //Cantidad de bytes leídos
    std::streamsize elementsRead = bytesRead / sizeof(int); //Cantidad de enteros leídos

    //Escribe los enteros restantes en el archivo .csv
    for (std::streamsize i = 0; i < elementsRead; ++i) {
        if (!first) {
            outputFile << ","; //Agrega una coma si no es el primer número
        }
        outputFile << buffer[i]; //Escribe el entero en el archivo .csv
        first = false; //Marca que no es el primer número
    }

    //Cierra los archivos
    inputFile.close();
    outputFile.close();

    std::cout << "Conversion a archivo .csv completada con exito." << std::endl; // Mensaje de éxito
}

int main() {
    std::string inputPath = "output.bin"; //Ruta del archivo binario de entrada
    std::string outputPath = "output.csv"; //Ruta del archivo .csv de salida

    convertBinToCSV(inputPath, outputPath); //Llama a la función de conversión

    return 0;
}