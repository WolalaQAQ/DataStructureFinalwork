#include "graph.h"
#include "mst.h"
#include <random>

int main() {
    // 1. 从dot文件中读取图
    // const std::filesystem::path file_path("neu_graph.dot");
    // Graph graph_from_file(file_path);
    // graph_from_file.visualize();
    // Graph mst_from_file = KruskalMST(graph_from_file);
    // mst_from_file.visualize();
    // 2. 从用户输入中读取图
    // Graph graph_from_input;
    // int v_in, w_in;
    // double weight_in;
    // while (std::cin >> v_in >> w_in >> weight_in) {
    //     graph_from_input.add_edge(v_in, w_in, weight_in);
    // }
    // graph_from_input.visualize();
    // Graph mst_from_input = KruskalMST(graph_from_input);
    // mst_from_input.visualize();
    // 3. 从随机生成的图中读取图
    Graph graph_from_random;
    constexpr int vertex_num = 10;
    constexpr int edge_num = 20;
    std::random_device rd;
    std::mt19937 gen(rd());

    // 定义均匀分布
    std::uniform_int_distribution<> vertices_dis(0, vertex_num - 1);
    std::uniform_real_distribution<> weight_dis(1.0, 10.0);

    // 生成随机边
    for (int i = 0; i < edge_num; ++i) {
        int v_random, w_random;
        do {
            v_random = vertices_dis(gen);
            w_random = vertices_dis(gen);
        } while (v_random == w_random);
        double weight = weight_dis(gen);

        graph_from_random.add_edge(v_random, w_random, weight);
    }
    graph_from_random.visualize();
    Graph mst_from_random = KruskalMST(graph_from_random);
    mst_from_random.visualize();
    return 0;
}
