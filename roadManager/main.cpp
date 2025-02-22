#include <iostream>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include "Road.h"
#include "RoadSystem.h"

int main() {
    int m, n;
    cin >> m >> n;

    if (m < 0 || n <= 0) {
        cerr << "invalid input" << endl;
        return 1;
    }

    RoadSystem system(m);

    string command;
    try {
        for (int i = 0; i < n; ++i) {
            cin >> command;
            if (command == "a") {
                system.init(m);
            }
            else if (command == "b") {
                float h;
                int r;
                cin >> h >> r;
                system.addBridge(h, r);
            }
            else if (command == "c") {
                float height;
                cin >> height;
                system.whichRoad(height);
            }
            else if (command == "d") {
                int r;
                cin >> r;
                system.print(r);
            }
            else {
                throw runtime_error("invalid input");
            }
        }
    }
    catch (const exception& e) {
        cerr << "invalid input" << endl;
        return 1;
    }

    return 0;
}
