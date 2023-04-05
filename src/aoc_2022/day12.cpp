#include <iostream>
#include <fstream>
#include <queue>
#include "day12.h"

namespace aoc2022day12 {
    static Area start = Area{0, 0, 0};
    static Area end = Area{0, 0, 0};

    bool read_input(std::vector<std::vector<Area>> &height_map, const std::string path_input) {
        std::ifstream in(path_input);
        std::string line;

        if (!in) {
            return false;
        }

        int r = 0, c = 0;

        while (std::getline(in, line)) {
            std::vector<Area> row;

            for (char ch : line) {
                row.push_back(Area(ch, r, c));
                switch (ch) {
                    case 'S': {
                        start = Area(ch, r, c);
                    } break;
                    case 'E': {
                        end = Area(ch, r, c);
                    } break;
                }
                c++;
            }
            c = 0;
            height_map.push_back(row);
            r++;
        }
        in.close();

        return true;
    }

    std::vector<Area> get_valid_nbors(std::vector<std::vector<Area>> &height_map, Area a, bool reverse) {
        std::vector<Area> nbors = { Area{0, a.row, a.col+1},
                                    Area{0, a.row, a.col-1},
                                    Area{0, a.row-1, a.col},
                                    Area{0, a.row+1, a.col} };

        std::vector<Area> valid_nbors;

        for (const Area& ar : nbors) {
            if (ar.row >= 0 &&
                ar.row < (int)height_map.size() &&
                ar.col >= 0 &&
                ar.col <= (int)height_map[0].size()) {

                const Area n = height_map[ar.row][ar.col];

                if (!reverse && n.elevation <= a.elevation+1) {
                    valid_nbors.push_back(height_map[ar.row][ar.col]);
                } else if (reverse && n.elevation >= a.elevation - 1) {
                    valid_nbors.push_back(height_map[ar.row][ar.col]);
                }
            }
        }

        return valid_nbors;
    }

    int bfs(std::vector<std::vector<Area>> height_map, Area start, Area end, bool reverse) {
        std::queue<Area> q;
        q.push(start);
        height_map[start.row][start.col].visited = true;
        Area cur;
        while (!q.empty()) {
            cur = q.front();
            if (!reverse && cur.row == end.row && cur.col == end.col) {
                return cur.distance;
            } else if (reverse && cur.elevation == (int)'a') {
                return cur.distance;
            }
            q.pop();
            std::vector<Area> nbors = get_valid_nbors(height_map, cur, reverse);
            for (Area &n : nbors) {
                Area &a = height_map[n.row][n.col];
                if (a.visited) {
                    continue;
                }
                a.visited = true;
                a.distance = cur.distance + 1;
                q.push(a);
            }
        }
        return -1;
    }

    int part_one(std::vector<std::vector<Area>> &height_map) {
        return bfs(height_map, start, end, false);
    }

    int part_two(std::vector<std::vector<Area>> &height_map) {
        return bfs(height_map, end, end, true);
    }


    int solve(const std::string path_input) {
        std::vector<std::vector<Area>> height_map;

        if (!read_input(height_map, path_input)) {
            std::cout << "failed to read input from " << path_input << std::endl;
            return 1;
        }

        std::cout << "year 2022, day 12" << std::endl;
        std::cout << "-----------------" << std::endl;
        std::cout << "part one: " << part_one(height_map) << std::endl;
        std::cout << "part two: " << part_two(height_map) << std::endl;

        return 0;
    }
}
