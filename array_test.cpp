//
// Created by Adminstrator on 2023/12/26.
//
#include <iostream>
#include "dynamic_array.h"
#include "disjoint_sets.h"

int main() {
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    array.push_back(4);
    array.push_back(5);
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    array.pop_back();
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    array.erase(2);
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    array.insert(2, 3);
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    DisjointSets disjoint_sets(5);
    disjoint_sets.unite(0, 1);
    disjoint_sets.unite(1, 2);
    disjoint_sets.unite(3, 4);
    std::cout << disjoint_sets.find(0) << std::endl;
    std::cout << disjoint_sets.find(1) << std::endl;
    std::cout << disjoint_sets.find(2) << std::endl;
    std::cout << disjoint_sets.find(3) << std::endl;
    std::cout << disjoint_sets.find(4) << std::endl;
    return 0;
}