#ifndef DAY12_H_
#define DAY12_H_

#include <string>
#include <vector>

namespace aoc2022day12 {
    struct Area {
        int elevation;
        int row;
        int col;
        int distance;
        bool visited;
        Area() {
            elevation = 0;
            row = 0;
            col = 0;
            distance = 0;
            visited = false;
        }
        Area(char c, int row_, int col_) {
            row = row_;
            col = col_;
            visited = false;
            distance = 0;
            switch (c) {
                case 'S': {
                    elevation = (int)'a';
                } break;
                case 'E': {
                    elevation = (int)'z';
                } break;
                default: {
                    elevation = (int)c;
                }
            }
        }
    };

    int solve(const std::string path_input);
    int part_one(std::vector<std::vector<Area>> &height_map);
    bool read_input(std::vector<std::vector<Area>> &height_map, const std::string path_input);
    std::vector<Area> get_valid_nbors(std::vector<std::vector<Area>> &height_map, Area a);
    int bfs(std::vector<std::vector<Area>> height_map, Area start, Area end);
}


#endif // DAY12_H_
