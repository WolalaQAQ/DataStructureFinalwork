//
// Created by wolala on 23-12-8.
//

#ifndef DATASTRUCTUREFINALWORK_GRAPH_H
#define DATASTRUCTUREFINALWORK_GRAPH_H

#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "dynamic_array.h"
#include "list.h"

/**
 * @brief 图中的节点
 */
class GraphNode {
public:
    GraphNode() = default;
    GraphNode(const int id, const double weight) : id_(id), weight_(weight) {}
    ~GraphNode() = default;

    int id_ = 0;
    double weight_ = 0;
};

/**
 * @brief 基于邻接表的有权无向图
 */
class Graph {
public:
    Graph() = default;
    ~Graph() = default;

    // 禁用复制构造函数和复制赋值运算符
    Graph(const Graph &) = delete;
    Graph &operator=(const Graph &) = delete;

    // 移动构造函数
    Graph(Graph &&other) noexcept : adj_list(std::move(other.adj_list)) {}

    // 移动赋值运算符
    Graph &operator=(Graph &&other) noexcept {
        if (this != &other) {
            adj_list = std::move(other.adj_list);
        }
        return *this;
    }

    /**
     * @brief 从dot文件中读取图
     * @param file_path dot文件路径
     */
    explicit Graph(const std::filesystem::path &file_path);

    /**
     * @brief 添加一条边
     * @param v 起点
     * @param w 终点
     * @param weight 权重
     */
    void add_edge(int v, int w, double weight);

    /**
     * @brief 删除一条边
     * @param v 起点
     * @param w 终点
     */
    void remove_edge(int v, int w);

    /**
     * @brief 使用Graphviz可视化图
     * @note 需要安装Graphviz
     */
    void visualize();

    /**
     * @brief 获取图的大小
     * @return 图的大小
     */
    size_t size();

    List<List<GraphNode>> adj_list;
};

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

#endif //DATASTRUCTUREFINALWORK_GRAPH_H
