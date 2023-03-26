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

    std::map<std::string, int> read_file(std::map<std::string, int> dirs, std::vector<std::string> path, int sz) {
        const std::string PWD = get_path_str(path);
        dirs[PWD] += sz;
        while (path.size() > 0) {
            path.pop_back();
            dirs[get_path_str(path)] += sz;
        }
        return dirs;
    }

    std::string get_path_str(std::vector<std::string> path) {
        std::stringstream ss;
        ss << ROOT;
        for (std::string s : path) {
            ss << s;
        }

        return ss.str();
    }

    std::map<std::string, int> process_input(std::map<std::string, int> dirs, std::vector<std::string> path, std::vector<std::string>& input) {
        for (std::string line : input) {
            Action a = parse_line(line);
            switch (a.line_type) {
                case LineType::CMD: {
                    path = cmd_cd(path, a.data);
                } break;
                case LineType::FILE: {
                    dirs = read_file(dirs, path, std::stoi(a.data));
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

    int part_one(std::map<std::string, int>& dirs) {
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

    int solve(const std::string path_input) {
        std::vector<std::string> input;

        if (!read_input(input, path_input)) {
            std::cout << "error reading input from " << path_input << std::endl;
            return 1;
        }

        std::map<std::string, int> dirs;
        std::vector<std::string> path;

        dirs = process_input(dirs, path, input);

        std::cout << "year 2022 day 7" << std::endl;
        std::cout << "---------------" << std::endl;

        std::cout << "part one: " << part_one(dirs) << std::endl;

        return 0;
    }
}
