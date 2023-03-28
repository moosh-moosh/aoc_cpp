#ifndef DAY9_H_
#define DAY9_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <map>
#include <cmath>
#include <unordered_set>

namespace aoc2022day9 {

    enum class Direction {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    const std::map<std::string, Direction> dir_map = {
        {"L", Direction::LEFT},
        {"R", Direction::RIGHT},
        {"U", Direction::UP},
        {"D", Direction::DOWN}
    };

    struct Instruction {
        Direction dir;
        int steps;
    };

    struct Point {
        int x, y;
    };

    struct Rope {
        Point head;
        std::vector<Point> tail;
        std::unordered_set<int> tail_locs;
    };

    int solve(const std::string path_input);
    bool read_input(std::vector<Instruction>& out, const std::string path_input);
    Instruction parse_instruction(std::string line);
    void print_instruction(Instruction& instruction);
    Rope create_rope(size_t len_tail);
    size_t get_distance(Point& p1, Point& p2);
    void move(Rope& rope, Direction dir);
    void drag_tail(Rope& rope);
    void move_tail(Point h, Point& t);
    void move_left(Point& point);
    void move_right(Point& point);
    void move_up(Point& point);
    void move_down(Point& point);
    void move_up_left(Point& point);
    void move_down_left(Point& point);
    void move_up_right(Point& point);
    void move_down_right(Point& point);
    void handle_instruction(Rope& rope, Instruction instruction);
    void add_tail_loc(Rope& rope, Point& loc);
    int part_one(std::vector<Instruction>& instructions);
    int part_two(std::vector<Instruction>& instructions);
}

#endif // DAY9_H_
