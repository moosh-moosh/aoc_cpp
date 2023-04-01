#include "day11.h"
#include <fstream>
#include <regex>
#include <stdexcept>
#include <numeric>
#include <algorithm>

namespace aoc2022day11 {
    bool read_input(std::map<int, Monkey> &monkeys, const std::string path_input) {
        std::ifstream in(path_input);
        std::string line;
        std::regex pattern_monkey("Monkey\\s(\\d+):");
        std::regex pattern_items("Starting\\sitems:");
        std::regex pattern_operation("Operation:");
        std::regex pattern_test("Test:");
        std::regex pattern_success("If true:.*(\\d+)");
        std::regex pattern_failure("If false:.*(\\d+)");
        std::smatch match;

        if (!in) {
            return false;
        }

        int monkey_id = 0;
        while (std::getline(in, line)) {
            if (std::regex_search(line, match, pattern_monkey)) {
                Monkey m;
                monkey_id = std::stoi(match[1]);
                m.id = monkey_id;
                m.inspect_count = 0;
                monkeys[monkey_id] = m;
            }
            else if (std::regex_search(line, match, pattern_items)) {
                parse_items(monkeys[monkey_id], line);
            }
            else if (std::regex_search(line, match, pattern_operation)) {
                parse_operation(monkeys[monkey_id], line);
            }
            else if (std::regex_search(line, match, pattern_test)) {
                parse_test(monkeys[monkey_id], line);
            }
            else if (std::regex_search(line, match, pattern_success)) {
                monkeys[monkey_id].target_success = std::stoi(match[1]);
            }
            else if (std::regex_search(line, match, pattern_failure)) {
                monkeys[monkey_id].target_failure = std::stoi(match[1]);
            }
        }
        in.close();

        return true;
    }

    void parse_items(Monkey &monkey, std::string line) {
        std::regex pattern("(\\d+)");
        std::smatch match;

        while (std::regex_search(line, match, pattern)) {
            monkey.items.push_back(std::stol(match[1]));
            line = match.suffix();
        }
    }

    void parse_operation(Monkey &monkey, std::string line) {
        std::regex pattern("old\\s([-+*/])\\s(old|\\d+)");
        std::smatch match;

        if (std::regex_search(line, match, pattern)) {
            const char op = match[1].str()[0];
            const std::string operand = match[2];

            switch (op) {
                case '-': {
                    monkey.operation = [operand](long item) {
                        if (operand == "old") {
                            return item - item;
                        }
                        return item - std::stol(operand);
                    };
                } break;
                case '+': {
                    monkey.operation = [operand](long item) {
                        if (operand == "old") {
                            return item + item;
                        }
                        return item + std::stol(operand);
                    };
                } break;
                case '*': {
                    monkey.operation = [operand](long item) {
                        if (operand == "old") {
                            return item * item;
                        }
                        return item * std::stol(operand);
                    };
                } break;
                case '/': {
                    monkey.operation = [operand](long item) {
                        if (operand == "old") {
                            return item / item;
                        }
                        return item / std::stol(operand);
                    };
                } break;
                default: {
                    throw std::runtime_error("unparseable operation");
                }
            }
        }
    }

    void parse_test(Monkey &monkey, std::string line) {
        std::regex pattern("(\\d+)");
        std::smatch match;

        if (std::regex_search(line, match, pattern)) {
            const int n = std::stoi(match[1]);
            monkey.test_n = n;
        }
    }

    long get_lcm(std::map<int, Monkey> &monkeys) {
        long _lcm = 0;
        for (auto const& kv : monkeys) {
            if (_lcm) {
                _lcm = _lcm * kv.second.test_n;
            } else {
                _lcm = kv.second.test_n;
            }
        }
        return _lcm;
    }

    void process_round(std::map<int, Monkey> &monkeys, bool relief, long lcm) {
        for (auto const& kv : monkeys) {
            Monkey m = kv.second;
            for (long item : m.items) {
                m.inspect(item, monkeys, relief, lcm);
            }
            m.items = std::vector<long>();
            monkeys[m.id] = m;
        }
    }

    long monkey_business(std::map<int, Monkey> &monkeys) {
        std::vector<long> inspect_counts;
        for (auto const& kv : monkeys) {
            inspect_counts.push_back(kv.second.inspect_count);
        }
        std::sort(inspect_counts.begin(), inspect_counts.end(), [](int a, int b) { return a > b; });
        return inspect_counts[0] * inspect_counts[1];
    }

    long part_one(std::map<int, Monkey> monkeys) {
        for (size_t i = 0; i < 20; i++) {
            process_round(monkeys, true, 0);
        }

        return monkey_business(monkeys);
    }

    long part_two(std::map<int, Monkey> monkeys) {
        const long lcm = get_lcm(monkeys);
        for (size_t i = 0; i < 10000; i++) {
            process_round(monkeys, false, lcm);
        }

        return monkey_business(monkeys);
    }

    int solve(const std::string path_input) {
        std::map<int, Monkey> monkeys;

        if (!read_input(monkeys, path_input)) {
            std::cout << "failed to parse input from " << path_input << std::endl;
            return 1;
        }

        std::cout << "year 2022 day 11" << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout << "part one: " << part_one(monkeys) << std::endl;
        std::cout << "part two: " << part_two(monkeys) << std::endl;

        return 0;
    }
}
