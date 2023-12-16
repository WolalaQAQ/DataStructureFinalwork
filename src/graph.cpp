//
// Created by wolala on 23-12-8.
//
#include "graph.h"

Graph::Graph(const std::filesystem::path& file_path) {
    std::ifstream dot(file_path);
    std::string line;
    while (std::getline(dot, line)) {
        if (line.find("--") != std::string::npos) {
            int v = std::stoi(line.substr(0, line.find("--")));
            int w = std::stoi(line.substr(line.find("--") + 2, line.find('[') - line.find("--") - 3));
            double weight = std::stod(line.substr(line.find('=') + 2, line.find(']') - line.find('=') - 2));
            add_edge(v, w, weight);
        }
    }
    dot.close();
}

void Graph::add_edge(const int v, const int w, const double weight) {
    if (v >= size() || w >= size()) {
        adj_list.resize(std::max(v, w) + 1);
    }
    if (v == w) {
        throw std::invalid_argument("Self loop is not allowed");
    }
    adj_list[v].push_back(GraphNode(w, weight));
    adj_list[w].push_back(GraphNode(v, weight));
}

void Graph::remove_edge(const int v, const int w) {
    if (v >= size() || w >= size()) {
        throw std::out_of_range("Vertex out of range");
    }
    for (int i = 0; i < adj_list[v].size(); i++) {
        if (adj_list[v][i].id_ == w) {
            adj_list[v].erase(i);
            break;
        }
    }
    for (int i = 0; i < adj_list[w].size(); i++) {
        if (adj_list[w][i].id_ == v) {
            adj_list[w].erase(i);
            break;
        }
    }
}

void Graph::visualize() {
    std::filesystem::path dot_path = "dot";
    std::filesystem::path png_path = "image";
    if (!std::filesystem::exists(dot_path)) {
        std::filesystem::create_directory(dot_path);
    }
    if (!std::filesystem::exists(png_path)) {
        std::filesystem::create_directory(png_path);
    }
    int index = 0;
    for (auto &file : std::filesystem::directory_iterator(dot_path)) {
        index++;
    }
    std::string dot_file = dot_path.string() + "/" + "graph_" + std::to_string(index) + ".dot";
    std::string png_file = png_path.string() + "/" + "graph_" + std::to_string(index) + ".png";
    std::ofstream dot(dot_file);
    dot << "graph G {" << std::endl;
    for (int i = 0; i < size(); i++) {
        for (int j = 0; j < adj_list[i].size(); j++) {
            if (i < adj_list[i][j].id_) {
                dot << "    " << i << " -- " << adj_list[i][j].id_ << " [label=\"" << adj_list[i][j].weight_ << "\"];" << std::endl;
            }
        }
    }
    dot << "}" << std::endl;
    dot.close();
    std::string command = "dot -Tpng " + dot_file + " -o " + png_file;
    system(command.c_str());
    // 打开并显示图片，需要多平台适配
    #ifdef _WIN32
        command = "start " + png_file;
    #elif __linux__
        command = "xdg-open " + png_file;
    #endif
    system(command.c_str());
}

size_t Graph::size() {
    return adj_list.size();
}