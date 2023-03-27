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
    const int TOTAL_DISK = 70000000;
    const int SPACE_REQUIRED = 30000000;

    int solve(const std::string path_input);
    bool read_input(std::vector<std::string>& out, std::string path_input);
    std::vector<std::string> cmd_cd(std::vector<std::string> path, std::string cmd_path);
    void process_file(std::map<std::string, int>& dirs, std::vector<std::string> path, int sz);
    std::string get_path_str(std::vector<std::string> path);
    std::map<std::string, int> process_input(std::vector<std::string>& input);
    Action parse_line(std::string line);
    int part_one(const std::map<std::string, int>& dirs);
    int part_two(const std::map<std::string, int>& dirs);
    int get_space_to_free(int space_used);
}


#endif // DAY7_H_
