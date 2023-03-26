#include "day6.h"

namespace aoc2022day6 {

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

    int find_start_of_packet(std::string stream, int marker) {
        std::string seq;
        for (size_t i = 0; i < stream.length(); i++) {
            seq = stream.substr(i, marker);
            std::unordered_set<char> seq_set(seq.begin(), seq.end());
            if (seq_set.size() == seq.length()) {
                return marker + i;
            }
        }

        return 0;
    }

    int part_one(std::vector<std::string> input) {
        return find_start_of_packet(input[0], 4);
    }

    int part_two(std::vector<std::string> input) {
        return find_start_of_packet(input[0], 14);
    }

    int solve(std::string path_input) {
        std::vector<std::string> input;

        if (!read_input(input, path_input)) {
            std::cout << "error reading input from " << path_input << std::endl;
            return 1;
        }

        std::cout << "year 2022 day 6" << std::endl;
        std::cout << "---------------" << std::endl;

        std::cout << "part one: " << part_one(input) << std::endl;
        std::cout << "part two: " << part_two(input) << std::endl;

        return 0;
    }

}
