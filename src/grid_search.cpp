//
// Created by wolala on 23-12-16.
//
#include "grid_search.h"

GridMap::GridMap(const int width, const int height, const std::vector<Point> &obstacles) : width_(width), height_(height) {
    for (int i = 0; i < width_; ++i) {
        for (int j = 0; j < height_; ++j) {
            if (std::find(obstacles.begin(), obstacles.end(), Point{i, j}) != obstacles.end()) {
                points_[{i, j}] = PointType::kObstacle;
            } else {
                points_[{i, j}] = PointType::kEmpty;
            }
            for (const auto dir: directions_) {
                const int x = i + dir.x;
                const int y = j + dir.y;
                if (x >= 0 && x < width_ && y >= 0 && y < height_ && points_[{x, y}] != PointType::kObstacle && points_[{i, j}] != PointType::kObstacle) {
                    graph_.add_edge(get_index({i, j}, width_), get_index({x, y}, width_), 1);
                }
            }
        }
    }
    for (const auto &obstacle: obstacles) {
        add_obstacle(obstacle);
    }
}

void GridMap::add_obstacle(const Point &point) {
    points_[point] = PointType::kObstacle;
    for (const auto dir: directions_) {
        const int x = point.x + dir.x;
        const int y = point.y + dir.y;
        if (x >= 0 && x < width_ && y >= 0 && y < height_) {
            // std::cout << "remove edge: " << get_index(point, width_) << " " << get_index({x, y}, width_) << std::endl;
            graph_.remove_edge(get_index(point, width_), get_index({x, y}, width_));
        }
    }
}

void GridMap::add_path(const Path &path) {
    if (path.length_ < 2) {
        return;
    }
    for (int i = 1; i < path.length_ - 1; ++i) {
        points_[path.path_points_[i]] = PointType::kPath;
    }
}

void GridMap::add_goal(const Point &point) {
    points_[point] = PointType::kGoal;
}

void GridMap::add_start(const Point &point) {
    points_[point] = PointType::kStart;
}

void GridMap::visualize() {
    std::filesystem::path dot_path = "dot";
    std::filesystem::path png_path = "image";
    std::filesystem::create_directory(dot_path);
    std::filesystem::create_directory(png_path);
    int index = 0;
    for (auto &file: std::filesystem::directory_iterator(dot_path)) {
        index++;
    }
    std::filesystem::path dot_file_path = dot_path / ("grid_map_" + std::to_string(index) + ".dot");
    std::filesystem::path png_file_path = png_path / ("grid_map_" + std::to_string(index) + ".png");
    std::ofstream dot(dot_file_path);
    dot << "graph G {\n";
    dot << "    node [shape=square, fixedsize=true, width=0.6, height=0.6];\n";
    dot << "    edge [style=invis];\n";
    for (int x = 0; x < width_; ++x) {
        for (int y = 0; y < height_; ++y) {
            Point point{x, y};
            auto pointType = points_.find(point);
            if (pointType != points_.end()) {
                dot << "    \"" << x << "," << y << "\" [pos=\"" << y << "," << -x << "!\"";
                if (pointType->second == PointType::kObstacle) {
                    dot << ", style=filled, fillcolor=gray]";
                } else if (pointType->second == PointType::kPath) {
                    dot << ", style=filled, fillcolor=blue]";
                } else if (pointType->second == PointType::kStart) {
                    dot << ", style=filled, fillcolor=green]";
                } else if (pointType->second == PointType::kGoal) {
                    dot << ", style=filled, fillcolor=red]";
                } else {
                    dot << "]";
                }
                dot << ";\n";
            }
        }
    }
    dot << "}\n";
    dot.close();
    std::string command = "neato -Tpng " + dot_file_path.string() + " -o " + png_file_path.string();
    std::system(command.c_str());
// 打开并显示图片，需要多平台适配
#ifdef _WIN32
    command = "start " + png_file_path.string();
#elif __linux__
    command = "xdg-open " + png_file_path.string();
#endif
    std::system(command.c_str());
}

Path AStar::plan(const GridMap &grid_map, const Point &point_start, const Point &point_goal) {
    std::vector<Point> open_set;
    std::vector<Point> close_set;
    std::map<Point, Point> came_from;
    std::map<Point, double> g_score;
    std::map<Point, double> f_score;
    open_set.push_back(point_start);
    g_score[point_start] = 0;
    f_score[point_start] = g_score[point_start] + manhattan_distance(point_goal, point_start);
    while (!open_set.empty()) {
        Point current = open_set[0];
        for (const auto &point: open_set) {
            if (f_score[point] < f_score[current]) {
                current = point;
            }
        }
        if (current == point_goal) {
            Path path;
            path.path_points_.push_back(current);
            while (came_from.find(current) != came_from.end()) {
                current = came_from[current];
                path.path_points_.push_back(current);
            }
            std::reverse(path.path_points_.begin(), path.path_points_.end());
            path.length_ = path.path_points_.size();
            return path;
        }
        open_set.erase(std::remove(open_set.begin(), open_set.end(), current), open_set.end());
        close_set.push_back(current);
        for (const auto &dir: grid_map.directions_) {
            Point neighbor = current + dir;
            if (!grid_map.is_valid(neighbor)) {
                continue;
            }
            if (std::find(close_set.begin(), close_set.end(), neighbor) != close_set.end()) {
                continue;
            }
            double tentative_g_score = g_score[current] + manhattan_distance(neighbor, current);
            if (std::find(open_set.begin(), open_set.end(), neighbor) == open_set.end()) {
                open_set.push_back(neighbor);
            } else if (tentative_g_score >= g_score[neighbor]) {
                continue;
            }
            came_from[neighbor] = current;
            g_score[neighbor] = tentative_g_score;
            f_score[neighbor] = g_score[neighbor] + manhattan_distance(neighbor, current);
        }
    }
    return {};
}
