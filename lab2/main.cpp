#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <chrono>

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

    auto xy_generator = []() {
        std::uniform_real_distribution<> dis(-10, 10);
        return std::pair<double, double>(dis(mt_generator), dis(mt_generator));
    };

    for (int i = 0; i < 20; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        auto best_sphere = brute_force(sphere_f, xy_generator, 1000000);
        auto stop = std::chrono::high_resolution_clock::now();

        std::cout << "best sphere x,y = " << best_sphere.first << ", " << best_sphere.second
                  << " | result: " << sphere_f(best_sphere)
                  << " | time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
                  << std::endl;
    }

    std::cout << "-----------------------" << std::endl;

    for (int i = 0; i < 20; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        auto best_booth = brute_force(booth_f, xy_generator, 1000000);
        auto stop = std::chrono::high_resolution_clock::now();

        std::cout << "best booth x,y = " << best_booth.first << ", " << best_booth.second
                  << " | result: " << booth_f(best_booth)
                  << " | time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
                  << std::endl;
    }

    std::cout << "-----------------------" << std::endl;

    for (int i = 0; i < 20; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        auto best_matyas = brute_force(matyas_f, xy_generator, 1000000);
        auto stop = std::chrono::high_resolution_clock::now();

        std::cout << "best matyas x,y = " << best_matyas.first << ", " << best_matyas.second
                  << " | result: " << matyas_f(best_matyas)
                  << " | time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
                  << std::endl;
    }

    return 0;
}