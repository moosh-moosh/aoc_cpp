#ifndef DAY14_H_
#define DAY14_H_

#include <string>
#include <vector>
#include <unordered_map>

namespace aoc2022day14 {
    struct Point {
        int x,y;
        std::string key;
        Point(int x_, int y_):x{x_}, y{y_} {
            key = std::to_string(x) + "," + std::to_string(y);
        };
    };

    struct Cave  {
        Point entry_point = Point(500, 0);
        int floor;
        bool infinite = false;
        std::unordered_map<std::string, int> occupied_spaces;

        void occupy_spaces(std::vector<Point> points) {
            for (size_t i = 0; i < points.size(); i++) {
                Point cur = points[i];
                occupy_space(cur);
                if (i > 0) {
                    Point prev = points[i-1];
                    if (prev.x < cur.x) {
                        for (int j = prev.x+1; j < cur.x; j++) {
                            occupy_space(Point(j, cur.y));
                        }
                    } else if (prev.x > cur.x) {
                        for (int j = cur.x+1; j < prev.x; j++) {
                            occupy_space(Point(j, cur.y));
                        }
                    }
                    if (prev.y < cur.y) {
                        for (int j = prev.y+1; j < cur.y; j++) {
                            occupy_space(Point(cur.x, j));
                        }
                    } else if (prev.y > cur.y) {
                        for (int j = cur.y+1; j < prev.y; j++) {
                            occupy_space(Point(cur.x, j));
                        }
                    }
                }
            }
        }

        void occupy_space(Point p) {
            occupied_spaces[p.key] = 1;
        }

        bool is_at_rest(Point p) {
            if (infinite && p.y == floor-1) {
                return true;
            }
            return is_occupied(Point(p.x, p.y+1)) &&
                   is_occupied(Point(p.x-1, p.y+1)) &&
                   is_occupied(Point(p.x+1, p.y+1));
        }

        bool is_occupied(Point p) {
            return occupied_spaces.count(p.key) > 0;
        }

        Point drop_sand() {
            Point sand = entry_point;
            while (!is_at_rest(sand)) {
                sand = Point(sand.x, sand.y+1);

                if (sand.y >= floor) {
                    break;
                }

                if (!is_occupied(sand)) {
                    continue;
                }

                if (!is_occupied(Point(sand.x-1, sand.y))) {
                    sand = Point(sand.x-1, sand.y);
                    continue;
                }
                if (!is_occupied(Point(sand.x+1, sand.y))) {
                    sand = Point(sand.x+1, sand.y);
                    continue;
                }
            }
            occupy_space(sand);

            return sand;
        }
    };

    bool read_input(Cave &cave, const std::string path_input);
    int solve(const std::string path_input);
    int part_one(Cave cave);
    int part_two(Cave cave);
}

#endif // DAY14_H_
