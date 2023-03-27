#ifndef DAY8_H_
#define DAY8_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

namespace aoc2022day8 {
    int solve(const std::string path_input);
    bool read_input(std::vector<std::string>& out, std::string path_input);
    std::vector<std::vector<int>> parse_input(std::vector<std::string>& input);
    bool visible_left(int row, int col, std::vector<std::vector<int>>& grid);
    bool visible_right(int row, int col, std::vector<std::vector<int>>& grid);
    bool visible_up(int row, int col, std::vector<std::vector<int>>& grid);
    bool visible_down(int row, int col, std::vector<std::vector<int>>& grid);
    bool is_visible(int row, int cold, std::vector<std::vector<int>>& grid);
    int score_left(int row, int col, std::vector<std::vector<int>>& grid);
    int score_right(int row, int col, std::vector<std::vector<int>>& grid);
    int score_up(int row, int col, std::vector<std::vector<int>>& grid);
    int score_down(int row, int col, std::vector<std::vector<int>>& grid);
    int scenic_score(int row, int col, std::vector<std::vector<int>>& grid);
    int part_one(std::vector<std::vector<int>>& grid);
    int part_two(std::vector<std::vector<int>>& grid);
}

#endif // DAY8_H_
