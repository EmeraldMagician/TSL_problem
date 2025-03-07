#pragma once
#include "common.hpp"

class Solver_linear {
public:
    Solver_linear(int n)
    {
        cities_n = n;
        Perm.resize(n);
        for (int i = 0; i < n; ++i) {
            Perm[i] = i;
        }
    }
    ~Solver_linear() = default;

    clock_t solve(const std::vector<std::vector<double>>& Distances, double& best_dist)
    {
        best_dist = 3 * cities_n;
        double temp_dist;
        clock_t start = clock();
        clock_t timer = clock();
        do {
            temp_dist = dist(Perm, Distances);
            if (temp_dist < best_dist - 1e-10) {
                timer = clock() - start;
                best_dist = temp_dist;
            }
        } while (next_permutation(++Perm.begin(), Perm.end()));
        return timer;
    }

private:
    int cities_n;
    std::vector<int> Perm;
};
