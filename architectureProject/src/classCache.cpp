#include <iostream>
#include <vector>

class Cache {
    public:

    // Constructor que inicializa la caché con un tamaño y tamaño de bloque específicos
    Cache(size_t size, size_t block_size)
        : size(size), block_size(block_size), hits(0), misses(0) {
        num_blocks = size / block_size;                                     // Calcula el número de bloques
        cache.resize(num_blocks, -1);                                       // Inicializa la caché con -1 (vacío)
    }


    // Método para acceder a una dirección de memoria
    void access(int address) {
        size_t index = (address / block_size) % num_blocks;                 // Calcula el índice del bloque
        if (cache[index] == address) {
            hits++;                                                         // Hit: la dirección ya está en la caché
        } else {
            misses++;                                                       // Miss: la dirección no está en la caché
            cache[index] = address;                                         // Actualiza la caché con la nueva dirección
        }
    }


    // Métodos para obtener estadísticas de la caché
    size_t getHits() const { return hits; }
    size_t getMisses() const { return misses; }
    

    // Método para calcular la tasa de aciertos
    double getHitRate() const {
        return (hits + misses) > 0 ? static_cast<double>(hits) / (hits + misses) : 0.0;
    }


    // Método para imprimir estadísticas de la caché
    void printStats() const {
        std::cout << "Hits: " << hits << ", Misses: " << misses 
                  << ", Hit Rate: " << getHitRate() * 100 << "%" << std::endl;
    }

    private:
        size_t size;                                                              // Tamaño total de la caché
        size_t block_size;                                                        // Tamaño de cada bloque
        size_t num_blocks;                                                        // Número de bloques en la caché
        std::vector<int> cache;                                                   // Vector que representa la caché
        size_t hits;                                                              // Contador de hits
        size_t misses;                                                            // Contador de misses
};