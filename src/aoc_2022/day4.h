#ifndef DAY4_H_
#define DAY4_H_

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <regex>
#include <algorithm>
#include <set>

namespace aoc2022day4 {
    struct Pair {
        std::vector<int> section1;
        std::vector<int> section2;
    };
    bool read_input(std::vector<std::string>& out, std::string path_input);
    int solve(const std::string path_input);
    std::vector<Pair> parse_pairs(std::vector<std::string>& input);
    Pair parse_pair(std::string& line);
    int part_one(std::vector<Pair>& pairs);
    int part_two(std::vector<Pair>& pairs);
    bool pair_contains_range(Pair pair);
    bool pair_contains_common(Pair pair);
}


#endif // DAY4_H_
