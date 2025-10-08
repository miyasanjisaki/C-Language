#include <bits/stdc++.h>
using namespace std;

// ���ò���
struct GAParams {
    int population_size = 100;
    int generations = 200;
    int dimension = 10;               // ������ά��
    double lower_bound = -5.12;       // �����½�
    double upper_bound = 5.12;        // �����Ͻ�
    double crossover_rate = 0.9;      // ������ʣ������ԣ�
    double mutation_rate = 0.1;       // ÿ������ı������
    double mutation_stddev = 0.1;     // ��˹�����׼��
    int tournament_size = 3;          // ������ѡ���ģ
    bool use_elitism = true;
    int elitism_count = 1;
};

// ���������
static std::mt19937 rng((unsigned) chrono::high_resolution_clock::now().time_since_epoch().count());

double rand_double(double a, double b) {
    uniform_real_distribution<double> dist(a, b);
    return dist(rng);
}

int rand_int(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist(rng);
}

// ����ṹ
struct Individual {
    vector<double> genes;
    double fitness; // ��Ӧ�ȣ�Խ��Խ��
    double objective; // ԭʼĿ��ֵ�������� Sphere ������ԽСԽ�ã�
};

// ʾ��Ŀ�꺯����Sphere (����С�� sum(x_i^2))
double objective_function(const vector<double>& x) {
    double s = 0.0;
    for (double v : x) s += v * v;
    return s;
}

// ��Ŀ��ת��Ϊ��Ӧ�ȣ���Ӧ��Խ��Խ�á�����ʹ�� 1/(1+obj) �ĳ����任
double objective_to_fitness(double obj) {
    return 1.0 / (1.0 + obj);
}

// ��ʼ����Ⱥ
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

// ������ѡ�񣨷��ظ���������
int tournament_select(const vector<Individual>& pop, int tournament_size) {
    int best = rand_int(0, (int)pop.size() - 1);
    for (int i = 1; i < tournament_size; ++i) {
        int idx = rand_int(0, (int)pop.size() - 1);
        if (pop[idx].fitness > pop[best].fitness) best = idx;
    }
    return best;
}

// ������Ͻ��棨��ÿ�����������alpha��
pair<Individual, Individual> crossover_arithmetic(const Individual& a, const Individual& b, const GAParams& p) {
    Individual c1 = a, c2 = b;
    for (int i = 0; i < p.dimension; ++i) {
        double alpha = rand_double(0.0, 1.0);
        c1.genes[i] = alpha * a.genes[i] + (1.0 - alpha) * b.genes[i];
        c2.genes[i] = alpha * b.genes[i] + (1.0 - alpha) * a.genes[i];
    }
    return {c1, c2};
}

// ���죺ÿ�������� mutation_rate ���ʼ����˹���������ü����߽�
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

// ��������
void evaluate(Individual& ind) {
    ind.objective = objective_function(ind.genes);
    ind.fitness = objective_to_fitness(ind.objective);
}

// ����һ����������������Ⱥ
vector<Individual> evolve(const vector<Individual>& pop, const GAParams& p) {
    vector<Individual> newpop;
    newpop.reserve(p.population_size);

    // ��Ӣ����������õļ���ֱ�ӿ�������һ��
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

    // �����¸���ֱ��������Ⱥ��С
    while ((int)newpop.size() < p.population_size) {
        // ѡ�񸸴�
        int idx1 = tournament_select(pop, p.tournament_size);
        int idx2 = tournament_select(pop, p.tournament_size);

        const Individual& parent1 = pop[idx1];
        const Individual& parent2 = pop[idx2];

        // ����
        if (rand_double(0.0, 1.0) < p.crossover_rate) {
            auto children = crossover_arithmetic(parent1, parent2, p);
            // ���첢����
            mutate(children.first, p);
            mutate(children.second, p);
            evaluate(children.first);
            evaluate(children.second);

            newpop.push_back(move(children.first));
            if ((int)newpop.size() < p.population_size)
                newpop.push_back(move(children.second));
        } else {
            // �����棬ֱ�ӿ�������������Ȼ���ܱ��죩
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

    // �����Ϊ��Ӣ��ż��/�������⵼�³�����С���ü�
    if ((int)newpop.size() > p.population_size) newpop.resize(p.population_size);
    return newpop;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    GAParams params;
    // �����ڴ˵������������磺
    params.population_size = 120;
    params.generations = 300;
    params.dimension = 30;           // �޸��Բ��Բ�ͬά��
    params.mutation_stddev = 0.5;
    params.mutation_rate = 0.02;
    params.tournament_size = 3;
    params.elitism_count = 2;

    auto population = initialize_population(params);

    // ��¼��������
    double best_obj = numeric_limits<double>::infinity();
    vector<double> best_sol;
    for (int gen = 0; gen <= params.generations; ++gen) {
        // �ҵ���ǰ��Ⱥ����
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
