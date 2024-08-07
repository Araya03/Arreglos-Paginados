#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include "pagedarray.cpp"

//Funciones de ordenamiento
void quickSort(PagedArray& arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}

void insertionSort(PagedArray& arr, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        size_t j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            if (j == 0) break;
            j--;
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(PagedArray& arr, size_t n) {
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

bool copyFile(const std::string& srcPath, const std::string& dstPath) {
    std::ifstream src(srcPath, std::ios::binary);
    if (!src) {
        std::cerr << "No se pudo abrir el archivo de entrada para lectura: " << srcPath << std::endl;
        return false;
    }

    std::ofstream dst(dstPath, std::ios::binary);
    if (!dst) {
        std::cerr << "No se pudo abrir el archivo de salida para escritura: " << dstPath << std::endl;
        return false;
    }

    dst << src.rdbuf();
    src.close();
    dst.close();
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        std::cerr << "Uso: " << argv[0] << " -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>" << std::endl;
        return 1;
    }

    std::string inputPath, outputPath, algorithm;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-input" && i + 1 < argc) {
            inputPath = argv[++i];
        } else if (arg == "-output" && i + 1 < argc) {
            outputPath = argv[++i];
        } else if (arg == "-alg" && i + 1 < argc) {
            algorithm = argv[++i];
        } else {
            std::cerr << "Argumento desconocido o incompleto: " << arg << std::endl;
            return 1;
        }
    }

    //Copiar el archivo de entrada al archivo de salida
    if (!copyFile(inputPath, outputPath)) {
        return 1;
    }

    //Crear la instancia de PagedArray con el archivo de salida
    PagedArray arr(outputPath);

    //Determinar el tamaño del archivo en enteros
    std::ifstream inFile(outputPath, std::ios::binary | std::ios::ate);
    if (!inFile) {
        std::cerr << "No se pudo abrir el archivo de salida para lectura: " << outputPath << std::endl;
        return 1;
    }
    size_t fileSize = inFile.tellg();
    size_t numElements = fileSize / sizeof(int);
    inFile.close();

    //Medir el tiempo de ejecución
    auto start = std::chrono::high_resolution_clock::now();

    //Ejecutar el algoritmo de ordenamiento
    if (algorithm == "QS") {
        quickSort(arr, 0, numElements - 1);
    } else if (algorithm == "IS") {
        insertionSort(arr, numElements);
    } else if (algorithm == "BS") {
        bubbleSort(arr, numElements);
    } else {
        std::cerr << "Algoritmo no reconocido. Use QS, IS o BS." << std::endl;
        return 1;
    }

    //Medir el tiempo de ejecución
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    //Imprimir el resumen
    std::cout << "Tiempo de ejecucion: " << duration.count() << " segundos" << std::endl;
    std::cout << "Algoritmo utilizado: " << algorithm << std::endl;
    std::cout << "Page faults: " << arr.getPageFaults() << std::endl;
    std::cout << "Page hits: " << arr.getPageHits() << std::endl;

    return 0;
}