#include "day8.h"

namespace aoc2022day8 {
    bool read_input(std::vector<std::string>& out, std::string path_input) {
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

    std::vector<std::vector<int>> parse_input(std::vector<std::string>& input) {
        const int ROWS = input.size();
        std::vector<std::vector<int>> grid(ROWS, std::vector<int>());

        for (size_t i = 0; i < input.size(); i++) {
            std::string line = input[i];
            for (char c : line) {
                grid[i].push_back(std::stoi(std::string(1, c)));
            }
        }

        return grid;
    }

    bool visible_up(int row, int col, std::vector<std::vector<int>>& grid) {
        if (row <= 0) {
            return true;
        }
        const int TREE = grid[row][col];
        for (int i = row-1; i >= 0; i--) {
            if (grid[i][col] >= TREE) {
                return false;
            }
        }
        return true;
    }

    bool visible_down(int row, int col, std::vector<std::vector<int>>& grid) {
        if ((size_t) row == grid.size()) {
            return true;
        }
        const int TREE = grid[row][col];
        for (size_t i = row+1; i < grid.size(); i++) {
            if (grid[i][col] >= TREE) {
                return false;
            }
        }
        return true;
    }

    bool visible_left(int row, int col, std::vector<std::vector<int>>& grid) {
        if (col <= 0) {
            return true;
        }
        const int TREE = grid[row][col];
        for (int i = col-1; i >= 0; i--) {
            if (grid[row][i] >= TREE) {
                return false;
            }
        }
        return true;
    }

    bool visible_right(int row, int col, std::vector<std::vector<int>>& grid) {
        if ((size_t) col >= grid.size()) {
            return true;
        }
        const int TREE = grid[row][col];
        for (size_t i = col+1; i < grid.size(); i++) {
            if (grid[row][i] >= TREE) {
                return false;
            }
        }
        return true;
    }

    bool is_visible(int row, int col, std::vector<std::vector<int>>& grid) {
        return visible_left(row, col, grid) || visible_right(row, col, grid) || visible_up(row, col, grid) || visible_down(row, col, grid);
    }

    int score_up(int row, int col, std::vector<std::vector<int>>& grid) {
        if (row <= 0) {
            return 0;
        }
        const int TREE = grid[row][col];
        size_t score = 0;
        for (int i = row-1; i >= 0; i--) {
            score++;
            if (grid[i][col] >= TREE) {
                return score;
            }
        }
        return score;
    }

    int score_down(int row, int col, std::vector<std::vector<int>>& grid) {
        if ((size_t) row == grid.size()) {
            return 0;
        }
        const int TREE = grid[row][col];
        size_t score = 0;
        for (size_t i = row+1; i < grid.size(); i++) {
            score++;
            if (grid[i][col] >= TREE) {
                return score;
            }
        }
        return score;
    }

    int score_left(int row, int col, std::vector<std::vector<int>>& grid) {
        if (col <= 0) {
            return true;
        }
        const int TREE = grid[row][col];
        int score = 0;
        for (int i = col-1; i >= 0; i--) {
            score++;
            if (grid[row][i] >= TREE) {
                return score;
            }
        }
        return score;
    }

    int score_right(int row, int col, std::vector<std::vector<int>>& grid) {
        if ((size_t) col >= grid.size()) {
            return true;
        }
        const int TREE = grid[row][col];
        int score = 0;
        for (size_t i = col+1; i < grid.size(); i++) {
            score++;
            if (grid[row][i] >= TREE) {
                return score;
            }
        }
        return score;
    }

    int scenic_score(int row, int col, std::vector<std::vector<int>>& grid) {
        return score_up(row, col, grid) * score_down(row, col, grid) * score_left(row, col, grid) * score_right(row, col, grid);
    }

    int part_one(std::vector<std::vector<int>>& grid) {
        const int EDGES = (grid.size() * 2) + ((grid[0].size() - 2) * 2);
        int visible_trees = 0;
        for (size_t i = 1; i < grid.size() - 1; i++) {
            for (size_t j = 1; j < grid[i].size() - 1; j++) {
                if (is_visible(i, j, grid)) {
                    visible_trees++;
                }
            }
        }
        return visible_trees + EDGES;
    }

    int part_two(std::vector<std::vector<int>>& grid) {
        int highest_score = 0;
        for (size_t i = 1; i < grid.size() - 1; i++) {
            for (size_t j = 1; j < grid[i].size() - 1; j++) {
                int score = scenic_score(i, j, grid);
                if (score > highest_score) {
                    highest_score = score;
                }
            }
        }
        return highest_score;
    }

    int solve(const std::string path_input) {
        std::vector<std::string> input;

        if (!read_input(input, path_input)) {
            std::cout << "error reading input from " << path_input << std::endl;
            return 1;
        }

        std::vector<std::vector<int>> grid = parse_input(input);

        std::cout << "year 2022 day 8" << std::endl;
        std::cout << "part one: " << part_one(grid) << std::endl;
        std::cout << "part two: " << part_two(grid) << std::endl;

        return 0;
    }
}
