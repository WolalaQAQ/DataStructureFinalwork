#include "graph.h"
#include "mst.h"

int main() {
    const std::filesystem::path file_path("neu_graph.dot");
    Graph graph(file_path);
    graph.visualize();
    Graph mst = KruskalMST(graph);
    mst.visualize();
    return 0;
}
