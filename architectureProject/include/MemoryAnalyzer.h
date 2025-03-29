#ifndef MEMORY_ANALYZER_H
//#ifndef MEMORY_ANALYZER_H
#define MEMORY_ANALYZER_H

#include "CacheSimulator.h"

#include <functional>
#include <vector>
#include <string>

class MemoryAnalyzer {
public:
    struct SortResult {
        std::string algorithm;
        uint32_t data_size;
        uint32_t cache_hits;
        uint32_t cache_misses;
        double hit_rate;
        double execution_time;
    };
    
    MemoryAnalyzer(uint32_t cache_size, uint32_t block_size);
    
    SortResult analyzeQuickSort(const std::vector<int>& data);
    SortResult analyzeMergeSort(const std::vector<int>& data);
    
    void setCacheSize(uint32_t cache_size);
    void setBlockSize(uint32_t block_size);
    
private:
    CacheSimulator cache_simulator;
    uint32_t current_cache_size;  // Nuevo: almacena tamaño de caché
    uint32_t current_block_size;  // Nuevo: almacena tamaño de bloque
    
    std::vector<int> prepareData(const std::vector<int>& original_data);
    
    SortResult runAnalysis(const std::vector<int>& data, const std::string& algorithm_name, 
                       void (*sort_func)(std::vector<int>&, std::function<void(uint64_t)>));
};

#endif // MEMORY_ANALYZER_H
