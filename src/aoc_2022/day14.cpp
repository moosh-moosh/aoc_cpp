#include <iostream>
#include <fstream>
#include <regex>
#include "day14.h"

namespace aoc2022day14 {

    bool read_input(Cave &cave, const std::string path_input) {
        std::ifstream in(path_input);
        std::string line;
        std::regex pattern("(\\d+),(\\d+)");
        std::smatch match;
        int rows = 0;

        if (!in) {
            return false;
        }

        while (std::getline(in, line)) {
            std::vector<Point> rocks;
            while(std::regex_search(line, match, pattern)) {
                int x = std::stoi(match[1]);
                int y = std::stoi(match[2]);
                rocks.push_back(Point(x,y));
                if (y > rows) {
                    rows = y;
                }

                line = match.suffix();
            }
            cave.occupy_spaces(rocks);
            cave.floor = rows;
        }
        in.close();

        return true;
    }

    int part_one(Cave cave) {
        size_t count = 0;
        while (cave.drop_sand().y != static_cast<int>(cave.floor)) {
            count++;
        }

        return count;
    }

    int part_two(Cave cave) {
        cave.infinite = true;
        cave.floor += 2;
        size_t count = 1;
        while (cave.drop_sand().y != 0) {
            count++;
        }
        return count;
    }

    int solve(const std::string path_input) {
        Cave cave;

        if (!read_input(cave, path_input)) {
            std::cout << "failed to read input from " << path_input << std::endl;
            return 1;
        }

        std::cout << "year 2022 day 14" << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout << "part one: " << part_one(cave) << std::endl;
        std::cout << "part two: " << part_two(cave) << std::endl;

        return 0;
    }
}
