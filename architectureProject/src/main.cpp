#include <stdexcept>
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include "MemoryAnalyzer.h"

// Añadir al inicio:
#include <stdexcept>

// Mejorar la función printResults:
void printResults(const std::vector<MemoryAnalyzer::SortResult>& results, const int colWidth = 15) {
    
    //const int colWidth = 15;
    
    auto printLine = [&]() {
        std::cout << std::string(colWidth * 6, '-') << '\n';
    };

    printLine();
    std::cout << "\033[1;33m"; // color amarillo
    std::cout << std::left 
              << std::setw(colWidth) << "Algorithm" << std::setw(colWidth) << "Data Size"
              << std::setw(colWidth) << "Cache Hits" << std::setw(colWidth) << "Cache Misses"
              << std::setw(colWidth) << "Hit Rate" << std::setw(colWidth) << "Time (s)"
              << std::endl;
    std::cout << "\033[0m"; // color amarillo
    printLine();



    for (const auto& result : results) {
        std::cout << std::left << std::fixed 
                  << std::setw(colWidth) << result.algorithm
                  << std::setw(colWidth) << result.data_size
                  << std::setw(colWidth) << result.cache_hits
                  << std::setw(colWidth) << result.cache_misses
                  << std::setprecision(4) << std::setw(colWidth) << result.hit_rate
                  << std::setprecision(6) << std::setw(colWidth) << result.execution_time
                  << '\n';
    }
    printLine();
}

std::vector<int> generateRandomData(size_t size) {
    std::vector<int> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 10000);
    
    for (auto& num : data) {
        num = dis(gen);
    }
    
    return data;
}

void runAnalysisForDifferentSizes(MemoryAnalyzer& analyzer) {
    std::vector<size_t> sizes = {1000, 5000, 10000, 50000, 100000};
    std::vector<MemoryAnalyzer::SortResult> results;
    
    for (size_t size : sizes) {
        auto data = generateRandomData(size);
        
        results.push_back(analyzer.analyzeQuickSort(data));
        results.push_back(analyzer.analyzeMergeSort(data));
    }
    
    printResults(results);
}

void runAnalysisForDifferentCacheConfigs(const std::vector<int>& data) {
    std::vector<std::pair<uint32_t, uint32_t>> configs = {
        {1024, 16},   // 1KB cache, 16B blocks
        {2048, 32},    // 2KB cache, 32B blocks
        {4096, 64},    // 4KB cache, 64B blocks
        {8192, 128}    // 8KB cache, 128B blocks
    };
    
    std::vector<MemoryAnalyzer::SortResult> results;
    
    for (const auto& config : configs) {
        MemoryAnalyzer analyzer(config.first, config.second);
        
        results.push_back(analyzer.analyzeQuickSort(data));
        results.back().algorithm += " (C:" + std::to_string(config.first) + 
                                  ",B:" + std::to_string(config.second) + ")";
        
        results.push_back(analyzer.analyzeMergeSort(data));
        results.back().algorithm += " (C:" + std::to_string(config.first) + 
                                   ",B:" + std::to_string(config.second) + ")";
    }
    
    printResults(results);
}

int main() {
    // Configuración inicial de la caché
    const uint32_t initial_cache_size = 4096; // 4KB
    const uint32_t initial_block_size = 64;   // 64B
    
    MemoryAnalyzer analyzer(initial_cache_size, initial_block_size);
    
    std::cout << "Análisis para diferentes tamaños de datos:\n";
    runAnalysisForDifferentSizes(analyzer);
    
    std::cout << "\nAnálisis para diferentes configuraciones de caché (con 10,000 elementos):\n";
    auto medium_data = generateRandomData(10000);
    runAnalysisForDifferentCacheConfigs(medium_data);
    
    return 0;
}
