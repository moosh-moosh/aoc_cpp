#include <iostream>
#include <string>
#include "aoc_2022/day1.h"

using namespace std;

void print_usage() {
    cout << "usage:" << endl;
    cout << "aoc <year> <day> <path_to_input_file>" << endl;;
}

int solve_2022(const int day, const string path_input) {
    switch (day) {
        case 1: {
            return aoc2022day1::solve(path_input);
        } break;
        default: {
            cout << "no solution found for year 2022 day " << day << endl;
            return 1;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cout << "invalid arguments" << endl;
        print_usage();
        return 1;
    }

    const int YEAR = stoi(argv[1]);
    const int DAY = stoi(argv[2]);
    const string PATH_INPUT = argv[3];

    switch (YEAR) {
        case 2022: {
            return solve_2022(DAY, PATH_INPUT);
        } break;
        default: {
            cout << "no solution found for year " << YEAR << " day " << DAY << endl;
            return 1;
        }
    }

    return 0;
}
