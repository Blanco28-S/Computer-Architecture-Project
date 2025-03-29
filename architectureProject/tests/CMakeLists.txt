add_executable(test_cache test_cache.cpp ../src/CacheSimulator.cpp)
target_include_directories(test_cache PRIVATE ../include)

add_executable(test_sort test_sort.cpp ../src/SortAlgorithms.cpp)
target_include_directories(test_sort PRIVATE ../include)

add_test(NAME TestCache COMMAND test_cache)
add_test(NAME TestSort COMMAND test_sort)