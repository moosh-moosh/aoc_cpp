#include "day6.h"

bool aoc2022day6::read_input(std::vector<std::string>& out, std::string path_input) {
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

int aoc2022day6::find_start_of_packet(std::string stream, int marker) {
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

int aoc2022day6::part_one(std::vector<std::string> input) {
    return aoc2022day6::find_start_of_packet(input[0], 4);
}

int aoc2022day6::part_two(std::vector<std::string> input) {
    return aoc2022day6::find_start_of_packet(input[0], 14);
}

int aoc2022day6::solve(std::string path_input) {
    std::vector<std::string> input;

    if (!aoc2022day6::read_input(input, path_input)) {
        std::cout << "error reading input from " << path_input << std::endl;
        return 1;
    }

    std::cout << "year 2022 day 6" << std::endl;
    std::cout << "---------------" << std::endl;

    std::cout << "part one: " << aoc2022day6::part_one(input) << std::endl;
    std::cout << "part two: " << aoc2022day6::part_two(input) << std::endl;

    return 0;
}
