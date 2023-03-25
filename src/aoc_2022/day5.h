#ifndef DAY5_H_
#define DAY5_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <regex>

namespace aoc2022day5 {

    struct Instruction {
        int from;
        int to;
        int count;
    };

    int solve(const std::string path_input);
    bool read_input(std::vector<std::string>& stacks, std::vector<std::string>& instructions, std::string path_input);
    int get_stack_count(std::vector<std::string>& stacks);
    void build_stacks(std::vector<std::stack<char>>& stacks, std::vector<std::string>& stack_lines, const int stack_count);
    std::vector<char> parse_stack(std::string line, const int stack_count);
    std::vector<Instruction> parse_instructions(std::vector<std::string> instructions);
    Instruction parse_instruction(std::string line);
    void move(std::vector<std::stack<char>>& stacks, Instruction instruction);
    void move_9001(std::vector<std::stack<char>>& stacks, Instruction instruction);
    std::vector<std::stack<char>> handle_instructions(std::vector<std::stack<char>>& stacks, std::vector<Instruction>& instructions, const int part);
    std::string get_top_items(std::vector<std::stack<char>>& stacks);
    std::string part_one(std::vector<std::stack<char>> stacks, std::vector<Instruction>& instructions);
    std::string part_two(std::vector<std::stack<char>> stacks, std::vector<Instruction>& instructions);
}


#endif // DAY5_H_
