#include <bits/stdc++.h>
using namespace std;

// 配置参数
struct GAParams {
    int population_size = 100;
    int generations = 200;
    int dimension = 10;               // 解向量维度
    double lower_bound = -5.12;       // 搜索下界
    double upper_bound = 5.12;        // 搜索上界
    double crossover_rate = 0.9;      // 交叉概率（针对配对）
    double mutation_rate = 0.1;       // 每个基因的变异概率
    double mutation_stddev = 0.1;     // 高斯变异标准差
    int tournament_size = 3;          // 锦标赛选择规模
    bool use_elitism = true;
    int elitism_count = 1;
};

// 用于随机数
static std::mt19937 rng((unsigned) chrono::high_resolution_clock::now().time_since_epoch().count());

double rand_double(double a, double b) {
    uniform_real_distribution<double> dist(a, b);
    return dist(rng);
}

int rand_int(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist(rng);
}

// 个体结构
struct Individual {
    vector<double> genes;
    double fitness; // 适应度，越大越好
    double objective; // 原始目标值（这里是 Sphere 函数，越小越好）
};

// 示例目标函数：Sphere (求最小化 sum(x_i^2))
double objective_function(const vector<double>& x) {
    double s = 0.0;
    for (double v : x) s += v * v;
    return s;
}

// 将目标转换为适应度：适应度越大越好。这里使用 1/(1+obj) 的常见变换
double objective_to_fitness(double obj) {
    return 1.0 / (1.0 + obj);
}

// 初始化种群
vector<Individual> initialize_population(const GAParams& p) {
    vector<Individual> pop;
    pop.reserve(p.population_size);
    for (int i = 0; i < p.population_size; ++i) {
        Individual ind;
        ind.genes.resize(p.dimension);
        for (int d = 0; d < p.dimension; ++d) {
            ind.genes[d] = rand_double(p.lower_bound, p.upper_bound);
        }
        ind.objective = objective_function(ind.genes);
        ind.fitness = objective_to_fitness(ind.objective);
        pop.push_back(move(ind));
    }
    return pop;
}

// 锦标赛选择（返回个体索引）
int tournament_select(const vector<Individual>& pop, int tournament_size) {
    int best = rand_int(0, (int)pop.size() - 1);
    for (int i = 1; i < tournament_size; ++i) {
        int idx = rand_int(0, (int)pop.size() - 1);
        if (pop[idx].fitness > pop[best].fitness) best = idx;
    }
    return best;
}

// 算术混合交叉（对每个基因用随机alpha）
pair<Individual, Individual> crossover_arithmetic(const Individual& a, const Individual& b, const GAParams& p) {
    Individual c1 = a, c2 = b;
    for (int i = 0; i < p.dimension; ++i) {
        double alpha = rand_double(0.0, 1.0);
        c1.genes[i] = alpha * a.genes[i] + (1.0 - alpha) * b.genes[i];
        c2.genes[i] = alpha * b.genes[i] + (1.0 - alpha) * a.genes[i];
    }
    return {c1, c2};
}

// 变异：每个基因以 mutation_rate 概率加入高斯噪声，并裁剪到边界
void mutate(Individual& ind, const GAParams& p) {
    normal_distribution<double> gauss(0.0, p.mutation_stddev);
    for (int i = 0; i < p.dimension; ++i) {
        if (rand_double(0.0, 1.0) < p.mutation_rate) {
            ind.genes[i] += gauss(rng);
            if (ind.genes[i] < p.lower_bound) ind.genes[i] = p.lower_bound;
            if (ind.genes[i] > p.upper_bound) ind.genes[i] = p.upper_bound;
        }
    }
}

// 评估个体
void evaluate(Individual& ind) {
    ind.objective = objective_function(ind.genes);
    ind.fitness = objective_to_fitness(ind.objective);
}

// 运行一代进化，返回新种群
vector<Individual> evolve(const vector<Individual>& pop, const GAParams& p) {
    vector<Individual> newpop;
    newpop.reserve(p.population_size);

    // 精英保留：把最好的几个直接拷贝到下一代
    vector<int> indices(pop.size());
    iota(indices.begin(), indices.end(), 0);
    sort(indices.begin(), indices.end(), [&](int a, int b) {
        return pop[a].fitness > pop[b].fitness;
    });

    int start = 0;
    if (p.use_elitism) {
        for (int e = 0; e < p.elitism_count && e < (int)pop.size(); ++e) {
            newpop.push_back(pop[indices[e]]);
        }
        start = newpop.size();
    }

    // 生成新个体直到满足种群大小
    while ((int)newpop.size() < p.population_size) {
        // 选择父代
        int idx1 = tournament_select(pop, p.tournament_size);
        int idx2 = tournament_select(pop, p.tournament_size);

        const Individual& parent1 = pop[idx1];
        const Individual& parent2 = pop[idx2];

        // 交叉
        if (rand_double(0.0, 1.0) < p.crossover_rate) {
            auto children = crossover_arithmetic(parent1, parent2, p);
            // 变异并评估
            mutate(children.first, p);
            mutate(children.second, p);
            evaluate(children.first);
            evaluate(children.second);

            newpop.push_back(move(children.first));
            if ((int)newpop.size() < p.population_size)
                newpop.push_back(move(children.second));
        } else {
            // 不交叉，直接拷贝父代（但仍然可能变异）
            Individual c1 = parent1;
            Individual c2 = parent2;
            mutate(c1, p);
            mutate(c2, p);
            evaluate(c1);
            evaluate(c2);
            newpop.push_back(move(c1));
            if ((int)newpop.size() < p.population_size)
                newpop.push_back(move(c2));
        }
    }

    // 如果因为精英或偶数/奇数问题导致超出大小，裁剪
    if ((int)newpop.size() > p.population_size) newpop.resize(p.population_size);
    return newpop;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    GAParams params;
    // 可以在此调整参数，例如：
    params.population_size = 120;
    params.generations = 300;
    params.dimension = 30;           // 修改以测试不同维度
    params.mutation_stddev = 0.5;
    params.mutation_rate = 0.02;
    params.tournament_size = 3;
    params.elitism_count = 2;

    auto population = initialize_population(params);

    // 记录初代最优
    double best_obj = numeric_limits<double>::infinity();
    vector<double> best_sol;
    for (int gen = 0; gen <= params.generations; ++gen) {
        // 找到当前种群最优
        auto it = min_element(population.begin(), population.end(), [](const Individual& a, const Individual& b){
            return a.objective < b.objective;
        });
        if (it->objective < best_obj) {
            best_obj = it->objective;
            best_sol = it->genes;
        }

        if (gen % 10 == 0 || gen == params.generations) {
            cout << "Gen " << setw(4) << gen
                 << "  Best objective: " << scientific << setprecision(6) << it->objective
                 << "  Best fitness: " << setprecision(6) << it->fitness << '\n';
        }

        if (gen == params.generations) break;
        population = evolve(population, params);
    }

    cout << "\nFinal best objective: " << fixed << setprecision(10) << best_obj << '\n';
    cout << "Solution (first 10 dims):";
    for (int i = 0; i < min((int)best_sol.size(), 10); ++i) {
        cout << ' ' << setprecision(6) << best_sol[i];
    }
    cout << '\n';
    return 0;
}
