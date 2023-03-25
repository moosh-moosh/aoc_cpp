#include "day5.h"


bool aoc2022day5::read_input(std::vector<std::string>& stacks,
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

int aoc2022day5::get_stack_count(std::vector<std::string>& stacks) {
    const std::string count_line = stacks.back();
    std::regex pattern("\\d+\\s*$");
    std::smatch match;
    int count = 0;

    if (std::regex_search(count_line, match, pattern)) {
        count = std::stoi(match.str());
    }

    return count;
}

std::vector<char> aoc2022day5::parse_stack(std::string line, const int stack_count) {
    std::vector<char> items;
    for (size_t i = 1; i < line.length(); i += 4) {
        items.push_back(line[i]);
    }
    items.resize(stack_count, ' ');

    return items;
}

void aoc2022day5::build_stacks(std::vector<std::stack<char>>& stacks, std::vector<std::string>& stack_lines, const int stack_count) {
    for (size_t i = stack_lines.size() - 1; i != (size_t) - 1; i--) {
        std::vector<char> items = aoc2022day5::parse_stack(stack_lines[i], stack_count);
        for (size_t j = 0; j < items.size(); j++) {
            if (items[j] == ' ') {
                continue;
            }
            stacks[j].push(items[j]);
        }
    }
}

aoc2022day5::Instruction aoc2022day5::parse_instruction(std::string line) {
    std::regex pattern("move\\s(\\d+)\\sfrom\\s(\\d+)\\sto\\s(\\d+)");
    std::smatch matches;
    aoc2022day5::Instruction inst;

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

std::vector<aoc2022day5::Instruction> aoc2022day5::parse_instructions(std::vector<std::string> instructions) {
    std::vector<aoc2022day5::Instruction> insts;
    for (std::string inst : instructions) {
        insts.push_back(aoc2022day5::parse_instruction(inst));
    }

    return insts;
}

void aoc2022day5::move(std::vector<std::stack<char>>& stacks, aoc2022day5::Instruction instruction) {
    for (int i = 0; i < instruction.count; i++) {
        char item = stacks[instruction.from].top();
        stacks[instruction.to].push(item);
        stacks[instruction.from].pop();
    }
}

void aoc2022day5::move_9001(std::vector<std::stack<char>>& stacks, aoc2022day5::Instruction instruction) {
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

std::vector<std::stack<char>> aoc2022day5::handle_instructions(std::vector<std::stack<char>>& stacks,
                                                               std::vector<aoc2022day5::Instruction>& instructions,
                                                               const int part) {

    for (aoc2022day5::Instruction instruction : instructions) {
        if (part == 1) {
            aoc2022day5::move(stacks, instruction);
        } else {
            aoc2022day5::move_9001(stacks, instruction);
        }
    }
    return stacks;
}

std::string aoc2022day5::get_top_items(std::vector<std::stack<char>>& stacks) {
    std::stringstream ss;

    for (size_t i = 0; i < stacks.size(); i++) {
        ss << stacks[i].top();
    }

    return ss.str();
}

std::string aoc2022day5::part_one(std::vector<std::stack<char>> stacks, std::vector<aoc2022day5::Instruction>& instructions) {
    aoc2022day5::handle_instructions(stacks, instructions, 1);
    return aoc2022day5::get_top_items(stacks);
}

std::string aoc2022day5::part_two(std::vector<std::stack<char>> stacks, std::vector<aoc2022day5::Instruction>& instructions) {
    aoc2022day5::handle_instructions(stacks, instructions, 2);
    return aoc2022day5::get_top_items(stacks);
}

int aoc2022day5::solve(const std::string path_input) {
    std::vector<std::string> stack_lines, instructions;
    if (!aoc2022day5::read_input(stack_lines, instructions, path_input)) {
        std::cout << "error reading input from " << path_input << std::endl;
        return 1;
    }

    const int STACK_COUNT = aoc2022day5::get_stack_count(stack_lines);

    if (STACK_COUNT == 0) {
        std::cout << "error parsing stack count" << std::endl;
        return 1;
    }

    // Remove the count line from stacks
    stack_lines.pop_back();

    std::vector<std::stack<char>> stacks(STACK_COUNT);
    aoc2022day5::build_stacks(stacks, stack_lines, STACK_COUNT);

    std::vector<aoc2022day5::Instruction> insts = aoc2022day5::parse_instructions(instructions);

    std::cout << "year 2022 day 5" << std::endl;
    std::cout << "---------------" << std::endl;

    std::cout << "part one: " << aoc2022day5::part_one(stacks, insts) << std::endl;
    std::cout << "part two: " << aoc2022day5::part_two(stacks, insts) << std::endl;

    return 0;
}
