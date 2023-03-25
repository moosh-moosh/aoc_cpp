#ifndef DAY3_H_
#define DAY3_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_set>
#include <set>
#include <algorithm>

namespace aoc2022day3 {
    bool read_input(std::vector<std::string>& out, std::string path_input);
    int solve(const std::string path_input);
    char get_common_item(std::string rucksack);
    char get_common_among_elves(std::string e1, std::string e2, std::string e3);
    int get_char_score(char c);
    int part_one(std::vector<std::string>& input);
    int part_two(std::vector<std::string>& input);
}

#endif // DAY3_H_
