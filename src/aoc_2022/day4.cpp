#include "day4.h"

bool aoc2022day4::read_input(std::vector<std::string>& out, std::string path_input) {
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

std::vector<aoc2022day4::Pair> aoc2022day4::parse_pairs(std::vector<std::string>& input) {
    std::vector<aoc2022day4::Pair> pairs;
    for (std::string line : input) {
        pairs.push_back(parse_pair(line));
    }
    return pairs;
}

aoc2022day4::Pair aoc2022day4::parse_pair(std::string& line) {
    std::regex pattern("(\\d+)-(\\d+),(\\d+)-(\\d+)");
    std::smatch matches;
    aoc2022day4::Pair p;

    if (std::regex_search(line, matches, pattern)) {
        const int sect1_start = std::stoi(matches[1]);
        const int sect1_end = std::stoi(matches[2]);
        const int sect2_start = std::stoi(matches[3]);
        const int sect2_end = std::stoi(matches[4]);
        const int sect1_size = sect1_end - sect1_start + 1;
        const int sect2_size = sect2_end - sect2_start + 1;
        std::vector<int> sect1(sect1_size);
        std::vector<int> sect2(sect2_size);
        std::iota(sect1.begin(), sect1.end(), sect1_start);
        std::iota(sect2.begin(), sect2.end(), sect2_start);
        p.section1 = sect1;
        p.section2 = sect2;
    } else {
        throw "unable to parse pair from " + line;
    }

    return p;
}

bool aoc2022day4::pair_contains_range(aoc2022day4::Pair pair) {
    if (std::includes(pair.section1.begin(), pair.section1.end(), pair.section2.begin(), pair.section2.end())) {
        return true;
    } else if (std::includes(pair.section2.begin(), pair.section2.end(), pair.section1.begin(), pair.section1.end())) {
        return true;
    }
    return false;
}

bool aoc2022day4::pair_contains_common(aoc2022day4::Pair pair) {
    std::vector<int> common;
    std::set_intersection(pair.section1.begin(), pair.section1.end(), pair.section2.begin(), pair.section2.end(), std::back_inserter(common));

    return common.size() > 0;
}

int aoc2022day4::part_one(std::vector<aoc2022day4::Pair>& pairs) {
    int count = 0;
    for (aoc2022day4::Pair pair : pairs) {
        if (aoc2022day4::pair_contains_range(pair)) {
            count++;
        }
    }
    return count;
}

int aoc2022day4::part_two(std::vector<aoc2022day4::Pair>& pairs) {
    int count = 0;
    for (aoc2022day4::Pair pair : pairs) {
        if (aoc2022day4::pair_contains_common(pair)) {
            count++;
        }
    }
    return count;
}

int aoc2022day4::solve(const std::string path_input) {
    std::vector<std::string> input;

    if (!aoc2022day4::read_input(input, path_input)) {
        return 1;
    }

    std::vector<aoc2022day4::Pair> PAIRS = parse_pairs(input);

    std::cout << "year 2022 day 4" << std::endl;
    std::cout << "---------------" << std::endl;

    std::cout << "part one: " << aoc2022day4::part_one(PAIRS) << std::endl;
    std::cout << "part two: " << aoc2022day4::part_two(PAIRS) << std::endl;

    return 0;
}
