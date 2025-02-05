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

class Solver_stupid {
public:
    Solver_stupid(int n)
    {
        cities_n = n;
        Perm.resize(n);
        for (int i = 0; i < n; ++i) {
            Perm[i] = i;
        }
    }
    ~Solver_stupid() = default;

    clock_t solve(const std::vector<std::vector<double>>& Distances, const double& best_dist)
    {
        double local_dist = 3 * cities_n;
        clock_t start = clock();
        int i;
        while (local_dist > best_dist + 1e-10) {
            i = rand() % cities_n;
            std::swap(Perm[i], Perm[(i + 1) % cities_n]);
            local_dist = dist(Perm, Distances);
        }
        return clock() - start;
    }

private:
    int cities_n;
    std::vector<int> Perm;
};

class Solver_linear {
public:
    Solver_linear(int n)
    {
        cities_n = n;
        Perm.resize(n);
        for (int i = 0; i < n; ++i) {
            Perm[i] = i;
        }
    }
    ~Solver_linear() = default;

    clock_t solve(const std::vector<std::vector<double>>& Distances, double& best_dist)
    {
        best_dist = 3 * cities_n;
        double temp_dist;
        clock_t start = clock();
        clock_t timer = clock();
        do {
            temp_dist = dist(Perm, Distances);
            if (temp_dist < best_dist - 1e-10) {
                timer = clock() - start;
                best_dist = temp_dist;
            }
        } while (next_permutation(++Perm.begin(), Perm.end()));
        return timer;
    }

private:
    int cities_n;
    std::vector<int> Perm;
};

class Solver_genetic {
public:
    Solver_genetic(int n, int population_ = 100, double mutation_rate_ = 0.2)
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
    ~Solver_genetic() = default;

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
                index2 = choose_one();
                Pop_buff[i] = crossover(index1, index2);
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
        ull step = 0;
        ull hopeless_step = 0;
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
                index2 = choose_one();
                Pop_buff[i] = crossover(index1, index2);
                mutate(i);
            }
            Pop = Pop_buff;
            temp_dist = best_of_pop(Distances);
            //if (mutation_rate > 0.1)
            //    mutation_rate *= 0.99;
            //std::cout << mutation_rate << "\r";
            //std::cout.flush();
            ++step;
            ++hopeless_step;
            if (temp_dist < local_dist - 1e-10) {
                timer = clock() - start;
                local_dist = temp_dist;
                hopeless_step = 0;
            }
            if (step > 1000 && 2*hopeless_step > step){
                local_dist = 3 * cities_n;
                step = 0;
                hopeless_step = 0;
                std::cout << "A\n";
                for (int i = 0; i < Pop.size(); ++i) {
                    std::random_shuffle(Perm.begin(), Perm.end());
                    Pop[i] = Perm;
                }
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

enum mode {
    stupid = 1 << 0,
    linear = 1 << 1,
    genetic = 1 << 2,
    dynamic = 1 << 3,
    research = 1 << 4
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
        Results_local[research] = std::vector<double>(num_iter);
        Results[stupid] = std::vector<double>();
        Results[linear] = std::vector<double>();
        Results[genetic] = std::vector<double>();
        Results[dynamic] = std::vector<double>();
        Results[research] = std::vector<double>();

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
                    std::cout << n << " " << i << " d\r";
                    std::cout.flush();
                    Solver_dynamic dynamic_solver(n);
                    Results_local[dynamic][i] = dynamic_solver.solve(Distances, best_dist);
                }
                if (modes & linear) {
                    std::cout << n << " " << i << " l\r";
                    std::cout.flush();
                    Solver_linear linear_solver(n);
                    Results_local[linear][i] = linear_solver.solve(Distances, best_dist);
                }
                if (modes & stupid) {
                    if (modes & (linear | dynamic)) {
                        std::cout << n << " " << i << " s\r";
                        std::cout.flush();
                        Solver_stupid stupid_solver(n);
                        Results_local[stupid][i] = stupid_solver.solve(Distances, best_dist);
                    } else
                        modes &= ~stupid;
                }
                if (modes & genetic) {
                    if (modes & (linear | dynamic)) {
                        std::cout << n << " " << i << " g\r";
                        std::cout.flush();
                        Solver_genetic genetic_solver(n, 100, 0.2);
                        Results_local[genetic][i] = genetic_solver.solve(Distances, best_dist);
                    } else
                        modes &= ~genetic;
                }
                if (modes & research) {
                    if (modes & (linear | dynamic)) {
                        std::cout << n << " " << i << " r\r";
                        std::cout.flush();
                        Solver_research research_solver(n, 100, 0.2);
                        Results_local[research][i] = research_solver.solve(Distances, best_dist);
                    } else
                        modes &= ~research;
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
            if (modes & research) {
                Results[research].push_back(std::accumulate(Results_local[research].begin(), Results_local[research].end(), 0.0) / num_iter);
                if (Results[research].back() > CLOCKS_PER_SEC * end_condition)
                    modes &= ~research;
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
            if (Results[research].size() < n)
                std::cout << -1 << " ";
            else
                std::cout << Results[research].back() / CLOCKS_PER_SEC << " ";
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
    static const uint modes_max = dynamic | genetic | linear | stupid | research;
    static constexpr double end_condition = 1;
};
