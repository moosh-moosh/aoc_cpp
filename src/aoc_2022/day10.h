#ifndef DAY10_H_
#define DAY10_H_

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <stdexcept>
#include <numeric>

namespace aoc2022day10 {

    struct Operation {
        int num_cycles;
        int x;
    };

    int solve(const std::string path_input);
    bool read_input(std::vector<Operation>& out, const std::string path_input);
    std::vector<int> run_ops(std::vector<Operation>& ops);
    int calculate_signal_strength(std::vector<int>& stream, int cycle);
    bool draw_pixel(std::vector<int>& stream, int pos, int cycle);
    int part_one(std::vector<int>& stream);
    void part_two(std::vector<int>& stream);
}

#endif // DAY10_H_
