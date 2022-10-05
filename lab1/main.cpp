#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


int main(int argc, char **argv) {
    vector<string> argumenty;
    map<string, function<double(double, double)>> mapa;

    mapa["sin"] = [](vector<string> arguments) { cout << sin(arguments[0]); };
    mapa["mod"] = [](vector<string> arguments) { return fmod(x, y); };
    mapa["add"] = [](vector<string> arguments) { return x + y; };

    try {
        for (int i = 2; i < argc; i++) {
            argumenty.emplace_back(argv[i]);
        }

        auto selected_f = argumenty.at(0);

        lab1(selected_f, mapa.at(selected_f));
    } catch (std::out_of_range aor) {
        return 1;
    }
    return 0;
}