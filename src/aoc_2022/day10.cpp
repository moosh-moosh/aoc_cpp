#include "day10.h"

namespace aoc2022day10 {

    const char DRAWN = '#';
    const char DARK = '.';

    bool read_input(std::vector<Operation>& out, const std::string path_input) {
        std::ifstream in(path_input);
        std::regex pattern("^(noop|addx)\\s?(-?\\d+)?");
        std::string line;
        std::smatch matches;

        if (!in) {
            return false;
        }

        while (std::getline(in, line)) {
            if (std::regex_search(line, matches, pattern)) {
                const std::string action = matches[1];
                if (action == "noop") {
                    out.push_back(Operation{1, 0});
                    continue;
                }
                if (matches.size() < 3) {
                    throw std::runtime_error("parse error");
                }
                const int n = std::stoi(matches[2]);
                out.push_back(Operation{2, n});
            }
        }
        in.close();

        return true;
    }

    std::vector<int> run_ops(std::vector<Operation>& ops) {
        std::vector<int> stream {1};
        int x = 1;

        for (Operation op : ops) {
            for (int i = 0; i < op.num_cycles; i++) {
                stream.push_back(x);
            }
            x += op.x;
        }

        return stream;
    }

    int calculate_signal_strength(std::vector<int>& stream, int cycle) {
        const int x = stream[cycle];
        return cycle * x;
    }

    bool draw_pixel(std::vector<int>& stream, int pos, int cycle) {
        //std::cout << "pos: " << pos << ", cycle: " << cycle << std::endl;
        const int x = stream[cycle];
        return pos == x || pos == x-1 || pos == x+1;
    }

    int part_one(std::vector<int>& stream) {
        std::vector<int> signal_strengths;
        signal_strengths.push_back(calculate_signal_strength(stream, 20));
        signal_strengths.push_back(calculate_signal_strength(stream, 60));
        signal_strengths.push_back(calculate_signal_strength(stream, 100));
        signal_strengths.push_back(calculate_signal_strength(stream, 140));
        signal_strengths.push_back(calculate_signal_strength(stream, 180));
        signal_strengths.push_back(calculate_signal_strength(stream, 220));
        return std::accumulate(signal_strengths.begin(), signal_strengths.end(), 0);
    }

    void part_two(std::vector<int>& stream) {
        for (size_t i = 0; i < stream.size()-1; i++) {
            if (i != 0 && i % 40 == 0) {
                std::cout << std::endl;
            }
            const size_t pos = i % 40;
            if (draw_pixel(stream, pos, i+1)) {
                std::cout << DRAWN;
            } else {
                std::cout << DARK;
            }
        }
    }

    int solve(const std::string path_input) {
        std::vector<Operation> ops;

        if (!read_input(ops, path_input)) {
            std::cout << "failed to read input from " << path_input << std::endl;
            return 1;
        }

        std::vector<int> stream = run_ops(ops);

        std::cout << "part one: " << part_one(stream) << std::endl;
        std::cout << "part two:" << std::endl;
        part_two(stream);

        return 0;
    }
}
