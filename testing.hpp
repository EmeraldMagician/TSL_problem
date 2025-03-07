#pragma once
#include "stupid.hpp"
#include "linear.hpp"
#include "dynamic.hpp"
#include "genetic.hpp"
#include "2opt.hpp"
#include "lk.hpp"

enum mode {
    stupid = 1 << 0,
    linear = 1 << 1,
    genetic = 1 << 2,
    dynamic = 1 << 3,
    opt2 = 1 << 4
};

class Tester {
public:
    Tester(uint modes_ = modes_max, uint num_iter_ = 1000)
    {
        modes = modes_;
        num_iter = num_iter_;
        Results_local[stupid] = std::vector<double>(num_iter);
        Results_local[linear] = std::vector<double>(num_iter);
        Results_local[genetic] = std::vector<double>(num_iter);
        Results_local[dynamic] = std::vector<double>(num_iter);
        Results_local[opt2] = std::vector<double>(num_iter);
        Results[stupid] = std::vector<double>();
        Results[linear] = std::vector<double>();
        Results[genetic] = std::vector<double>();
        Results[dynamic] = std::vector<double>();
        Results[opt2] = std::vector<double>();

    }
    ~Tester() = default;

    void generate_country(int n)
    {
        std::vector<point_d> Cities(n);
        Distances.resize(n);
        for (int i = 0; i < n; ++i) {
            Cities[i] = { (2.0 * rand() / RAND_MAX) - 1, (2.0 * rand() / RAND_MAX) - 1 };
            Distances[i].resize(n);
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                Distances[i][j] = dist(Cities[i], Cities[j]);
    }

    void test(int n = 1)
    {
        double best_dist;
        while (modes > 0) {
            for (int i = 0; i < num_iter; ++i) {
                generate_country(n);
                best_dist = 3 * n;
                // important that dynamic or linear is first
                if (modes & dynamic) {
                    std::cout << n << " " << i << " dynamic\r";
                    std::cout.flush();
                    Solver_dynamic dynamic_solver(n);
                    Results_local[dynamic][i] = dynamic_solver.solve(Distances, best_dist);
                }
                if (modes & linear) {
                    std::cout << n << " " << i << " linear\r";
                    std::cout.flush();
                    Solver_linear linear_solver(n);
                    Results_local[linear][i] = linear_solver.solve(Distances, best_dist);
                }
                if (modes & stupid) {
                    if (modes & (linear | dynamic)) {
                        std::cout << n << " " << i << " stupid\r";
                        std::cout.flush();
                        Solver_stupid stupid_solver(n);
                        Results_local[stupid][i] = stupid_solver.solve(Distances, best_dist);
                    } else
                        modes &= ~stupid;
                }
                if (modes & genetic) {
                    if (modes & (linear | dynamic)) {
                        std::cout << n << " " << i << " genetic\r";
                        std::cout.flush();
                        Solver_genetic genetic_solver(n, 100, 0.2);
                        Results_local[genetic][i] = genetic_solver.solve(Distances, best_dist);
                    } else
                        modes &= ~genetic;
                }
                if (modes & opt2) {
                    if (modes & (linear | dynamic)) {
                        std::cout << n << " " << i << " opt2\r";
                        std::cout.flush();
                        Solver_2opt opt2_solver(n);
                        Results_local[opt2][i] = opt2_solver.solve(Distances, best_dist);
                    } else
                        modes &= ~opt2;
                }
            }
            if (modes & dynamic) {
                Results[dynamic].push_back(std::accumulate(Results_local[dynamic].begin(), Results_local[dynamic].end(), 0.0) / num_iter);
                if (Results[dynamic].back() > CLOCKS_PER_SEC * end_condition)
                    modes &= ~dynamic;
            }
            if (modes & genetic) {
                Results[genetic].push_back(std::accumulate(Results_local[genetic].begin(), Results_local[genetic].end(), 0.0) / num_iter);
                if (Results[genetic].back() > CLOCKS_PER_SEC * end_condition)
                    modes &= ~genetic;
            }
            if (modes & linear) {
                Results[linear].push_back(std::accumulate(Results_local[linear].begin(), Results_local[linear].end(), 0.0) / num_iter);
                if (Results[linear].back() > CLOCKS_PER_SEC * end_condition)
                    modes &= ~linear;
            }
            if (modes & stupid) {
                Results[stupid].push_back(std::accumulate(Results_local[stupid].begin(), Results_local[stupid].end(), 0.0) / num_iter);
                if (Results[stupid].back() > CLOCKS_PER_SEC * end_condition)
                    modes &= ~stupid;
            }
            if (modes & opt2) {
                Results[opt2].push_back(std::accumulate(Results_local[opt2].begin(), Results_local[opt2].end(), 0.0) / num_iter);
                if (Results[opt2].back() > CLOCKS_PER_SEC * end_condition)
                    modes &= ~opt2;
            }
            std::cout << n << ": ";
            if (Results[dynamic].size() < n)
                std::cout << -1 << " ";
            else
                std::cout << Results[dynamic].back() / CLOCKS_PER_SEC << " ";
            if (Results[genetic].size() < n)
                std::cout << -1 << " ";
            else
                std::cout << Results[genetic].back() / CLOCKS_PER_SEC << " ";
            if (Results[opt2].size() < n)
                std::cout << -1 << " ";
            else
                std::cout << Results[opt2].back() / CLOCKS_PER_SEC << " ";
            if (Results[linear].size() < n)
                std::cout << -1 << " ";
            else
                std::cout << Results[linear].back() / CLOCKS_PER_SEC << " ";
            if (Results[stupid].size() < n)
                std::cout << -1 << " ";
            else
                std::cout << Results[stupid].back() / CLOCKS_PER_SEC << " ";
            std::cout << "\n";
            ++n;
        }
    }

private:
    uint modes;
    uint num_iter;
    std::vector<std::vector<double>> Distances;
    std::unordered_map<mode, std::vector<double>> Results_local;
    std::unordered_map<mode, std::vector<double>> Results;
    static const uint modes_max = dynamic | genetic | linear | stupid | opt2;
    static constexpr double end_condition = 1;
};
