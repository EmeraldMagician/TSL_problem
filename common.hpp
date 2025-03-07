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
