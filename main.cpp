#include <iostream>
//#include "funcs.hpp"
#include "testing.hpp"

#include <ctime>
#include <random>

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(0));
    /*int n = 5;
    std::vector<point_d> Cities(n);
    vector<vector<double>> Distances(n);
    for (int i = 0; i < n; ++i) {
        Cities[i] = { (2.0 * rand() / RAND_MAX) - 1, (2.0 * rand() / RAND_MAX) - 1 };
        Distances[i].resize(n);
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            Distances[i][j] = dist(Cities[i], Cities[j]);
            cout << Distances[i][j] << ", ";
        }
        cout << "\n";
    }
    Solver_dynamic solver(n);
    Solver_linear solver1(n);
    double best_dist = 3 * n;
    solver.solve(Distances, best_dist);
    cout << best_dist << "\n";
    best_dist = 3 * n;
    solver1.solve(Distances, best_dist);
    cout << best_dist << "\n";*/

    Tester tester(genetic | dynamic | opt2);
    tester.test();
    //6.64592
    return 0;
}
