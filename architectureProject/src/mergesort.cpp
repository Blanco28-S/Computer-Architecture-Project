#include<iostream>
#include<vector>
#include<fstream>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergesort(arr, left, mid);                                      // Ordenamos la primera mitad
        mergesort(arr, mid + 1, right);                                 // Ordenamos la segunda mitad
        merge(arr, left, mid, right);                                   // Fusiona las dos mitades
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


    size_t dataset_size = 1000; // Cambia esto al tamaño de tus datasets

    // Leer los datos desde los archivos binarios
    std::vector<int> random_data = read_from_binary_file("random_data.bin", dataset_size);
    std::vector<int> sorted_data = read_from_binary_file("sorted_data.bin", dataset_size); 
    std::vector<int> partial_sorted_data = read_from_binary_file("partial_sorted_data.bin", dataset_size); 
    std::vector<int> data_with_duplicates = read_from_binary_file("data_with_duplicates.bin", dataset_size);

    // Aplicar Mergesort y mostrar resultados
    std::vector<std::string> dataset_names = {"Datos aleatorios", "Datos ordenados", "Datos parcialmente ordenados", "Datos con duplicados"}; 
    std::vector<std::vector<int>*> datasets = {&random_data, &sorted_data, &partial_sorted_data, &data_with_duplicates}; 

    for (size_t i = 0; i < datasets.size(); ++i) {
        std::cout << dataset_names[i] << " (sin ordenar): ";
        for (const int& num : *datasets[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        std::cout << "\n";
        mergesort(*datasets[i], 0, datasets[i]->size() - 1);

        std::cout << dataset_names[i] << " (ordenado): ";
        for (const int& num : *datasets[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl << std::endl;
        std::cout << std::endl; //
        std::cout << "\n";
    }

    return 0;

}
