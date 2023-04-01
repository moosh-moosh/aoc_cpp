#ifndef DAY11_H_
#define DAY11_H_

#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <map>

namespace aoc2022day11 {
    struct Monkey {
        int id;
        int inspect_count;
        int target_success;
        int target_failure;
        std::function<long(int)> operation;
        std::function<bool(int)> test;
        std::vector<long> items;
        void inspect(long item, std::map<int, Monkey> &monkeys, bool relief) {
            inspect_count++;
            long worry = operation(item);

            if (relief) {
                worry = worry / 3;
            }

            if (test(worry)) {
                monkeys[target_success].items.push_back(worry);
            } else {
                monkeys[target_failure].items.push_back(worry);
            }
        }
    };

    bool read_input(std::map<int, Monkey> &monkeys, const std::string path_input);
    void parse_items(Monkey &monkey, std::string line);
    void parse_operation(Monkey &monkey, std::string line);
    void parse_test(Monkey &monkey, std::string line);
    void process_round(std::map<int, Monkey> &monkeys, bool relief);
    long monkey_business(std::map<int, Monkey> &monkeys);
    long part_one(std::map<int, Monkey> &monkeys);
    int solve(const std::string path_input);
}

#endif // DAY11_H_
