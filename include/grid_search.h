//
// Created by wolala on 23-12-16.
//

#ifndef GRID_SEARCH_H
#define GRID_SEARCH_H

#include "graph.h"

#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <vector>
#include <unordered_map>

enum class PointType {
    kEmpty = 0,
    kObstacle,
    kStart,
    kGoal,
    kPath,
};

class Point {
public:
    Point() = default;
    Point(const int x, const int y) : x(x), y(y) {}
    ~Point() = default;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Point& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }

    Point operator+(const Point& other) const {
        return Point{x + other.x, y + other.y};
    }

    Point operator-(const Point& other) const {
        return Point{x - other.x, y - other.y};
    }

    int x = 0;
    int y = 0;
};

inline unsigned int manhattan_distance(const Point& a, const Point& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

namespace std {
    template<>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            return hash<int>()(p.x) ^ hash<int>()(p.y);
        }
    };
}

class Path {
public:
    Path() = default;
    ~Path() = default;

    explicit Path(std::vector<Point>&& path_points) : path_points_(std::move(path_points)), length_(path_points_.size()) {}

    std::vector<Point> path_points_;

    size_t length_ = 0;
};

class GridMap {
public:
    GridMap() = default;
    ~GridMap() = default;

    GridMap(int width, int height, const std::vector<Point>& obstacles = {});

    void add_obstacle(const Point& point);

    void add_path(const Path& path);

    void add_goal(const Point& point);

    void add_start(const Point& point);

    void visualize();

    static int get_index(const Point& point, const int width) {
        return point.x * width + point.y;
    }

    [[nodiscard]] bool is_valid(const Point& point) const {
        return point.x >= 0 && point.x < width_ && point.y >= 0 && point.y < height_;
    }

    const std::vector<Point> directions_ = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    std::map<Point, PointType> points() {
        return points_;
    };
private:


    Graph graph_;
    std::map<Point, PointType> points_;

    int width_ = 0;
    int height_ = 0;
};

class AStar {
public:
    static Path plan(GridMap& grid_map, const Point& point_start, const Point& point_goal);

private:

};

#endif//GRID_SEARCH_H
