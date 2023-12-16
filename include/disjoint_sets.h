//
// Created by wolala on 23-12-8.
//

#ifndef DATASTRUCTUREFINALWORK_DISJOINT_SETS_H
#define DATASTRUCTUREFINALWORK_DISJOINT_SETS_H

#include "dynamic_array.h"

/**
 * @brief 并查集
 */
class DisjointSets {
public:
    DisjointSets() = default;
    explicit DisjointSets(int size);

    /**
     * @brief 查找元素所在集合的代表元素
     * @param x 元素
     * @return 代表元素
     */
    int find(int x);

    /**
     * @brief 合并两个集合
     * @param x 集合1
     * @param y 集合2
     */
    void unite(int x, int y);

private:
    DynamicArray<int> parent_;
    DynamicArray<int> rank_;

};
#endif//DATASTRUCTUREFINALWORK_DISJOINT_SETS_H
