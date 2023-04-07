#include <algorithm>
#include <iostream>
#include <fstream>
#include <cctype>
#include <numeric>
#include "day13.h"

namespace aoc2022day13 {

    bool read_input(std::vector<Value> &values, const std::string path_input) {
        std::ifstream in(path_input);
        std::string line;

        if (!in) {
            return false;
        }

        while (std::getline(in, line)) {
            if (line.size() == 0) {
                continue;
            }
            Scanner s = Scanner(line);
            s.scan();
            values.push_back(s.values[0]);
        }
        in.close();

        return true;
    }

    Alignment cmp_values(Value &left, Value &right) {
        size_t pos = 0;
        while (true) {
            if (pos >= left.values.size() && pos >= right.values.size()) {
                return Alignment::EQUAL;
            }
            if (pos >= left.values.size()) {
                return Alignment::RIGHT;
            }
            if (pos >= right.values.size()) {
                return Alignment::LEFT;
            }
            Value l = left.values[pos];
            Value r = right.values[pos];
            pos++;
            if (l.is_int && r.is_int) {
                Alignment a = cmp_int_values(l, r);
                if (a == Alignment::EQUAL) {
                    continue;
                }
                return a;
            }
            if (l.is_int && !r.is_int) {
                Value val;
                val.is_int = false;
                val.values.push_back(l);
                Alignment a = cmp_values(val, r);
                if (a == Alignment::EQUAL) {
                    continue;
                }
                return a;
            }
            if (!l.is_int && r.is_int) {
                Value val;
                val.is_int = false;
                val.values.push_back(r);
                Alignment a = cmp_values(l, val);
                if (a == Alignment::EQUAL) {
                    continue;
                }
                return a;
            }
            Alignment a = cmp_values(l, r);
            if (a == Alignment::EQUAL) {
                continue;
            }
            return a;
        }
    }

    Alignment cmp_int_values(Value &left, Value &right) {
        if (left.int_val < right.int_val) {
            return Alignment::RIGHT;
        }
        if (left.int_val > right.int_val) {
            return Alignment::LEFT;
        }
        return Alignment::EQUAL;
    }

    int part_one(std::vector<Value> &values) {
        std::vector<int> indices;
        size_t pn = 1;
        for (size_t i = 0; i < values.size(); i += 2) {
            if (cmp_values(values[i], values[i+1]) == Alignment::RIGHT) {
                indices.push_back(pn);
            }
            pn++;
        }
        return std::accumulate(indices.begin(), indices.end(), 0);
    }

    int part_two(std::vector<Value> values) {
        Value x, y, z, x1, y1, z1;
        x.is_int = false;
        x.is_divider = true;
        y.is_int = false;
        z.is_int = true;
        z.int_val = 2;
        y.values.push_back(z);
        x.values.push_back(y);
        x1.is_int = false;
        x1.is_divider = true;
        y1.is_int = false;
        z1.is_int = true;
        z1.int_val = 6;
        y1.values.push_back(z1);
        x1.values.push_back(y1);
        values.push_back(x);
        values.push_back(x1);
        std::sort(values.begin(), values.end(), [](Value l, Value r) -> bool {return cmp_values(l, r) == Alignment::RIGHT;});
        std::vector<size_t> positions;
        for (size_t i = 0; i < values.size(); i++) {
            if (values[i].is_divider) {
                positions.push_back(i+1);
            }
        }
        return positions[0] * positions[1];
    }

    int solve(const std::string path_input) {
        std::vector<Value> values;

        if (!read_input(values, path_input)) {
            std::cout << "failed to read input from " << path_input << std::endl;
            return 1;
        }

        std::cout << "year 2022 day 13" << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout << "part one: " << part_one(values) << std::endl;
        std::cout << "part two: " << part_two(values) << std::endl;

        return 0;
    }

}
