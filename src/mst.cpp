//
// Created by wolala on 23-12-8.
//
#include "mst.h"

Edges::Edges(Graph &graph) {
    for (int i = 0; i < graph.adj_list.size(); i++) {
        for (int j = 0; j < graph.adj_list[i].size(); j++) {
            if (i < graph.adj_list[i][j].id_) {
                push_back(Edge(i, graph.adj_list[i][j].id_, graph.adj_list[i][j].weight_));
            }
        }
    }
}

Graph KruskalMST(Graph &graph) {
    // 首先将图转化为边集的表示方式
    Edges edges(graph);
    edges.heap_sort(0, edges.size() - 1, [](const Edge &a, const Edge &b) { return a.weight_ < b.weight_; });

    DisjointSets disjoint_sets(graph.adj_list.size());
    Graph mst(graph.adj_list.size());

    for (int i = 0; i < edges.size(); i++) {
        if (disjoint_sets.find(edges[i].v_) != disjoint_sets.find(edges[i].w_)) {
            disjoint_sets.unite(edges[i].v_, edges[i].w_);
            mst.add_edge(edges[i].v_, edges[i].w_, edges[i].weight_);
        }
    }

    return mst;
}