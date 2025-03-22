/*
los datos deberian de ser de cualquier clase
*/


#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<fstream>

using namespace std;

//funcion que genera datos aleatorios
vector<int> generate_random_data(size_t size){
    vector<int> data(size);
    generate(data.begin(), data.end(), [] () {return rand() % 100000;});    //MODIFICADO AQUI
    return data;
}


//funcion que genera datos ordenados
vector<int> generate_sorted_data(size_t size){
    vector<int> data(size);
    generate(data.begin(), data.end(), []() { return rand() % 100000; });           //MODIFICADO AQUI
    return data;
}


//funcion que genera datos parcialmente ordenados
vector<int> generate_partial_sorted_data(size_t size){
    vector<int> data(size);
    size_t sorted_size = static_cast<size_t>(size * 0.7);
    for (size_t i = 0; i < sorted_size; ++i) {
        data[i] = i;                                        // Parte ordenada
    }
    for (size_t i = sorted_size; i < size; ++i) {
        data[i] = rand() % 10000;                            // Parte aleatoria   // Cambia el tamaño según sea necesario
    }
    return data;
}



//funcion que genera datos duplicados
vector<int> generate_data_with_duplicates(size_t size){
    vector<int> data(size);
    for (size_t i = 0; i < size; ++i){
        data[i] = rand() % 1000;                       // Duplicados en el rango de 0 a 999 ojo aqui
    }
    return data;
}


// Función para guardar datos en un archivo binario
void save_to_binary_file(const string& filename, const vector<int>& data){
    ofstream outFile(filename, ios::binary);
    if (outFile.is_open()){
        outFile.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(int));
        outFile.close();
        cout << "Datos guardados en " << filename << endl;
    } else {
        cerr << "No se pudo abrir el archivo " << filename << endl;
    }
}



int main(){
    size_t dataset_size = 100000;                                            // Cambia el tamaño según sea necesario

    // Generar diferentes tipos de datasets
    vector<int> random_data = generate_random_data(dataset_size);
    vector<int> sorted_data = generate_sorted_data(dataset_size);
    vector<int> partial_sorted_data = generate_partial_sorted_data(dataset_size);
    vector<int> data_with_duplicates = generate_data_with_duplicates(dataset_size);

    // Guardar los datasets en archivos binarios
    save_to_binary_file("random_data.bin", random_data);
    save_to_binary_file("sorted_data.bin", sorted_data);
    save_to_binary_file("partial_sorted_data.bin", partial_sorted_data);
    save_to_binary_file("data_with_duplicates.bin", data_with_duplicates);


    /*
    // Aquí puedes imprimir o utilizar los datasets generados
    // Por ejemplo, imprimir el primer elemento de cada dataset
    std::cout << "Primer elemento de datos aleatorios: " << random_data[0] << std::endl;
    std::cout << "Primer elemento de datos ordenados: " << sorted_data[0] << std::endl;
    std::cout << "Primer elemento de datos parcialmente ordenados: " << partial_sorted_data[0] << std::endl;
    std::cout << "Primer elemento de datos con duplicados: " << data_with_duplicates[0] << std::endl;
    */

    /*
    // Imprimir los datos de cada dataset
    std::cout << "Datos aleatorios:" << std::endl;
        for (const int& num : random_data) {
            std::cout << num << " ";
        }
    std::cout << std::endl;
    
    std::cout << "\n";

    std::cout << "Datos ordenados:" << std::endl;
        for (const int& num : sorted_data) {
            std::cout << num << " ";
        }
    std::cout << std::endl;

    std::cout << "\n";

    std::cout << "Datos parcialmente ordenados:" << std::endl;
        for (const int& num : partial_sorted_data) {
            std::cout << num << " ";
        }
    std::cout << std::endl;

    std::cout << "\n";

    std::cout << "Datos con duplicados:" << std::endl;
        for (const int& num : data_with_duplicates) {
            std::cout << num << " ";
        }
    std::cout << std::endl;

    std::cout << "\n";*/



    return 0;

}

