#include "aoc2022.h"
#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"
#include "day7.h"
#include "day8.h"
#include "day9.h"
#include "day10.h"
#include "day11.h"
#include "day12.h"
#include "day13.h"
#include "day14.h"

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
        } break;
        case 8: {
            return aoc2022day8::solve(path_input);
        } break;
        case 9: {
            return aoc2022day9::solve(path_input);
        }
        case 10: {
            return aoc2022day10::solve(path_input);
        }
        case 11: {
            return aoc2022day11::solve(path_input);
        }
        case 12: {
            return aoc2022day12::solve(path_input);
        }
        case 13: {
            return aoc2022day13::solve(path_input);
        }
        case 14: {
            return aoc2022day14::solve(path_input);
        }
        default: {
            std::cout << "no solution available for year 2022 day " << day << std::endl;
            return 1;
        }
    }
}
