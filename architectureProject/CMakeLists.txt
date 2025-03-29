cmake_minimum_required(VERSION 3.5)
project(CacheSortAnalysis)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(cache_sort_analysis
    src/main.cpp
    src/CacheSimulator.cpp
    src/SortAlgorithms.cpp
    src/MemoryAnalyzer.cpp
)