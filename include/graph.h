//
// Created by wolala on 23-12-8.
//

#ifndef DATASTRUCTUREFINALWORK_GRAPH_H
#define DATASTRUCTUREFINALWORK_GRAPH_H

#include <exception>
#include <filesystem>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "list.h"

/**
 * @brief 图中的节点
 */
class GraphNode {
public:
    GraphNode() = default;
    GraphNode(int id, double weight) : id_(id), weight_(weight) {}
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

    explicit Graph(int size) : adj_list(size) {}

    /**
     * @brief 从dot文件中读取图
     * @param path dot文件路径
     */
     explicit Graph(std::filesystem::path& file_path);

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
    int size();

    List< List<GraphNode> > adj_list;

private:

};


#endif //DATASTRUCTUREFINALWORK_GRAPH_H
