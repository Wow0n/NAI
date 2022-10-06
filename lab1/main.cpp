#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

void lab1(function<double(vector<double>)> operation, vector<double> numbers) {
    cout << operation(numbers);
}

int main(int argc, char **argv) {
    vector<double> argNumbers;
    map<string, function<double(vector<double>)>> operations;

    operations["sin"] = [](vector<double> numbers) { return sin(numbers[0]); };
    operations["mod"] = [](vector<double> numbers) { return fmod(numbers[0], numbers[1]); };
    operations["add"] = [](vector<double> numbers) { return numbers[0] + numbers[1]; };

    try {
        char* operationName = argv[2];
        for (int i = 3; i < argc; i++) {
            argNumbers.push_back(stod(argv[i]));
        }

        lab1(operations.at(operationName), argNumbers);
    } catch (std::out_of_range aor) {
        return 1;
    }
    return 0;
}