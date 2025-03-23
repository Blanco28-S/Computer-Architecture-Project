#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> read_from_binary_file(const string& filename, size_t size) {
    vector<int> data(size);
    ifstream inFile(filename, ios::binary);
    if (inFile.is_open()) {
        inFile.read(reinterpret_cast<char*>(data.data()), size * sizeof(int));
        inFile.close();
    } else {
        cerr << "No se pudo abrir el archivo " << filename << endl;
    }
}

int main()