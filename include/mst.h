//
// Created by wolala on 23-12-8.
//

#ifndef DATASTRUCTUREFINALWORK_MST_H
#define DATASTRUCTUREFINALWORK_MST_H

#include "graph.h"
#include "disjoint_sets.h"
#include "dynamic_array.h"

/**
 * @brief 图中的边
 */
class Edge {
public:
    Edge() = default;
    Edge(const int v, const int w, const double weight) : v_(v), w_(w), weight_(weight) {}
    ~Edge() = default;

    int v_ = 0;
    int w_ = 0;
    double weight_ = 0;
};

class Edges : public DynamicArray<Edge> {
public:
    Edges() = default;

    /**
     * @brief 从图中构造边集
     * @param graph 图
     */
    explicit Edges(Graph& graph);

};

/**
 * @brief Kruskal算法求最小生成树
 * @param graph 原图
 * @return 最小生成树
 */
Graph KruskalMST(Graph& graph);

#endif//DATASTRUCTUREFINALWORK_MST_H
