#include "grid_search.h"
#include <random>

int main() {
    constexpr unsigned int width = 10;
    constexpr unsigned int height = 10;
    constexpr unsigned int residents_num = 10;
    constexpr unsigned int obstacles_num = 50;

    GridMap grid_map(width, height);
    // Generate random residents and obstacles
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> x_dis(0, width - 1);
    std::uniform_int_distribution<> y_dis(0, height - 1);
    std::vector<Point> residents;
    std::vector<Point> obstacles;
    for (int i = 0; i < residents_num; ++i) {
        Point resident{x_dis(gen), y_dis(gen)};
        if (std::find(residents.begin(), residents.end(), resident) == residents.end()) {
            residents.push_back(resident);
            grid_map.add_goal(resident);
            std::cout << "Resident " << resident.x << " " << resident.y << std::endl;
        } else {
            i--;
        }
    }
    for (int i = 0; i < obstacles_num; ++i) {
        Point obstacle{x_dis(gen), y_dis(gen)};
        if (std::find(residents.begin(), residents.end(), obstacle) == residents.end() && std::find(obstacles.begin(), obstacles.end(), obstacle) == obstacles.end()) {
            obstacles.push_back(obstacle);
            grid_map.add_obstacle(obstacle);
            std::cout << "Obstacle " << obstacle.x << " " << obstacle.y << std::endl;
        } else {
            i--;
        }
    }

    // Search!
    std::vector<Path> shortest_paths;
    unsigned int shortest_length = std::numeric_limits<unsigned int>::max();
    Point best_location;

    auto tic = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; j++) {
            std::cout << "Searching " << i << " " << j << std::endl;
            if (std::find(residents.begin(), residents.end(), Point{i, j}) != residents.end() || std::find(obstacles.begin(), obstacles.end(), Point{i, j}) != obstacles.end()) {
                std::cout << "Skip " << i << " " << j << std::endl;
                continue;
            }
            std::vector<Path> paths;
            unsigned int lengths = 0;
            bool stop_flag = false;
            for (const auto &resident: residents) {
                Path path = AStar::plan(grid_map, Point{i, j}, resident);
                if (path.length_ == 0) {
                    stop_flag = true;
                    break;
                }
                paths.push_back(path);
                lengths += path.length_;
            }
            if (stop_flag) {
                continue;
            } else if (lengths < shortest_length) {
                shortest_paths = paths;
                shortest_length = lengths;
                best_location = Point{i, j};
            }
        }
    }
    auto toc = std::chrono::high_resolution_clock::now();
    std::cout << "耗时: " << std::chrono::duration_cast<std::chrono::milliseconds>(toc - tic).count() << " ms" << std::endl;

    // Visualize
    if (shortest_paths.empty()) {
        std::cout << "No path found" << std::endl;
    } else {
        for (const auto &path: shortest_paths) {
            grid_map.add_path(path);
        }
        grid_map.add_start(best_location);
        std::cout << "Best location: " << best_location.x << " " << best_location.y << std::endl;
    }
    grid_map.visualize();

    return 0;
}