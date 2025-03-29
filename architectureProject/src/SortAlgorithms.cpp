#include "SortAlgorithms.h"
#include <algorithm>
#include <cstdint> 


void  SortAlgorithms::simulateMemoryAccess(uint64_t address, std::function<void(uint64_t)> callback) {
    if (callback) {
        callback(address);
    }
}

void SortAlgorithms::quickSort(std::vector<int>& data, std::function<void(uint64_t)> memoryAccessCallback) {
    quickSortHelper(data, 0, data.size() - 1, memoryAccessCallback);
}

void SortAlgorithms::quickSortHelper(std::vector<int>& data, int low, int high, std::function<void(uint64_t)> callback) {
    if (low < high) {
        int pi = partition(data, low, high, callback);
        quickSortHelper(data, low, pi - 1, callback);
        quickSortHelper(data, pi + 1, high, callback);
    }
}



int SortAlgorithms::partition(std::vector<int>& data, int low, int high, std::function<void(uint64_t)> callback) {
    int pivot = data[high];
    simulateMemoryAccess(reinterpret_cast<uint64_t>(&data[high]), callback);
    
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
        simulateMemoryAccess(reinterpret_cast<uint64_t>(&data[j]), callback);
        if (data[j] < pivot) {
            i++;
            std::swap(data[i], data[j]);
            simulateMemoryAccess(reinterpret_cast<uint64_t>(&data[i]), callback);
            simulateMemoryAccess(reinterpret_cast<uint64_t>(&data[j]), callback);
        }
    }
    
    std::swap(data[i + 1], data[high]);
    simulateMemoryAccess(reinterpret_cast<uint64_t>(&data[i + 1]), callback);
    simulateMemoryAccess(reinterpret_cast<uint64_t>(&data[high]), callback);
    
    return i + 1;
}

void SortAlgorithms::mergeSort(std::vector<int>& data, std::function<void(uint64_t)> memoryAccessCallback) {
    mergeSortHelper(data, 0, data.size() - 1, memoryAccessCallback);
}

void SortAlgorithms::mergeSortHelper(std::vector<int>& data, int left, int right, std::function<void(uint64_t)> callback) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSortHelper(data, left, mid, callback);
        mergeSortHelper(data, mid + 1, right, callback);
        
        merge(data, left, mid, right, callback);
    }
}

void SortAlgorithms::merge(std::vector<int>& data, int left, int mid, int right, std::function<void(uint64_t)> callback) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++) {
        L[i] = data[left + i];
        simulateMemoryAccess(reinterpret_cast<uint64_t>(&data[left + i]), callback);
    }
    for (int j = 0; j < n2; j++) {
        R[j] = data[mid + 1 + j];
        simulateMemoryAccess(reinterpret_cast<uint64_t>(&data[mid + 1 + j]), callback);
    }
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            data[k] = L[i];
            simulateMemoryAccess(reinterpret_cast<uint64_t>(&L[i]), callback);
            i++;
        } else {
            data[k] = R[j];
            simulateMemoryAccess(reinterpret_cast<uint64_t>(&R[j]), callback);
            j++;
        }
        simulateMemoryAccess(reinterpret_cast<uint64_t>(&data[k]), callback);
        k++;
    }
    
    while (i < n1) {
        data[k] = L[i];
        simulateMemoryAccess(reinterpret_cast<uint64_t>(&L[i]), callback);
        simulateMemoryAccess(reinterpret_cast<uint64_t>(&data[k]), callback);
        i++;
        k++;
    }
    
    while (j < n2) {
        data[k] = R[j];
        simulateMemoryAccess(reinterpret_cast<uint64_t>(&R[j]), callback);
        simulateMemoryAccess(reinterpret_cast<uint64_t>(&data[k]), callback);
        j++;
        k++;
    }
}
