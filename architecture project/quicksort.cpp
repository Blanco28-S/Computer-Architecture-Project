#include <iostream>
#include <vector>
#include <fstream>

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Elegimos el último elemento como pivote
    int i = low - 1; // Índice del elemento más pequeño

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]); // Intercambiamos si el elemento es menor que el pivote
        }
    }
    swap(arr[i + 1], arr[high]); // Colocamos el pivote en su posición correcta
    return i + 1; // Retornamos el índice del pivote
}

void quicksort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Particionamos el arreglo

        quicksort(arr, low, pi - 1); // Ordenamos los elementos antes del pivote
        quicksort(arr, pi + 1, high); // Ordenamos los elementos después del pivote
    }
}

// Función para leer datos desde un archivo binario
std::vector<int> read_from_binary_file(const std::string& filename, size_t size) {
    std::vector<int> data(size);
    std::ifstream inFile(filename, std::ios::binary);
    if (inFile.is_open()) {
        inFile.read(reinterpret_cast<char*>(data.data()), size * sizeof(int));
        inFile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
    }
    return data;
}

int main() {
    size_t dataset_size = 10000; // Cambia esto al tamaño de tus datasets

    // Leer los datos desde los archivos binarios
    std::vector<int> random_data = read_from_binary_file("random_data.bin", dataset_size);
    std::vector<int> sorted_data = read_from_binary_file("sorted_data.bin", dataset_size);
    std::vector<int> partial_sorted_data = read_from_binary_file("partial_sorted_data.bin", dataset_size);
    std::vector<int> data_with_duplicates = read_from_binary_file("data_with_duplicates.bin", dataset_size);

    // Aplicar Quicksort y mostrar resultados
    std::vector<std::string> dataset_names = {"Datos aleatorios", "Datos ordenados", "Datos parcialmente ordenados", "Datos con duplicados"};
    std::vector<std::vector<int>*> datasets = {&random_data, &sorted_data, &partial_sorted_data, &data_with_duplicates};

    for (size_t i = 0; i < datasets.size(); ++i) {
        /*std::cout << dataset_names[i] << " (sin ordenar): ";
        for (const int& num : *datasets[i]) {
            std::cout << num << " ";
        }*/
        std::cout << std::endl;

        quicksort(*datasets[i], 0, datasets[i]->size() - 1);

        std::cout << dataset_names[i] << " (ordenado): ";
        for (const int& num : *datasets[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl << std::endl;
    }

    return 0;
}