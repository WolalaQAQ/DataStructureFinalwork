//
// Created by wolala on 23-12-8.
//
#include "disjoint_sets.h"

DisjointSets::DisjointSets(int size) : parent_(size), rank_(size) {
    for (int i = 0; i < size; i++) {
        parent_[i] = i;
        rank_[i] = 0;
    }
}

int DisjointSets::find(int x) {
    if (parent_[x] != x) {
        parent_[x] = find(parent_[x]);
    }
    return parent_[x];
}

void DisjointSets::unite(int x, int y) {
    int x_root = find(x);
    int y_root = find(y);
    if (x_root == y_root) {
        return;
    }
    if (rank_[x_root] < rank_[y_root]) {
        parent_[x_root] = y_root;
    } else if (rank_[x_root] > rank_[y_root]) {
        parent_[y_root] = x_root;
    } else {
        parent_[y_root] = x_root;
        rank_[x_root]++;
    }
}