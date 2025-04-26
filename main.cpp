#include <iostream>
//#include "funcs.hpp"
#include "testing.hpp"

#include <ctime>
#include <random>

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(0));
    /*int n = 500;
    vector<point_d> Cities;
    vector<vector<double>> Distances;
    double best_dist = 0;
    generate_synthetic(n, Distances, Cities, best_dist);
    Solver_2opt solver_2opt(n);
    Solver_lkh solver_lkh(n);

    cout << 1.0*solver_2opt.solve(Distances, best_dist)/CLOCKS_PER_SEC << "\n";
    auto start = std::chrono::steady_clock::now();
    cout << 1.0*solver_lkh.solve(Cities, best_dist)/CLOCKS_PER_SEC << "\n";
    auto end = std::chrono::steady_clock::now();
    cout << 0.001*std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";*/

    /*vector<point_d> Cities;
    vector<vector<double>> Distances;
    vector<double> mutrat(100);
    vector<double> popul(100);
    double best_dist;
    int n = 13;
    Solver_dynamic solver(n);
    for (int mr = 1; mr <= 6; ++mr){
        Solver_genetic solver1(n, 100, 0.1*mr);
        for (int i = 0; i < 1000; ++i){
            cout << i << "\r";
            cout.flush();
            generate_country(n, Distances, Cities);
            solver.solve(Distances, best_dist);
            mutrat.push_back(solver1.solve(Distances, best_dist));
        }
        cout << 0.1*mr << " " << average(mutrat) << "\n";
        mutrat.clear();
    }
    cout << "\n";
    for (int po = 1; po <= 20; ++po){
        Solver_genetic solver1(n, po*10, 0.2);
        for (int i = 0; i < 1000; ++i){
            cout << i << "\r";
            cout.flush();
            generate_country(n, Distances, Cities);
            solver.solve(Distances, best_dist);
            popul.push_back(solver1.solve(Distances, best_dist));
        }
        cout << po*10 << " " << average(popul) << "\n";
    }*/


    Tester tester(dynamic | genetic);
    tester.test(3);
    return 0;
}
