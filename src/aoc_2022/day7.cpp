#include "day7.h"

namespace aoc2022day7 {
    bool read_input(std::vector<std::string>& out, std::string path_input) {
        std::ifstream in(path_input);
        std::string line;

        if (!in) {
            return false;
        }

        while (std::getline(in, line)) {
            out.push_back(line);
        }
        in.close();

        return true;
    }

    std::vector<std::string> cmd_cd(std::vector<std::string> path, std::string cmd_path) {
        if (cmd_path == ROOT) {
            path.clear();
        } else if (cmd_path == "..") {
            path.pop_back();
        } else {
            path.push_back(cmd_path);
        }

        return path;
    }

    void process_file(std::map<std::string, int>& dirs, std::vector<std::string> path, int sz) {
        const std::string PWD = get_path_str(path);
        dirs[PWD] += sz;
        while (path.size() > 0) {
            path.pop_back();
            dirs[get_path_str(path)] += sz;
        }
    }

    std::string get_path_str(std::vector<std::string> path) {
        std::stringstream ss;
        ss << ROOT;
        for (std::string s : path) {
            ss << s;
        }

        return ss.str();
    }

    std::map<std::string, int> process_input(std::vector<std::string>& input) {
        std::map<std::string, int> dirs;
        std::vector<std::string> path;

        for (std::string line : input) {
            Action a = parse_line(line);
            switch (a.line_type) {
                case LineType::CMD: {
                    path = cmd_cd(path, a.data);
                } break;
                case LineType::FILE: {
                    process_file(dirs, path, std::stoi(a.data));
                } break;
                case LineType::IGNORE: {
                    continue;
                } break;
            }
        }

        return dirs;
    }

    Action parse_line(std::string line) {
        std::regex file_regex("^(\\d+)\\s");
        std::regex cmd_regex("^\\$ cd (.*)");
        std::smatch match;
        Action action;

        if (std::regex_search(line, match, cmd_regex)) {
            action.line_type = LineType::CMD;
            action.data = match[1];
        } else if (std::regex_search(line, match, file_regex)) {
            action.line_type = LineType::FILE;
            action.data = match[1];
        } else {
            action.line_type = LineType::IGNORE;
            action.data = "";
        }

        return action;
    }

    int get_space_to_free(int space_used) {
        const int SPACE_AVAILABLE = TOTAL_DISK - space_used;
        const int SPACE_TO_FREE = SPACE_REQUIRED - SPACE_AVAILABLE;
        return SPACE_TO_FREE;
    }

    int part_one(const std::map<std::string, int>& dirs) {
        int answer = 0;
        for (auto const& kv : dirs) {
            if (kv.first == ROOT) {
                continue;
            }
            if (kv.second <= 100000) {
                answer += kv.second;
            }
        }

        return answer;
    }

    int part_two(const std::map<std::string, int>& dirs) {
        const int SPACE_TO_FREE = get_space_to_free(dirs.at(ROOT));
        int smallest_dir = 0;
        for (auto const& kv : dirs) {
            if (kv.second >= SPACE_TO_FREE) {
                if (smallest_dir > 0 && kv.second > smallest_dir) {
                    continue;
                }
                smallest_dir = kv.second;
            }
        }
        return smallest_dir;
    }

    int solve(const std::string path_input) {
        std::vector<std::string> input;

        if (!read_input(input, path_input)) {
            std::cout << "error reading input from " << path_input << std::endl;
            return 1;
        }

        const std::map<std::string, int> DIRS = process_input(input);

        std::cout << "year 2022 day 7" << std::endl;
        std::cout << "---------------" << std::endl;

        std::cout << "part one: " << part_one(DIRS) << std::endl;
        std::cout << "part two: " << part_two(DIRS) << std::endl;

        return 0;
    }
}
