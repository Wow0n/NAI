#include <iostream>
#include <vector>
#include <functional>
#include <random>

auto brute_force = [](auto f, auto domain, int iterations) {
    auto current_p = domain();
    auto best_point = current_p;

    for (int i = 0; i < iterations; ++i) {
        if (f(current_p) < f(best_point)) {
            best_point = current_p;
        }
        current_p = domain();
    }

    return best_point;
};

std::random_device rd;
std::mt19937 mt_generator(rd());

int main() {
    auto sphere_f = [](std::pair<double, double> pair) { return pow(pair.first, 2) + pow(pair.second, 2); };

    auto booth_f = [](std::pair<double, double> pair) {
        return pow((pair.first + 2 * pair.second - 7), 2) + pow((2 * pair.first + pair.second - 5), 2);
    };

    auto matyas_f = [](std::pair<double, double> pair) {
        return 0.26 * (pow(pair.first, 2) + pow(pair.second, 2) - 0.48 * pair.first * pair.second);
    };

    auto xy_generator = [&]() {
        std::uniform_real_distribution<> dis(-10, 10);
        return std::pair<double, double> (dis(mt_generator), dis(mt_generator));
    };

    auto best_sphere = brute_force(sphere_f, xy_generator, 1000000);
    std::cout << "best sphere x,y = " << best_sphere.first << ", " << best_sphere.second << std::endl;

    auto best_booth = brute_force(booth_f, xy_generator, 1000000);
    std::cout << "best booth x,y = " << best_booth.first << ", " << best_booth.second << std::endl;

    auto best_matyas = brute_force(matyas_f, xy_generator, 1000000);
    std::cout << "best matyas x,y = " << best_matyas.first << ", " << best_matyas.second << std::endl;

    return 0;
}