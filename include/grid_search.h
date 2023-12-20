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

/**
 * @brief 栅格地图上点的类型
 */
enum class PointType {
    kEmpty = 0,
    kObstacle,
    kStart,
    kGoal,
    kPath,
};

/**
 * @brief 栅格地图上的点
 */
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

/**
 * @brief 计算两点之间的曼哈顿距离
 * @param a 点a
 * @param b 点b
 * @return 曼哈顿距离
 */
inline unsigned int manhattan_distance(const Point& a, const Point &b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

/**
 * @brief Point的hash函数
 */
namespace std {
    template<>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            return hash<int>()(p.x) ^ hash<int>()(p.y);
        }
    };
}

/**
 * @brief 栅格地图上的路径
 */
class Path {
public:
    Path() = default;
    ~Path() = default;

    explicit Path(std::vector<Point>&& path_points) : path_points_(std::move(path_points)), length_(path_points_.size()) {}

    std::vector<Point> path_points_;

    size_t length_ = 0;
};

/**
 * @brief 栅格地图
 */
class GridMap {
public:
    GridMap() = default;
    ~GridMap() = default;

    /**
     * @brief 构造函数
     * @param width 地图宽度
     * @param height 地图高度
     * @param obstacles 障碍物
     */
    GridMap(int width, int height, const std::vector<Point>& obstacles = {});

    /**
     * @brief 添加障碍物
     * @param point 障碍物坐标
     */
    void add_obstacle(const Point& point);

    /**
     * @brief 添加路径
     * @param path 路径
     */
    void add_path(const Path& path);

    /**
     * @brief 添加目标点
     * @param point 目标点坐标
     */
    void add_goal(const Point& point);

    /**
     * @brief 添加起始点
     * @param point 起始点坐标
     */
    void add_start(const Point& point);

    /**
     * @brief 可视化
     */
    void visualize();

    /**
     * @brief 获取点的索引
     * @param point 点
     * @param width 地图宽度
     * @return 索引
     */
    static int get_index(const Point& point, const int width) {
        return point.x * width + point.y;
    }

    /**
     * @brief 检查某个点是否在地图内
     * @param index 索引
     * @param width 地图宽度
     * @return 坐标
     */
    [[nodiscard]] bool is_valid(const Point& point) const {
        return point.x >= 0 && point.x < width_ && point.y >= 0 && point.y < height_;
    }

    // 可以行进的4个方向
    const std::vector<Point> directions_ = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    std::map<Point, PointType> points() {
        return points_;
    };
private:
    // 栅格地图对应的图
    Graph graph_;
    // 栅格地图上的点
    std::map<Point, PointType> points_;

    int width_ = 0;
    int height_ = 0;
};

/**
 * @brief A*算法
 */
class AStar {
public:
    /**
     * @brief A*算法
     * @param grid_map 栅格地图
     * @param point_start 起始点
     * @param point_goal 目标点
     * @return 路径
     */
    static Path plan(const GridMap& grid_map, const Point& point_start, const Point& point_goal);

};

#endif//GRID_SEARCH_H
