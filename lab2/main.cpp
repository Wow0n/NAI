#include <iostream>
#include <vector>
#include <functional>
#include <random>

/**
 * domain - generate domain points. Throws exception when all the points were returned
 */
auto brute_force = [](auto f, auto domain) {
    auto current_p = domain();
    auto best_point = current_p;

    try {
        while (true) {
            if (f(current_p) < f(best_point)) {
                best_point = current_p;
            }
            current_p = domain();
        }
    } catch (std::exception &e) {
    }

    return best_point;
};

using domain_t = std::vector<double>;
std::random_device rd;
std::mt19937 mt_generator(rd());

int main() {
    auto sphere_f = [](double x) { return x * x; };

    auto booth_f = [](double x, double y) {
        return pow((x + 2 * y - 7), 2) + pow((2 * x + y - 5), 2);
    };

    auto matyas_f = [](double x, double y) {
        return 0.26 * (pow(x, 2) + pow(y, 2) - 0.48 * x * y);
    };

    auto x_generator = []() {
        return std::uniform_real_distribution<> (-10, 10);
    };

    auto xy_generator = []() {
        return std::pair(std::uniform_real_distribution<> (-10, 10), std::uniform_int_distribution<int> (-10, 10));
    };

    auto best_point = brute_force(sphere_f, x_generator);
    std::cout << "best x = " << best_point << std::endl;

    return 0;
}