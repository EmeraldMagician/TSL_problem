#pragma once
#include "common.hpp"
#include "unistd.h"

class Solver_2opt {
public:
    Solver_2opt(int n)
    {
        cities_n = n;
        Perm.resize(n);
        for (int i = 0; i < n; ++i) {
            Perm[i] = i;
        }
    }
    ~Solver_2opt() = default;

    clock_t solve(const std::vector<std::vector<double>>& Distances, const double& best_dist)
    {
        double local_dist = 3 * cities_n;
        double temp_dist;
        int i, j;
        bool optimal;
        clock_t start = clock();
        while (local_dist > best_dist + 1e-10){
            optimal = false;
            std::random_shuffle(Perm.begin(), Perm.end());
            while (!optimal){
                optimal = true;
                for (i = 0; i < cities_n; ++i)
                    for (j = i + 2; j < cities_n; ++j){
                        if (Distances[Perm[(i + cities_n - 1) % cities_n]][Perm[i]] +
                                Distances[Perm[(j + cities_n - 1) % cities_n]][Perm[j]] -
                                Distances[Perm[(i + cities_n - 1) % cities_n]][Perm[(j + cities_n - 1) % cities_n]] -
                                Distances[Perm[i]][Perm[j]] > 1e-10){
                            optimal = false;
                            std::reverse(Perm.begin() + i, Perm.begin() + j);
                            i = cities_n;
                            j = cities_n;
                        }
                    }
            }
            temp_dist = dist(Perm, Distances);
            if (temp_dist < local_dist - 1e-10)
                local_dist = temp_dist;
        }
        return clock() - start;
    }

private:
    int cities_n;
    std::vector<int> Perm;
};
