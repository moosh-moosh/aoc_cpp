#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "hello aoc! args: ";

    for (int i = 0; i < argc; i++) {
        if (i > 0) {
            cout << ", ";
        }
        cout << argv[i];
    }
    cout << endl;
    return 0;
}
