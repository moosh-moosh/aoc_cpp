#include "day5.h"

namespace aoc2022day5 {

    bool read_input(std::vector<std::string>& stacks,
                                std::vector<std::string>& instructions,
                                std::string path_input) {
        std::ifstream in(path_input);
        std::string line;

        if (!in) {
            return false;
        }

        bool is_instructions = false;

        while (std::getline(in, line)) {
            if (line.length() == 0) {
                is_instructions = true;
                continue;
            }
            if (is_instructions) {
                instructions.push_back(line);
            } else {
                stacks.push_back(line);
            }
        }
        in.close();

        return true;
    }

    int get_stack_count(std::vector<std::string>& stacks) {
        const std::string count_line = stacks.back();
        std::regex pattern("\\d+\\s*$");
        std::smatch match;
        int count = 0;

        if (std::regex_search(count_line, match, pattern)) {
            count = std::stoi(match.str());
        }

        return count;
    }

    std::vector<char> parse_stack(std::string line, const int stack_count) {
        std::vector<char> items;
        for (size_t i = 1; i < line.length(); i += 4) {
            items.push_back(line[i]);
        }
        items.resize(stack_count, ' ');

        return items;
    }

    void build_stacks(std::vector<std::stack<char>>& stacks, std::vector<std::string>& stack_lines, const int stack_count) {
        for (size_t i = stack_lines.size() - 1; i != (size_t) - 1; i--) {
            std::vector<char> items = parse_stack(stack_lines[i], stack_count);
            for (size_t j = 0; j < items.size(); j++) {
                if (items[j] == ' ') {
                    continue;
                }
                stacks[j].push(items[j]);
            }
        }
    }

    Instruction parse_instruction(std::string line) {
        std::regex pattern("move\\s(\\d+)\\sfrom\\s(\\d+)\\sto\\s(\\d+)");
        std::smatch matches;
        Instruction inst;

        if (std::regex_search(line, matches, pattern)) {
            const int count = std::stoi(matches[1]);
            const int from = std::stoi(matches[2]) - 1;
            const int to = std::stoi(matches[3]) - 1;
            inst.count = count;
            inst.from = from;
            inst.to = to;
        }

        return inst;
    }

    std::vector<Instruction> parse_instructions(std::vector<std::string> instructions) {
        std::vector<Instruction> insts;
        for (std::string inst : instructions) {
            insts.push_back(parse_instruction(inst));
        }

        return insts;
    }

    void move(std::vector<std::stack<char>>& stacks, Instruction instruction) {
        for (int i = 0; i < instruction.count; i++) {
            char item = stacks[instruction.from].top();
            stacks[instruction.to].push(item);
            stacks[instruction.from].pop();
        }
    }

    void move_9001(std::vector<std::stack<char>>& stacks, Instruction instruction) {
        std::stack<char> tmp;
        for (int i = 0; i < instruction.count; i++) {
            char item = stacks[instruction.from].top();
            tmp.push(item);
            stacks[instruction.from].pop();
        }

        while (!tmp.empty()) {
            stacks[instruction.to].push(tmp.top());
            tmp.pop();
        }
    }

    std::vector<std::stack<char>> handle_instructions(std::vector<std::stack<char>>& stacks,
                                                                std::vector<Instruction>& instructions,
                                                                const int part) {

        for (Instruction instruction : instructions) {
            if (part == 1) {
                move(stacks, instruction);
            } else {
                move_9001(stacks, instruction);
            }
        }
        return stacks;
    }

    std::string get_top_items(std::vector<std::stack<char>>& stacks) {
        std::stringstream ss;

        for (size_t i = 0; i < stacks.size(); i++) {
            ss << stacks[i].top();
        }

        return ss.str();
    }

    std::string part_one(std::vector<std::stack<char>> stacks, std::vector<Instruction>& instructions) {
        handle_instructions(stacks, instructions, 1);
        return get_top_items(stacks);
    }

    std::string part_two(std::vector<std::stack<char>> stacks, std::vector<Instruction>& instructions) {
        handle_instructions(stacks, instructions, 2);
        return get_top_items(stacks);
    }

    int solve(const std::string path_input) {
        std::vector<std::string> stack_lines, instruction_lines;
        if (!read_input(stack_lines, instruction_lines, path_input)) {
            std::cout << "error reading input from " << path_input << std::endl;
            return 1;
        }

        const int STACK_COUNT = get_stack_count(stack_lines);

        if (STACK_COUNT == 0) {
            std::cout << "error parsing stack count" << std::endl;
            return 1;
        }

        // Remove the count line from stacks
        stack_lines.pop_back();

        std::vector<std::stack<char>> stacks(STACK_COUNT);
        build_stacks(stacks, stack_lines, STACK_COUNT);

        std::vector<Instruction> instructions = parse_instructions(instruction_lines);

        std::cout << "year 2022 day 5" << std::endl;
        std::cout << "---------------" << std::endl;

        std::cout << "part one: " << part_one(stacks, instructions) << std::endl;
        std::cout << "part two: " << part_two(stacks, instructions) << std::endl;

        return 0;
    }

}
