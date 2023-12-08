#include <iostream>

#include "graph.h"

int main() {
    std::filesystem::path file_path("/home/wolala/Documents/DataStructurePractice/DataStructureFinalwork/neu_graph.dot");
    Graph graph(file_path);
    graph.visualize();
    return 0;
}
