#ifndef DAY6_H_
#define DAY6_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

namespace aoc2022day6 {
    int solve(const std::string path_input);
    bool read_input(std::vector<std::string>& out, std::string path_input);
    int find_start_of_packet(std::string stream, int marker);
    int part_one(std::vector<std::string> input);
    int part_two(std::vector<std::string> input);
}

#endif // DAY6_H_
