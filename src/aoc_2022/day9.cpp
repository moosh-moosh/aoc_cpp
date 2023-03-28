#include "day9.h"

namespace aoc2022day9 {

    bool read_input(std::vector<Instruction>& out, const std::string path_input) {
        std::ifstream in(path_input);
        std::string line;

        if (!in) {
            return false;
        }

        while (std::getline(in, line)) {
            out.push_back(parse_instruction(line));
        }

        in.close();

        return true;
    }

    Instruction parse_instruction(std::string line) {
        std::regex pattern("([DULR])\\s(\\d+)");
        std::smatch match;
        Instruction instruction;

        if (std::regex_search(line, match, pattern)) {
            instruction.steps = std::stoi(match[2]);
            instruction.dir = dir_map.at(match[1]);
        }

        return instruction;
    }

    void print_instruction(Instruction& instruction) {
        switch (instruction.dir) {
            case Direction::LEFT: {
                std::cout << "move LEFT " << instruction.steps << " steps" << std::endl;
            } break;
            case Direction::UP: {
                std::cout << "move UP " << instruction.steps << " steps" << std::endl;
            } break;
            case Direction::RIGHT: {
                std::cout << "move RIGHT " << instruction.steps << " steps" << std::endl;
            } break;
            case Direction::DOWN: {
                std::cout << "move DOWN " << instruction.steps << " steps" << std::endl;
            } break;
        }
    }

    Rope create_rope(size_t len_tail) {
        Rope rope;
        rope.head = Point{0, 0};
        std::vector<Point> tail;
        std::unordered_set<int> tail_locs;
        for (size_t i = 0; i < len_tail; i++) {
            tail.push_back(Point{0, 0});
        }
        rope.tail = tail;
        rope.tail_locs = tail_locs;
        add_tail_loc(rope, rope.head);

        return rope;
    }

    void move_up(Point& point) {
        point.y++;
    }

    void move_down(Point& point) {
        point.y--;
    }

    void move_right(Point& point) {
        point.x++;
    }

    void move_left(Point& point) {
        point.x--;
    }

    void move_up_right(Point& point) {
        move_up(point);
        move_right(point);
    }

    void move_up_left(Point& point) {
        move_up(point);
        move_left(point);
    }

    void move_down_right(Point& point) {
        move_down(point);
        move_right(point);
    }

    void move_down_left(Point& point) {
        move_down(point);
        move_left(point);
    }

    size_t get_distance(Point& p1, Point& p2) {
        const double dx = p1.x - p2.x;
        const double dy = p1.y - p2.y;
        const double sd = pow(dx, 2) + pow(dy, 2);
        const double distance = sqrt(sd);
        return floor(distance);
    }

    void move(Rope& rope, Direction dir) {
        switch (dir) {
            case Direction::UP: {
                move_up(rope.head);
            } break;
            case Direction::DOWN: {
                move_down(rope.head);
            } break;
            case Direction::LEFT: {
                move_left(rope.head);
            } break;
            case Direction::RIGHT: {
                move_right(rope.head);
            }
        }
        drag_tail(rope);
    }

    void drag_tail(Rope& rope) {
        for (size_t i = 0; i < rope.tail.size(); i++) {
            Point& p = rope.tail[i];
            Point front = i == 0 ? rope.head : rope.tail[i-1];

            if (get_distance(front, p) < 2) {
                continue;
            }

            move_tail(front, p);

            if (i == rope.tail.size()-1) {
                add_tail_loc(rope, p);
            }
        }
    }

    void move_tail(Point h, Point& t) {
        if (h.y > t.y && h.x > t.x) {
            move_up_right(t);
        } else if (h.y < t.y && h.x > t.x) {
            move_down_right(t);
        } else if (h.y < t.y && h.x < t.x) {
            move_down_left(t);
        } else if (h.y > t.y && h.x < t.x) {
            move_up_left(t);
        } else if (h.y > t.y) {
            move_up(t);
        } else if (h.y < t.y) {
            move_down(t);
        } else if (h.x > t.x) {
            move_right(t);
        } else {
            move_left(t);
        }
    }

    void handle_instruction(Rope& rope, Instruction instruction) {
        for (int i = 0; i < instruction.steps; i++) {
            move(rope, instruction.dir);
        }
    }

    // TODO: Be better with this
    // This shit is really annoying, not to mention error prone
    void add_tail_loc(Rope& rope, Point& loc) {
        rope.tail_locs.insert(loc.x*1000 + loc.y);
    }

    int part_one(std::vector<Instruction>& instructions) {
        Rope rope = create_rope(1);
        for (Instruction instruction : instructions) {
            handle_instruction(rope, instruction);
        }

        return rope.tail_locs.size();
    }

    int part_two(std::vector<Instruction>& instructions) {
        Rope rope = create_rope(9);
        for (Instruction instruction : instructions) {
            handle_instruction(rope, instruction);
        }

        return rope.tail_locs.size();
    }

    int solve(const std::string path_input) {
        std::vector<Instruction> instructions;

        if (!read_input(instructions, path_input)) {
            std::cout << "error reading input from " << path_input << std::endl;
            return 1;
        }

        std::cout << "year 2022 day 9" << std::endl;
        std::cout << "---------------" << std::endl;
        std::cout << "part one: " << part_one(instructions) << std::endl;
        std::cout << "part two: " << part_two(instructions) << std::endl;

        return 0;
    }

}
