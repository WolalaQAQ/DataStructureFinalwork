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
    if (path.length() < 2) {
        return;
    }
    for (int i = 0; i < path.length() - 1; ++i) {
        points_[path.path_points_[i]] = PointType::kPath;
    }
}

void GridMap::add_goal(const Point &point) {
    points_[point] = PointType::kGoal;
}

void GridMap::visualize() {
    std::filesystem::path dot_path = "dot";
    std::filesystem::path png_path = "image";
    if (!std::filesystem::exists(dot_path)) {
        std::filesystem::create_directory(dot_path);
    }
    if (!std::filesystem::exists(png_path)) {
        std::filesystem::create_directory(png_path);
    }
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
                    dot << ", style=filled, fillcolor=green]";
                } else if (pointType->second == PointType::kStart) {
                    dot << ", style=filled, fillcolor=blue]";
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

std::vector<Point> JumpPointSearch::jump(GridMap &grid_map, const Point &point, const Point &direction, const Point &goal) {
    std::vector<Point> path;
    Point current = point;
    while (true) {
        current.x += direction.x;
        current.y += direction.y;
        // 检查点是否超出地图范围或是否是障碍物
        if (!grid_map.is_valid(current) || grid_map.points()[current] == PointType::kObstacle) {
            return {};// 空路径表示失败或无法跳跃
        }
        path.push_back(current);// 记录路径
        // 如果当前点是目标点，则返回路径
        if (current == goal) {
            return path;
        }
        // 检查是否存在强制邻居
        if (has_forced_neighbours(grid_map, current, direction)) {
            return path;// 返回到此点的路径
        }
    }
}

std::vector<Point> JumpPointSearch::trace_path(const std::unordered_map<Point, Point> &came_from, const Point &start, const Point &end) {
    std::vector<Point> path;
    Point current = start;

    // 如果当前点不是目标点，则一直向前追溯
    while (current != end) {
        path.push_back(current);
        if (!came_from.count(current)) {
            return {};// 如果当前点没有父节点，则返回空路径
        }
        current = came_from.at(current);
    }

    std::reverse(path.begin(), path.end());
    return path;
}


bool JumpPointSearch::has_forced_neighbours(GridMap &grid_map, const Point &point, const Point &direction) {
    // 只有直线方向上才有强制邻居
    if (direction.x != 0) {
        return (grid_map.is_valid({point.x, point.y + 1}) && grid_map.points()[{point.x, point.y + 1}] == PointType::kObstacle && grid_map.points()[{point.x + direction.x, point.y + 1}] != PointType::kObstacle) ||
               (grid_map.is_valid({point.x, point.y - 1}) && grid_map.points()[{point.x, point.y - 1}] == PointType::kObstacle && grid_map.points()[{point.x + direction.x, point.y - 1}] != PointType::kObstacle);
    } else if (direction.y != 0) {
        return (grid_map.is_valid({point.x + 1, point.y}) && grid_map.points()[{point.x + 1, point.y}] == PointType::kObstacle && grid_map.points()[{point.x + 1, point.y + direction.y}] != PointType::kObstacle) ||
               (grid_map.is_valid({point.x - 1, point.y}) && grid_map.points()[{point.x - 1, point.y}] == PointType::kObstacle && grid_map.points()[{point.x - 1, point.y + direction.y}] != PointType::kObstacle);
    }
    return false;
}


Path JumpPointSearch::Plan(GridMap &grid_map, const Point &start, const Point &goal) {
    struct Node {
        Point point;
        double f_score;
        double g_score;
        Point parent;

        bool operator>(const Node &rhs) const {
            return f_score > rhs.f_score;
        }
    };

    std::priority_queue<Node, std::vector<Node>, std::greater<>> open_set;
    open_set.push({start, 0, 0, start});
    std::unordered_map<Point, double> g_score;
    g_score[start] = 0;
    std::unordered_map<Point, Point> came_from;

    while (!open_set.empty()) {
        Node current = open_set.top();
        open_set.pop();

        if (current.point == goal) {
            return Path(trace_path(came_from, start, goal));
        }

        for (const auto &dir: grid_map.directions_) {
            auto next_path = jump(grid_map, current.point, dir, goal);
            if (!next_path.empty()) {
                Point next_point = next_path.back(); // 最后一个点是跳点
                double tentative_g_score = g_score[current.point] + manhattan_distance(current.point, next_point);
                if (!g_score.count(next_point) || tentative_g_score < g_score[next_point]) {
                    g_score[next_point] = tentative_g_score;
                    double f_score = tentative_g_score + manhattan_distance(next_point, goal);
                    open_set.push({next_point, f_score, tentative_g_score, current.point});
                    // 更新 came_from 为完整路径
                    for (size_t i = 0; i < next_path.size() - 1; ++i) {
                        came_from[next_path[i + 1]] = next_path[i];
                    }
                }
            }
        }
    }
    return {}; // 如果找不到路径，则返回空路径
}
