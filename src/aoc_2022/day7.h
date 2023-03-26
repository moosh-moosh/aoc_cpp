#ifndef DAY7_H_
#define DAY7_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include <map>

namespace aoc2022day7 {
    enum class LineType { CMD, FILE, IGNORE };
    struct Action {
        LineType line_type;
        std::string data;
    };
    const std::string ROOT = "/";
    int solve(const std::string path_input);
    bool read_input(std::vector<std::string>& out, std::string path_input);
    std::vector<std::string> cmd_cd(std::vector<std::string> path, std::string cmd_path);
    std::map<std::string, int> read_file(std::map<std::string, int> dirs, std::vector<std::string> path, int sz);
    std::string get_path_str(std::vector<std::string> path);
    std::map<std::string, int> process_input(std::map<std::string, int> dirs, std::vector<std::string> path, std::vector<std::string>& input);
    Action parse_line(std::string line);
    int part_one(std::map<std::string, int>& dirs);
}


#endif // DAY7_H_
