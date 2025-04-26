#pragma once
#include "stupid.hpp"
#include "linear.hpp"
#include "dynamic.hpp"
#include "genetic.hpp"
#include "2opt.hpp"
#include "lkh.hpp"
#include "research.hpp"

enum mode {
    stupid = 1 << 0,
    linear = 1 << 1,
    genetic = 1 << 2,
    dynamic = 1 << 3,
    opt2 = 1 << 4,
    lkh = 1 << 5
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
        Results_local[lkh] = std::vector<double>(num_iter);
        Results[stupid] = std::vector<double>();
        Results[linear] = std::vector<double>();
        Results[genetic] = std::vector<double>();
        Results[dynamic] = std::vector<double>();
        Results[opt2] = std::vector<double>();
        Results[lkh] = std::vector<double>();
        Variations[stupid] = std::vector<double>();
        Variations[linear] = std::vector<double>();
        Variations[genetic] = std::vector<double>();
        Variations[dynamic] = std::vector<double>();
        Variations[opt2] = std::vector<double>();
        Variations[lkh] = std::vector<double>();

    }
    ~Tester() = default;

    void test(int N = 1)
    {
        double best_dist;
        int n = N;
        mode localmode;
        while (modes > 0) {
            for (int i = 0; i < num_iter; ++i) {
                generate_country(n, Distances, Cities);
                best_dist = 3 * n;
                // important that dynamic or linear is first
                if (modes & dynamic) {
                    std::cout << n << " " << i << " dyn_\r";
                    std::cout.flush();
                    Solver_dynamic dynamic_solver(n);
                    Results_local[dynamic][i] = dynamic_solver.solve(Distances, best_dist);
                }
                if (modes & linear) {
                    std::cout << n << " " << i << " lin_\r";
                    std::cout.flush();
                    Solver_linear linear_solver(n);
                    Results_local[linear][i] = linear_solver.solve(Distances, best_dist);
                }
                if (modes & stupid) {
                    if (modes & (linear | dynamic)) {
                        std::cout << n << " " << i << " stup\r";
                        std::cout.flush();
                        Solver_stupid stupid_solver(n);
                        Results_local[stupid][i] = stupid_solver.solve(Distances, best_dist);
                    } else
                        modes &= ~stupid;
                }
                if (modes & genetic) {
                    if (modes & (linear | dynamic)) {
                        std::cout << n << " " << i << " gen_\r";
                        std::cout.flush();
                        Solver_genetic genetic_solver(n, 60, 0.2);
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
                if (modes & lkh) {
                    if (modes & (linear | dynamic)) {
                        std::cout << n << " " << i << " lkh_\r";
                        std::cout.flush();
                        Solver_lkh lkh_solver(n);
                        Results_local[lkh][i] = lkh_solver.solve(Cities, best_dist);
                    } else
                        modes &= ~lkh;
                }
            }
            if (modes & dynamic) {
                localmode = dynamic;
                Results[localmode].push_back(std::accumulate(Results_local[localmode].begin(), Results_local[localmode].end(), 0.0) / num_iter);
                Variations[localmode].push_back(variance(Results_local[localmode], Results[localmode].back()));
                if (Results[localmode].back() > CLOCKS_PER_SEC * end_condition)
                    modes &= ~localmode;
            }
            if (modes & genetic) {
                localmode = genetic;
                Results[localmode].push_back(std::accumulate(Results_local[localmode].begin(), Results_local[localmode].end(), 0.0) / num_iter);
                Variations[localmode].push_back(variance(Results_local[localmode], Results[localmode].back()));
                if (Results[localmode].back() > CLOCKS_PER_SEC * end_condition)
                    modes &= ~localmode;
            }
            if (modes & linear) {
                localmode = linear;
                Results[localmode].push_back(std::accumulate(Results_local[localmode].begin(), Results_local[localmode].end(), 0.0) / num_iter);
                Variations[localmode].push_back(variance(Results_local[localmode], Results[localmode].back()));
                if (Results[localmode].back() > CLOCKS_PER_SEC * end_condition)
                    modes &= ~localmode;
            }
            if (modes & stupid) {
                localmode = stupid;
                Results[localmode].push_back(std::accumulate(Results_local[localmode].begin(), Results_local[localmode].end(), 0.0) / num_iter);
                Variations[localmode].push_back(variance(Results_local[localmode], Results[localmode].back()));
                if (Results[localmode].back() > CLOCKS_PER_SEC * end_condition)
                    modes &= ~localmode;
            }
            if (modes & opt2) {
                localmode = opt2;
                Results[localmode].push_back(std::accumulate(Results_local[localmode].begin(), Results_local[localmode].end(), 0.0) / num_iter);
                Variations[localmode].push_back(variance(Results_local[localmode], Results[localmode].back()));
                if (Results[localmode].back() > CLOCKS_PER_SEC * end_condition)
                    modes &= ~localmode;
            }
            if (modes & lkh) {
                localmode = lkh;
                Results[localmode].push_back(std::accumulate(Results_local[localmode].begin(), Results_local[localmode].end(), 0.0) / num_iter);
                Variations[localmode].push_back(variance(Results_local[localmode], Results[localmode].back()));
                if (Results[localmode].back() > CLOCKS_PER_SEC * end_condition)
                    modes &= ~localmode;
            }
            std::cout << n << ": ";
            if (Results[dynamic].size() < n - N + 1)
                std::cout << -1 << " ";
            else
                std::cout << Results[dynamic].back() / CLOCKS_PER_SEC << " ";
            if (Results[genetic].size() < n - N + 1)
                std::cout << -1 << " ";
            else
                std::cout << Results[genetic].back() / CLOCKS_PER_SEC << " ";
            if (Results[opt2].size() < n - N + 1)
                std::cout << -1 << " ";
            else
                std::cout << Results[opt2].back() / CLOCKS_PER_SEC << " ";
            if (Results[lkh].size() < n - N + 1)
                std::cout << -1 << " ";
            else
                std::cout << Results[lkh].back() / CLOCKS_PER_SEC << " ";
            if (Results[linear].size() < n - N + 1)
                std::cout << -1 << " ";
            else
                std::cout << Results[linear].back() / CLOCKS_PER_SEC << " ";
            if (Results[stupid].size() < n - N + 1)
                std::cout << -1 << " ";
            else
                std::cout << Results[stupid].back() / CLOCKS_PER_SEC << " ";
            std::cout << "\n";
            std::cout << "d: ";
            if (Results[dynamic].size() < n - N + 1)
                std::cout << -1 << " ";
            else
                std::cout << Variations[dynamic].back() / CLOCKS_PER_SEC << " ";
            if (Results[genetic].size() < n - N + 1)
                std::cout << -1 << " ";
            else
                std::cout << Variations[genetic].back() / CLOCKS_PER_SEC << " ";
            if (Results[opt2].size() < n - N + 1)
                std::cout << -1 << " ";
            else
                std::cout << Variations[opt2].back() / CLOCKS_PER_SEC << " ";
            if (Results[lkh].size() < n - N + 1)
                std::cout << -1 << " ";
            else
                std::cout << Variations[lkh].back() / CLOCKS_PER_SEC << " ";
            if (Results[linear].size() < n - N + 1)
                std::cout << -1 << " ";
            else
                std::cout << Variations[linear].back() / CLOCKS_PER_SEC << " ";
            if (Results[stupid].size() < n - N + 1)
                std::cout << -1 << " ";
            else
                std::cout << Variations[stupid].back() / CLOCKS_PER_SEC << " ";
            std::cout << "\n";
            ++n;
        }
    }

private:
    uint modes;
    uint num_iter;
    std::vector<std::vector<double>> Distances;
    std::vector<point_d> Cities;
    std::unordered_map<mode, std::vector<double>> Results_local;
    std::unordered_map<mode, std::vector<double>> Results;
    std::unordered_map<mode, std::vector<double>> Variations;
    static const uint modes_max = dynamic | genetic | linear | stupid | opt2 | lkh;
    static constexpr double end_condition = 1;
};
