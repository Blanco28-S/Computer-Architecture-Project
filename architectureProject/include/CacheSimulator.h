/*
simulador de cache (correspondencia directa)
*/


#ifndef CACHE_SIMULATOR_H
#define CACHE_SIMULATOR_H

#include <vector>
#include <cstdint>

class CacheSimulator {
public:
    CacheSimulator(uint32_t cache_size, uint32_t block_size, uint32_t associativity = 1);
    
    void reset();
    bool accessMemory(uint64_t address);
    
    uint32_t getHitCount() const;
    uint32_t getMissCount() const;
    double getHitRate() const;

    // Añadir estos nuevos métodos
    uint32_t getCacheSize() const { return cache_size; }
    uint32_t getBlockSize() const { return block_size; }
    uint32_t getAssociativity() const { return associativity; }
    
private:
    struct CacheBlock {
        bool valid;
        uint64_t tag;
    };
    
    uint32_t cache_size;
    uint32_t block_size;
    uint32_t associativity;
    uint32_t block_count;
    uint32_t sets;
    uint32_t hits;
    uint32_t misses;
    
    std::vector<std::vector<CacheBlock>> cache;
    
    uint64_t getTag(uint64_t address) const;
    uint64_t getIndex(uint64_t address) const;
};

#endif // CACHE_SIMULATOR_H