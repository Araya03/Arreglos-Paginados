#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <cassert>

//Clase que representa un arreglo paginado
class PagedArray {
private:
    const size_t PAGE_SIZE = 128; //Tamaño de página (en cantidad de enteros)
    const size_t NUM_PAGES = 4; //Máximo número de páginas en memoria
    std::string filePath; //Ruta del archivo que contiene los datos
    std::unordered_map<size_t, std::vector<int>> pages; //Páginas en memoria
    std::vector<size_t> pageOrder; //Orden de páginas en memoria
    size_t pageHits = 0; //Contador de aciertos de página
    size_t pageFaults = 0; //Contador de fallos de página

    //Método para cargar una página desde el archivo
    void loadPage(size_t pageIndex) {
        if (pages.size() >= NUM_PAGES) { //Si el número de páginas en memoria alcanza el máximo permitido, se usa una política de reemplazo (FIFO)
            size_t pageToEvict = pageOrder.front(); //Página a eliminar (la más antigua)
            pageOrder.erase(pageOrder.begin()); //Remueve la página del orden de páginas
            pages.erase(pageToEvict); //Elimina la página de la memoria
        }

        std::ifstream file(filePath, std::ios::binary); //Abre el archivo en modo binario
        if (!file.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo: " + filePath); //Lanza una excepción si no se puede abrir el archivo
        }

        std::vector<int> page(PAGE_SIZE); //Crea un vector para almacenar la página
        file.seekg(pageIndex * PAGE_SIZE * sizeof(int), std::ios::beg); //Posiciona el cursor del archivo en el lugar correcto para leer la página deseada
        file.read(reinterpret_cast<char*>(page.data()), PAGE_SIZE * sizeof(int)); //Lee los datos del archivo en el vector "page"

        // Verificar si la lectura fue completa
        if (!file) {
            throw std::runtime_error("Error al leer la página desde el archivo");
        }

        file.close(); //Cierra el archivo

        pages[pageIndex] = page; //Guarda la página en el mapa "pages"
        pageOrder.push_back(pageIndex); //Registra el orden de la página cargada
    }

public:
    //Constructor que inicializa 'filePath' con la ruta del archivo
    explicit PagedArray(const std::string& path) : filePath(path) {
        //Validar si el archivo existe y tiene el tamaño esperado
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);
        if (!file.is_open() || file.tellg() == 0) {
            throw std::runtime_error("El archivo no existe o está vacío: " + filePath);
        }
        file.close();
    }

    //Sobrecarga del operador '[]' para acceder a un elemento en el arreglo paginado
    int& operator[](size_t index) {
        size_t pageIndex = index / PAGE_SIZE; //Calcula el índice de la página
        size_t offset = index % PAGE_SIZE; //Calcula el desplazamiento dentro de la página

        //Si la página no está en memoria, se carga
        if (pages.find(pageIndex) == pages.end()) {
            loadPage(pageIndex);
            pageFaults++; //Incrementa el contador de fallos de página
        } else {
            pageHits++; //Si ya está en memoria, incrementa el contador de aciertos de página
        }

        return pages[pageIndex][offset]; //Devuelve una referencia al elemento solicitado dentro de la página
    }

    //Métodos para obtener los contadores de aciertos y fallos de página
    size_t getPageHits() const {
        return pageHits;
    }

    size_t getPageFaults() const {
        return pageFaults;
    }
};