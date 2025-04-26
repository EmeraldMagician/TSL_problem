#pragma once
#include "common.hpp"
#include "unistd.h"

class Solver_research {
public:
    Solver_research(int n, int population_ = 100, double mutation_rate_ = 0.2)
    {
        cities_n = n;
        mutation_rate = mutation_rate_;
        Pop.resize(population_);
        Pop_buff.resize(population_);
        Prob.resize(population_);
        Perm.resize(n);
        for (int i = 0; i < n; ++i)
            Perm[i] = i;
    }
    ~Solver_research() = default;

    void normalize_prob()
    {
        double sum = accumulate(Prob.begin(), Prob.end(), .0);
        for (double& i : Prob)
            i /= sum;
    }

    int choose_one()
    {
        double r = ((double)rand() + 1) / (double(RAND_MAX) + 2);
        int ind = 0;
        while (r > 0) {
            if (ind >= Prob.size())
                throw std::logic_error("choose_one error\n");
            r -= Prob[ind];
            ++ind;
        }
        return ind - 1;
    }

    std::vector<int> crossover(int index1, int index2)
    {
        std::vector<int> Perm_res = Pop[index1];
        int lim = rand() % cities_n;
        int ind = 0;
        while (lim < cities_n) {
            if (find(Perm_res.begin(), Perm_res.begin() + lim, Pop[index2][ind]) == Perm_res.begin() + lim) {
                Perm_res[lim] = Pop[index2][ind];
                ++lim;
                if (ind >= Pop[index2].size())
                    throw std::logic_error("crossover error\n");
            }
            ++ind;
        }
        return Perm_res;
    }

    void mutate(int index)
    {
        int i, j;
        for (int ind = 0; ind < cities_n; ++ind) {
            if (rand() < mutation_rate * RAND_MAX) {
                i = rand() % Pop_buff[index].size();
                j = (i + 1) % Pop_buff[index].size();
                std::swap(Pop_buff[index][i], Pop_buff[index][j]);
            }
        }
    }

    double best_of_pop(const std::vector<std::vector<double>>& Distances)
    {
        double z = cities_n * 3;
        double temp_dist;
        for (int i = 0; i < Pop.size(); ++i) {
            temp_dist = dist(Pop[i], Distances);
            if (temp_dist < z)
                z = temp_dist;
        }
        return z;
    }

    clock_t solve(const std::vector<std::vector<double>>& Distances, const double& best_dist)
    {
        double local_dist = 3 * cities_n;
        double temp_dist;
        int index1, index2;
        clock_t start = clock();
        clock_t timer = clock() - start;
        for (int i = 0; i < Pop.size(); ++i) {
            std::random_shuffle(Perm.begin(), Perm.end());
            Pop[i] = Perm;
        }
        while (local_dist > best_dist + 1e-10) {
            for (int i = 0; i < Pop.size(); ++i)
                Prob[i] = 1 / pow(dist(Pop[i], Distances), 8);
            normalize_prob();
            for (int i = 0; i < Pop.size(); ++i) {
                index1 = choose_one();
                //index2 = choose_one();
                //Pop_buff[i] = crossover(index1, index2);
                Pop_buff[i] = Pop[index1];
                mutate(i);
            }
            Pop = Pop_buff;
            temp_dist = best_of_pop(Distances);
            if (temp_dist < local_dist - 1e-10) {
                timer = clock() - start;
                local_dist = temp_dist;
            }
        }
        return timer;
    }

private:
    int cities_n;
    double mutation_rate;
    std::vector<std::vector<int>> Pop;
    std::vector<std::vector<int>> Pop_buff;
    std::vector<double> Prob;
    std::vector<int> Perm;
};
