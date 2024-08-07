#include <iostream>
#include <fstream>
#include <random>
#include <string>

class GeneradorArchivo { //Clase generadora de archivos binarios aleatorios
public:
    GeneradorArchivo(const std::string& size, const std::string& rutaSalida) //Constructor de la clase que recibe el tamaño y la ruta del archivo de salida
        : tamano(obtenerTamano(size)), rutaSalida(rutaSalida) {}

    void generarArchivo() { //Función que genera el archivo
        if (tamano == 0) return; //Si el tamaño en bytes es 0, no se hace nada

        std::ofstream outputFile(rutaSalida, std::ios::out | std::ios::binary); //Abre el archivo de salida en modo binario
        if (!outputFile) { //Si no se puede abrir el archivo, muestra un mensaje de error y retorna
            std::cerr << "Error al abrir el archivo de salida: " << rutaSalida << std::endl;
            return;
        }

        std::random_device rd; //Generador de números aleatorios
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 100);

        size_t numberOfIntegers = tamano / sizeof(int); //Calcula el número de enteros que caben en el tamaño en bytes especificado
        for (size_t i = 0; i < numberOfIntegers; ++i) {  //Escribe números enteros aleatorios en el archivo
            int randomNumber = dis(gen);
            outputFile.write(reinterpret_cast<char*>(&randomNumber), sizeof(int));
        }

        outputFile.close();  //Cierra el archivo de salida
        std::cout << "Archivo generado exitosamente en: " << rutaSalida << std::endl;
    }

private:
    size_t tamano; //Tamaño del archivo en bytes
    std::string rutaSalida; //Ruta del archivo de salida

    size_t obtenerTamano(const std::string& size) { //Función que convierte el tamaño en una cadena de texto al tamaño en bytes
        if (size == "SMALL") return static_cast<size_t>(512000) * 1024;
        if (size == "MEDIUM") return static_cast<size_t>(1000000) * 1024;
        if (size == "LARGE") return static_cast<size_t>(2000000) * 1024;
        std::cerr << "Argumento de tamaño inválido. Use SMALL, MEDIUM, or LARGE." << std::endl;
        return 0;
    }
};

int main(int argc, char* argv[]) { //Función principal que maneja los argumentos de la línea de comandos
    if (argc != 5) { //Verifica que la cantidad de argumentos sea correcta
        std::cerr << "Use: " << argv[0] << " -size <SIZE> -output <OUTPUT FILE PATH>" << std::endl;
        return 1;
    }

    std::string tamanoArgumento, argumentoSalida;
    for (int i = 1; i < argc; ++i) { //Procesa los argumentos de la línea de comandos
        std::string arg = argv[i];
        if (arg == "-size" && i + 1 < argc) {
            tamanoArgumento = argv[++i];
        } else if (arg == "-output" && i + 1 < argc) {
            argumentoSalida = argv[++i];
        } else {
            std::cerr << "Argumento desconocido o incompleto: " << arg << std::endl;
            return 1;
        }
    }

    GeneradorArchivo generator(tamanoArgumento, argumentoSalida);  //Crea una instancia del generador y genera el archivo
    generator.generarArchivo();

    return 0;
}