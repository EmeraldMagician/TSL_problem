#pragma once
#include "common.hpp"

class Solver_stupid {
public:
    Solver_stupid(int n)
    {
        cities_n = n;
        Perm.resize(n);
        for (int i = 0; i < n; ++i) {
            Perm[i] = i;
        }
    }
    ~Solver_stupid() = default;

    clock_t solve(const std::vector<std::vector<double>>& Distances, const double& best_dist)
    {
        double local_dist = 3 * cities_n;
        clock_t start = clock();
        int i;
        while (local_dist > best_dist + 1e-10) {
            i = rand() % cities_n;
            std::swap(Perm[i], Perm[(i + 1) % cities_n]);
            local_dist = dist(Perm, Distances);
        }
        return clock() - start;
    }

private:
    int cities_n;
    std::vector<int> Perm;
};
