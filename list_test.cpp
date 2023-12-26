//
// Created by Adminstrator on 2023/12/26.
//
#include <iostream>
#include "list.h"

int main() {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    for (int i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;
    list.pop_back();
    for (int i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;
    list.erase(0);
    for (int i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;
    list.insert(1, 1);
    for (int i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}