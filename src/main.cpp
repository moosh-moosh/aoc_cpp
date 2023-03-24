#include <iostream>
#include <string>
#include "aoc_2022/aoc2022.h"
#define NUM_ARGS 4

using namespace std;

void print_usage() {
    cout << "usage:" << endl;
    cout << "aoc <year> <day> <path_to_input_file>" << endl;
}

int solve_2022(const int day, const string path_input) {
    return aoc2022::solve(day, path_input);
}

int main(int argc, char *argv[]) {
    if (argc < NUM_ARGS) {
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
}
