#include "aoc2022.h"
#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"
#include "day7.h"

int aoc2022::solve(const int day, const std::string path_input) {
    switch (day) {
        case 1: {
            return aoc2022day1::solve(path_input);
        } break;
        case 2: {
            return aoc2022day2::solve(path_input);
        } break;
        case 3: {
            return aoc2022day3::solve(path_input);
        } break;
        case 4: {
            return aoc2022day4::solve(path_input);
        } break;
        case 5: {
            return aoc2022day5::solve(path_input);
        } break;
        case 6: {
            return aoc2022day6::solve(path_input);
        } break;
        case 7: {
            return aoc2022day7::solve(path_input);
        }
        default: {
            std::cout << "no solution available for year 2022 day " << day << std::endl;
            return 1;
        }
    }
}
