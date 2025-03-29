

#include "MemoryAnalyzer.h"
#include "SortAlgorithms.h"

#include <chrono>
#include <random>
#include <algorithm>
#include <random>

MemoryAnalyzer::MemoryAnalyzer(uint32_t cache_size, uint32_t block_size) 
    : cache_simulator(cache_size, block_size), 
      current_cache_size(cache_size),
      current_block_size(block_size) {}


MemoryAnalyzer::SortResult MemoryAnalyzer::analyzeQuickSort(const std::vector<int>& data) {
    return runAnalysis(data, "QuickSort", &SortAlgorithms::quickSort);
}

MemoryAnalyzer::SortResult MemoryAnalyzer::analyzeMergeSort(const std::vector<int>& data) {
    return runAnalysis(data, "MergeSort", &SortAlgorithms::mergeSort);
}

void MemoryAnalyzer::setCacheSize(uint32_t cache_size) {
    current_cache_size = cache_size;
    cache_simulator = CacheSimulator(cache_size, current_block_size);
}


void MemoryAnalyzer::setBlockSize(uint32_t block_size) {
    current_block_size = block_size;
    cache_simulator = CacheSimulator(current_cache_size, block_size);
}



std::vector<int> MemoryAnalyzer::prepareData(const std::vector<int>& original_data) {
    // Hacer una copia y mezclar los datos para evitar sesgos en el ordenamiento
    std::vector<int> data = original_data;
    std::random_device rd;
    std::mt19937 g(rd());  // Generador aleatorio
    std::shuffle(data.begin(), data.end(), g);
    return data;
}

MemoryAnalyzer::SortResult MemoryAnalyzer::runAnalysis(
    const std::vector<int>& data, 
    const std::string& algorithm_name,
    void (*sort_func)(std::vector<int>&, std::function<void(uint64_t)>)) {
    
    std::vector<int> prepared_data = prepareData(data);
    
    // Resetear la caché antes de cada análisis
    cache_simulator.reset();
    
    auto start_time = std::chrono::high_resolution_clock::now();
    
    sort_func(prepared_data, [this](uint64_t address) {
        cache_simulator.accessMemory(address);
    });
    
    auto end_time = std::chrono::high_resolution_clock::now();
    double execution_time = std::chrono::duration<double>(end_time - start_time).count();
    
    return {
        algorithm_name,
        static_cast<uint32_t>(data.size()),
        cache_simulator.getHitCount(),
        cache_simulator.getMissCount(),
        cache_simulator.getHitRate(),
        execution_time
    };
}
