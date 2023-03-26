#include "day1.h"

namespace aoc2022day1 {

    bool read_input(std::vector<std::string> &out, std::string path) {
        std::ifstream in(path);
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

    std::vector<int> parse_input(std::vector<std::string> input) {
        std::vector<int> elves;
        int calories = 0;

        for (std::string cal : input) {
            if (cal.length() == 0) {
                elves.push_back(calories);
                calories = 0;
                continue;
            }
            calories += std::stoi(cal);
        }
        std::sort(elves.begin(), elves.end(), [](int a, int b) { return a > b; });

        return elves;
    }

    int part_one(std::vector<int> &elves) {
        return elves[0];
    }

    int part_two(std::vector<int> &elves) {
        return std::accumulate(elves.begin(), elves.begin()+3, 0);
    }

    int solve(std::string path_input) {
        std::vector<std::string> input;

        if (!read_input(input, path_input)) {
            std::cout << "error reading input from '" << path_input << "'" << std::endl;
            return 1;
        }

        std::vector<int> elves = parse_input(input);

        std::cout << "year 2022, day 1" << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout << "part one: " << part_one(elves) << std::endl;
        std::cout << "part two: " << part_two(elves) << std::endl;

        return 0;
    }

}
