#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <cmath>

auto brute_force = [](auto f, auto domain, int iterations, int a, int b) {
    auto current_p = domain(a, b);
    auto best_point = current_p;

    for (int i = 0; i < iterations; ++i) {
        if (f(current_p) < f(best_point)) {
            best_point = current_p;
        }
        current_p = domain(a, b);
    }

    return best_point;
};

auto hill_climbing = [](
        const std::function<double(std::vector<double>)> &f, std::vector<double> start_point,
        std::function<std::vector<std::vector<double>>(std::vector<double>)> get_close_points,
        int max_iterations) {

    std::vector<double> best_p = start_point;

    for (int iteration = 0; iteration < max_iterations; iteration++) {
        auto close_points = get_close_points(best_p);
        auto best_neighbour =
                *std::min_element(close_points.begin(), close_points.end(),
                                  [f](auto a, auto b) { return f(a) > f(b); });

        if (f(best_neighbour) < f(best_p))
            best_p = best_neighbour;
    }
    return best_p;
}

auto simulated_annealing() {

}

std::random_device rd;
std::mt19937 mt_generator(rd());

int main() {
//    (-5;5)
    auto ackley_f = [](std::pair<double, double> pair) {
        return -20.0 * exp(-0.2 * sqrt(0.5 * (pow(pair.first, 2) + pow(pair.second, 2)))) -
               exp(0.5 * (cos(2 * M_PI * pair.first) + cos(2 * M_PI * pair.second))) + exp(1) + 20;
    };

//    (-5;5)
    auto himmelblau_f = [](std::pair<double, double> pair) {
        return pow(pow(pair.first, 2) + pair.second + 11, 2) + pow(pair.first + pow(pair.second, 2) - 7, 2);
    };

//    (-10;10)
    auto holderTable_f = [](std::pair<double, double> pair) {
        return -std::abs(sin(pair.first) * cos(pair.second) *
                    exp(std::abs(1 - (sqrt(pow(pair.first, 2) + pow(pair.second, 2)) / M_PI))));
    };

    auto xy_generator = [](int a, int b) {
        std::uniform_real_distribution<> dis(a, b);
        return std::pair<double, double>(dis(mt_generator), dis(mt_generator));
    };

    std::cout << "----------------ackley------------------" << std::endl;

    auto ackley_burte = brute_force(ackley_f, xy_generator, 1000000, -5, 5);
    std::cout << "~brute_force~ (x,y) = " << ackley_burte.first << ", " << ackley_burte.second
              << " | result: " << ackley_f(ackley_burte)
              << std::endl;

    auto ackley_hill = hill_climbing(ackley_f, xy_generator, 1000000, -5, 5);
    std::cout << "~hill_climbing~ (x,y) = " << ackley_hill.first << ", " << ackley_hill.second
              << " | result: " << ackley_f(ackley_hill)
              << std::endl;

    auto ackley_annealing = simulated_annealing(ackley_f, xy_generator, 1000000, -5, 5);
    std::cout << "~simulated_annealing~ (x,y) = " << ackley_annealing.first << ", " << ackley_annealing.second
              << " | result: " << ackley_f(ackley_annealing)
              << std::endl;
//
//
//    std::cout << "----------------------------------------------" << std::endl;
//
//    auto best_booth = brute_force(booth_f, xy_generator, 1000000);
//    std::cout << "best booth x,y = " << best_booth.first << ", " << best_booth.second
//              << " | result: " <<
//              booth_f(best_booth)
//              <<
//              std::endl;
//
//    std::cout << "----------------------------------------------" << std::endl;
//
//    auto best_matyas = brute_force(matyas_f, xy_generator, 1000000);
//    std::cout << "best matyas x,y = " << best_matyas.first << ", " << best_matyas.second
//              << " | result: " << matyas_f(best_matyas)
//              << std::endl;
//
//    std::cout << "----------------------------------------------" << std::endl;

    return 0;
}