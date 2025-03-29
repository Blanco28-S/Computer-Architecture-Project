#include "CacheSimulator.h"
#include <cmath>

CacheSimulator::CacheSimulator(uint32_t cache_size, uint32_t block_size, uint32_t associativity) 
    : cache_size(cache_size), block_size(block_size), associativity(associativity), hits(0), misses(0) {
    
    // Calcular número de bloques y conjuntos
    block_count = cache_size / block_size;
    sets = block_count / associativity;
    
    // Inicializar la caché
    cache.resize(sets, std::vector<CacheBlock>(associativity, {false, 0}));
}

void CacheSimulator::reset() {
    hits = 0;
    misses = 0;
    for (auto& set : cache) {
        for (auto& block : set) {
            block.valid = false;
            block.tag = 0;
        }
    }
}

bool CacheSimulator::accessMemory(uint64_t address) {
    uint64_t index = getIndex(address);
    uint64_t tag = getTag(address);
    
    // Buscar en el conjunto correspondiente
    for (auto& block : cache[index]) {
        if (block.valid && block.tag == tag) {
            hits++;
            return true; // Hit
        }
    }
    
    // Miss - reemplazar el primer bloque no válido o usar política FIFO/LRU
    misses++;
    for (auto& block : cache[index]) {
        if (!block.valid) {
            block.valid = true;
            block.tag = tag;
            return false;
        }
    }
    
    // Todos los bloques están ocupados - reemplazar el primero (política simple)
    cache[index][0].tag = tag;
    return false;
}

uint64_t CacheSimulator::getTag(uint64_t address) const {
    uint64_t block_address = address / block_size;
    return block_address / sets;
}

uint64_t CacheSimulator::getIndex(uint64_t address) const {
    uint64_t block_address = address / block_size;
    return block_address % sets;
}

uint32_t CacheSimulator::getHitCount() const {
    return hits;
}

uint32_t CacheSimulator::getMissCount() const {
    return misses;
}

double CacheSimulator::getHitRate() const {
    return static_cast<double>(hits) / (hits + misses);
}