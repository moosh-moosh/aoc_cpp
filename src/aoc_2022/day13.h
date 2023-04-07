#ifndef DAY13_H_
#define DAY13_H_

#include <cctype>
#include <iostream>
#include <string>
#include <vector>
namespace aoc2022day13 {

    enum class Alignment {
    LEFT,
    RIGHT,
    EQUAL
    };

    struct Value {
        bool is_int;
        bool is_divider = false;
        int int_val;
        std::vector<Value> values;
    };

    struct Pair {
        Value left, right;
    };

    struct Scanner {
        size_t pos, start;
        std::string source;
        std::vector<Value> values;

        Scanner(std::string str) {
            source = str;
            pos = 0;
            values.clear();
        }

        bool is_at_end() {
            return pos >= source.size();
        }

        char peek() {
            if (is_at_end()) {
                return '\0';
            }
            return source[pos+1];
        }

        char advance() {
            char ch = source[pos];
            pos++;
            return ch;
        }

        Value number() {
            int len = 1;
            while(std::isdigit(source[pos])) {
                advance();
                len++;
            }

            std::string res = source.substr(start, len);
            Value v;
            v.is_int = true;
            v.int_val = std::stoi(res);
            return v;
        }

        Value list() {
            Value v;
            v.is_int = false;
            while(!is_at_end()) {
                start = pos;
                char ch = advance();
                switch (ch) {
                    case '[': {
                        v.values.push_back(list());
                    } break;
                    case ']': {
                        return v;
                    } break;
                    default: {
                        if (std::isdigit(ch)) {
                            v.values.push_back(number());
                        }
                    }
                }
            }
            return v;
        }

        void scan() {
            while(!is_at_end()) {
                start = pos;
                char ch = advance();
                switch (ch) {
                    case '[': {
                        values.push_back(list());
                    } break;
                    case ']': {
                        advance();
                    }break;
                    default: {
                        if (std::isdigit(ch)) {
                            values.push_back(number());
                        } else {
                            advance();
                        }
                    } break;
                }
            }
        }
    };

    Alignment cmp_values(Value &left, Value &right);
    Alignment cmp_int_values(Value &left, Value &right);
    bool read_input(std::vector<Value> &values, const std::string str);
    int part_one(std::vector<Value> &values);
    int part_two(std::vector<Value> values);
    int solve(const std::string path_input);
}

#endif // DAY13_H_
