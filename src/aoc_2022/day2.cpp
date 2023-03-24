#include "day2.h"

// Boring solution since there are so few possible outcomes
// just lay them all out in a map and get the scores...
//
// Might write this out later but it's not that interesting of
// a problem.
//

// I have no idea if these should be defined in the header or what
const int PTS_ROCK     = 1;
const int PTS_PAPER    = 2;
const int PTS_SCISSORS = 3;

const int PTS_WIN  = 6;
const int PTS_DRAW = 3;
const int PTS_LOSS = 0;

const std::map<std::string, int> POINTS_P1 = {
    {"A X", PTS_DRAW + PTS_ROCK},
    {"A Y", PTS_WIN  + PTS_PAPER},
    {"A Z", PTS_LOSS + PTS_SCISSORS},
    {"B X", PTS_LOSS + PTS_ROCK},
    {"B Y", PTS_DRAW + PTS_PAPER},
    {"B Z", PTS_WIN  + PTS_SCISSORS},
    {"C X", PTS_WIN  + PTS_ROCK},
    {"C Y", PTS_LOSS + PTS_PAPER},
    {"C Z", PTS_DRAW + PTS_SCISSORS}
};

const std::map<std::string, int> POINTS_P2 = {
    {"A X", PTS_LOSS + PTS_SCISSORS},
    {"A Y", PTS_DRAW + PTS_ROCK},
    {"A Z", PTS_WIN  + PTS_PAPER},
    {"B X", PTS_LOSS + PTS_ROCK},
    {"B Y", PTS_DRAW + PTS_PAPER},
    {"B Z", PTS_WIN  + PTS_SCISSORS},
    {"C X", PTS_LOSS + PTS_PAPER},
    {"C Y", PTS_DRAW + PTS_SCISSORS},
    {"C Z", PTS_WIN  + PTS_ROCK}
};

bool aoc2022day2::read_input(std::vector<std::string> &out, std::string path_input) {
    std::ifstream in(path_input);
    std::string line;

    if (!in) {
        return false;
    }

    while (std::getline(in, line)) {
        if (line.length() == 0) {
            continue;
        }
        out.push_back(line);
    }
    in.close();

    return true;
}

int aoc2022day2::part_one(std::vector<std::string>& input) {
    int score = 0;
    for (std::string line : input) {
        score += POINTS_P1.at(line);
    }

    return score;
}

int aoc2022day2::part_two(std::vector<std::string> &input) {
    int score = 0;
    for (std::string line : input) {
        if (line.length() == 0) {
            continue;
        }
        score += POINTS_P2.at(line);
    }

    return score;
}

int aoc2022day2::solve(std::string path_input) {
    std::vector<std::string> input;

    if (!aoc2022day2::read_input(input, path_input)) {
        std::cout << "error reading input from '" << path_input << "'" << std::endl;
        return 1;
    }

    std::cout << "year 2022 day 2" << std::endl;
    std::cout << "---------------" << std::endl;

    std::cout << "part one: " << aoc2022day2::part_one(input) << std::endl;
    std::cout << "part two: " << aoc2022day2::part_two(input) << std::endl;

    return 0;
}
