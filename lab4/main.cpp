#include <iostream>
#include <vector>
#include <functional>
#include <random>

std::random_device rd;
std::mt19937 mt_generator(rd());

using namespace std;

using chromosome_t = std::vector<int>;
using population_t = std::vector<chromosome_t>;

auto genetic_algorithm = [](
        auto initial_population, auto fitness, auto term_condition,
        auto selection, double p_crossover,
        auto crossover, double p_mutation, auto mutation) {

    uniform_real_distribution<double> uniform(0.0, 1.0);
    auto population = initial_population;
    vector<double> population_fit = fitness(population);

    while (!term_condition(population, population_fit)) {
        auto parents_indexes = selection(population_fit);
        decltype(population) new_population;

        for (int i = 0; i < parents_indexes.size(); i += 2) {
            decltype(initial_population) offspring = {population[i], population[i + 1]};
            if (uniform(mt_generator) < p_crossover) {
                offspring = crossover(offspring);
            }
            for (auto chromosome: offspring) new_population.push_back(chromosome);
        }

        for (auto &chromosome: new_population) {
            chromosome = mutation(chromosome, p_mutation);
        }

        population = new_population;
        population_fit = fitness(population);
    }
    return population;
};

std::vector<int> selection_empty(std::vector<double> fitnesses) {
    return {};
}

std::vector<chromosome_t> crossover_empty(std::vector<chromosome_t> parents) {
    return parents;
}

chromosome_t mutation_empty(chromosome_t parents, double p_mutation) {
    return parents;
}

population_t generate_population(int size) {
    population_t pop;

    for (int i = 0; i < size; ++i) {
        chromosome_t ch;

        for (int j = 0; j < size; ++j) {
//            generować w dziedzinie, później przeliczyć na bin i wrzucic do pary
            uniform_int_distribution<int> uni(0, 1);
            ch.push_back(uni(mt_generator));
        }
        pop.push_back(ch);
    }

    return pop;
}

pair<double, double> decode(chromosome_t chromosome) {
    double x = 0.0;
    double y = 0.0;

    for (int i = 1; i < chromosome.size() / 2; i++) {
        x = x * 2 + chromosome[i];
    }

    for (int i = (chromosome.size() / 2) + 1; i < chromosome.size(); i++) {
        y = y * 2 + chromosome[i];
    }

    if (chromosome[0] == 0) {
        x = 1 / x * -5;
    } else {
        x = -1 / x * -5;
    }

    if (chromosome[chromosome.size() / 2] == 0) {
        y = 1 / y * -5;
    } else {
        y = -1 / y * -5;
    }

    return {x, y};
}

// <-5;5>
auto ackley_f = [](pair<double, double> pair) {
    return -20 * exp(-0.2 * sqrt(0.5 * (pow(pair.first, 2) + pow(pair.second, 2)))) -
           exp(0.5 * (cos(2 * M_PI * pair.first) + cos(2 * M_PI * pair.second))) + exp(1) + 20;
};

double fitness_f(chromosome_t chromosome) {
    return 1.0 / (1.0 + abs(ackley_f(decode(chromosome))));
}

int main() {
    population_t population = generate_population(100 + (22432 % 10) * 2);

    for (auto &chromosome: population) {
        auto decoded = decode(chromosome);
        cout << decoded.first << ", " << decoded.second << endl;
    }

//    auto result = genetic_algorithm(population,
//                                    fintess_function,
//                                    [](auto a, auto b) { return true; },
//                                    selection_empty, 1.0,
//                                    crossover_empty,
//                                    0.01, mutation_empty);
//    for (chromosome_t chromosome: result) {
//        cout << "[";
//        for (int p: chromosome) {
//            cout << p;
//        }
//        cout << "] ";
//    }
//    cout << endl;
//    return 0;
}