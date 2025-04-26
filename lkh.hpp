#pragma once
#include "common.hpp"
#include <fstream>

class Solver_lkh {
public:
    Solver_lkh(int n)
    {
        cities_n = n;
    }
    ~Solver_lkh() = default;

    clock_t solve(const std::vector<point_d>& Cities, const double& best_dist)
    {
        std::ofstream data;
        std::ofstream pars;
        data.open("/home/emeraldmagician/Downloads/LKH-2.0.10/data.tsp");
        data << "TYPE : TSP\n";
        data << "DIMENSION : " << cities_n << "\n";
        data << "EDGE_WEIGHT_TYPE : EUC_2D\n";
        data << "NODE_COORD_SECTION\n";
        for (int i = 0; i < cities_n; ++i){
            data << i + 1 << " " << Cities[i].x*1000000 << " " << Cities[i].y*1000000 << "\n";
        }
        data << "EOF";
        data.close();
        pars.open("/home/emeraldmagician/Downloads/LKH-2.0.10/pars.par");
        pars << "PROBLEM_FILE = /home/emeraldmagician/Downloads/LKH-2.0.10/data.tsp\n";
        pars << "TRACE_LEVEL = 0\n";
        pars << "OPTIMUM = " << ceil(best_dist*1000000) << "\n";
        pars.close();
        //std::cout << "test\n";
        auto start = std::chrono::steady_clock::now();
        clock_t result = system("/home/emeraldmagician/Downloads/LKH-2.0.10/./LKH /home/emeraldmagician/Downloads/LKH-2.0.10/pars.par > temp.txt");
        auto end = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()*0.001*CLOCKS_PER_SEC;
    }

private:
    int cities_n;
};
