#include "day3.h"

bool aoc2022day3::read_input(std::vector<std::string>& out, std::string path_input) {
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

char aoc2022day3::get_common_item(std::string rucksack) {
    const size_t LEN = rucksack.length();
    const size_t MID = LEN / 2;

    std::string c1 = rucksack.substr(0, MID);
    std::string c2 = rucksack.substr(MID, LEN);
    std::set<char> r1(c1.begin(), c1.end());
    std::set<char> r2(c2.begin(), c2.end());

    std::set<char> intersection;
    std::set_intersection(r1.begin(), r1.end(), r2.begin(), r2.end(), std::inserter(intersection, intersection.begin()));

    if (intersection.size() == 0) {
        // FIXME: Apparently this is not correct since if we get here, a different
        // exception is thrown. So figure out how to properly throw custom exceptions
        // in C++ at some point.
        throw "no common items in rucksack " + rucksack;
    }

    const char COMMON_ITEM = *(intersection.begin());

    return COMMON_ITEM;
}

int aoc2022day3::get_char_score(char c) {
    if (std::isupper(c)) {
        return c - 'A' + 27;
    } else {
        return c - 'a' + 1;
    }
}

int aoc2022day3::part_one(std::vector<std::string>& input) {
    int total = 0;
    for (std::string rucksack : input) {
        total += aoc2022day3::get_char_score(aoc2022day3::get_common_item(rucksack));
    }

    return total;
}

char aoc2022day3::get_common_among_elves(std::string e1, std::string e2, std::string e3) {

    std::set<char> s1(e1.begin(), e1.end());
    std::set<char> s2(e2.begin(), e2.end());
    std::set<char> s3(e3.begin(), e3.end());
    std::set<char> int1, int2;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(int1, int1.begin()));
    std::set_intersection(int1.begin(), int1.end(), s3.begin(), s3.end(), std::inserter(int2, int2.begin()));

    if (int2.size() == 0) {
        // FIXME: Apparently this is not correct since if we get here, a different
        // exception is thrown. So figure out how to properly throw custom exceptions
        // in C++ at some point.
        throw "no common items among elves";
    }

    const char COMMON_ITEM = *(int2.begin());
    return COMMON_ITEM;
}

int aoc2022day3::part_two(std::vector<std::string>& input) {
    int total = 0;
    for (size_t i = 0; i < input.size(); i += 3) {
        std::string e1 = input[i];
        std::string e2 = input[i+1];
        std::string e3 = input[i+2];
        char common = get_common_among_elves(e1, e2, e3);
        total += get_char_score(common);
    }
    return total;
}

int aoc2022day3::solve(const std::string path_input) {
    std::vector<std::string> input;

    if (!aoc2022day3::read_input(input, path_input)) {
        return 1;
    }

    std::cout << "year 2022 day 3" << std::endl;
    std::cout << "---------------" << std::endl;

    std::cout << "part one: " << aoc2022day3::part_one(input) << std::endl;
    std::cout << "part two: " << aoc2022day3::part_two(input) << std::endl;

    return 0;
}
