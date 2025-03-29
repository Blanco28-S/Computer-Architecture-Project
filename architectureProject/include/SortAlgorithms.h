


#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <vector>
#include <functional>
#include <cstdint> // Incluido

class SortAlgorithms {
public:
    static void quickSort(std::vector<int>& data, std::function<void(uint64_t)> memoryAccessCallback = nullptr);
    static void mergeSort(std::vector<int>& data, std::function<void(uint64_t)> memoryAccessCallback = nullptr);
    
private:
    static void quickSortHelper(std::vector<int>& data, int low, int high, std::function<void(uint64_t)> callback);
    static int partition(std::vector<int>& data, int low, int high, std::function<void(uint64_t)> callback);
    
    static void mergeSortHelper(std::vector<int>& data, int left, int right, std::function<void(uint64_t)> callback);
    static void merge(std::vector<int>& data, int left, int mid, int right, std::function<void(uint64_t)> callback);
    
    static void simulateMemoryAccess(uint64_t address, std::function<void(uint64_t)> callback);
};

#endif // SORT_ALGORITHMS_H
