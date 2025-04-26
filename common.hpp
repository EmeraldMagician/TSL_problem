#pragma once

#include <algorithm>
#include <bitset>
#include <cmath>
#include <ctime>
#include <deque>
#include <iostream>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <stack>
#include <set>
#include <cassert>
#include <unistd.h>
#include <chrono>

typedef unsigned long long ull;

struct point_d {
    double x;
    double y;
};

double sqr(double a) { return a * a; }

double dist(const std::vector<int>& Perm, const std::vector<std::vector<double>>& Distances)
{
    double z = 0;
    for (int i = 0; i < Perm.size(); ++i)
        z += Distances[Perm[i]][Perm[(i + 1) % Perm.size()]];
    return z;
}

double dist(point_d p1, point_d p2)
{
    return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}

void print(std::vector<int>& Perm){
    for (int i:Perm) std::cout << i << " ";
    std::cout << "\n";
}

void generate_country(int n, std::vector<std::vector<double>> &Distances, std::vector<point_d> &Cities)
{
    Cities.resize(n);
    Distances.resize(n);
    for (int i = 0; i < n; ++i) {
        Cities[i] = { (2.0 * rand() / RAND_MAX) - 1, (2.0 * rand() / RAND_MAX) - 1 };
        Distances[i].resize(n);
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            Distances[i][j] = dist(Cities[i], Cities[j]);
}

void generate_synthetic(int n, std::vector<std::vector<double>> &Distances, std::vector<point_d> &Cities, double& best_dist){
    if (n < 3)
        throw std::logic_error("synthetic generation called with <3 cities");
    Cities.resize(n);
    Distances.resize(n);
    int side = static_cast<long long int>(rand())*((n - 3)/2)/RAND_MAX;
    double baseangle = M_PI/(2*(n - 2 - 2*side));
    double step_lin = 2.0/(side + 1);
    Cities[0] = {-1, -1};
    Cities[1] = {-1, 1};
    Cities[2] = {1, -1};
    for (int i = 1; i <= side; ++i)
        Cities[2 + i] = {-1 + i*step_lin, -1};
    for (int i = 1; i <= side; ++i)
        Cities[2 + side + i] = {-1, -1 + i*step_lin};
    for (int i = 1; i <= n - 3 - 2*side; ++i){
        Cities[2 + 2*side + i] = {1 - 2*cos(i*baseangle), 1 - 2*sin(i*baseangle)};
    }
    for (int i = 0; i < n; ++i) {
        Distances[i].resize(n);
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            Distances[i][j] = dist(Cities[i], Cities[j]);
    best_dist = 4 + 2*sqrt(2 - 2*cos(baseangle))*(n - 2 - 2*side);
}

//i1-j1 intersect with i2-j2
bool intersect(int i1, int j1, int i2, int j2, const std::vector<std::vector<double>>& D){
    return D[i1][j1] + D[i2][j2] > D[i1][i2] + D[j1][j2] &&
           D[i1][j1] + D[i2][j2] > D[i1][j2] + D[j1][i2];
}

double variance(const std::vector<double>& Data, double average){
    double z = 0;
    for (double i:Data){
        z += sqr(1.0*(i - average)/CLOCKS_PER_SEC);
    }
    return z/Data.size();
}

double average(const std::vector<double>& Data){
    double z = 0;
    for (double i:Data){
        z += i/CLOCKS_PER_SEC;
    }
    return z/Data.size();
}
