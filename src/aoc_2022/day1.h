#ifndef DAY1_H_
#define DAY1_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <numeric>

namespace aoc2023day1 {
    bool read_input(std::vector<std::string>& out, std::string path);
    std::vector<int> parse_input(std::vector<std::string> input);
    int part_one(std::vector<int>& elves);
    int part_two(std::vector<int>& elves);
    int solve(std::string path_input);
}

#endif // DAY1_H_
