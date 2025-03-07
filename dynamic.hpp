#pragma once
#include "common.hpp"

class Solver_dynamic {
public:
    Solver_dynamic(int n)
    {
        dp = std::vector<std::vector<double>>((ull)1 << n, std::vector<double>(n, -1));
        cities_n = n;
    }
    ~Solver_dynamic() = default;

    double cost(ull mask, int curr, const std::vector<std::vector<double>>& Distances)
    {
        if (mask == ((ull)1 << cities_n) - 1)
            return Distances[0][curr];
        if (dp[mask][curr] > -1)
            return dp[mask][curr];
        double ans = 3 * cities_n;
        for (int i = 0; i < cities_n; ++i) {
            if ((mask & ((ull)1 << i)) == 0) {
                ans = std::min(ans, Distances[curr][i] + cost(mask | ((ull)1 << i), i, Distances));
            }
        }
        return dp[mask][curr] = ans;
    }
    clock_t solve(const std::vector<std::vector<double>>& Distances, double& best_dist)
    {
        clock_t start = clock();
        for (ull i = 0; i < dp.size(); ++i)
            for (ull j = 0; j < dp[i].size(); ++j)
                dp[i][j] = -1;
        best_dist = cost(1, 0, Distances);
        return clock() - start;
    }

private:
    int cities_n;
    std::vector<std::vector<double>> dp;
};
