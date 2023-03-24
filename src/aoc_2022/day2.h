#ifndef DAY2_H_
#define DAY2_H_

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>

namespace aoc2022day2 {
    bool read_input(std::vector<std::string>& out, std::string path_input);
    int part_one(std::vector<std::string>& input);
    int part_two(std::vector<std::string>& input);
    int solve(std::string path_input);
}


#endif // DAY2_H_
