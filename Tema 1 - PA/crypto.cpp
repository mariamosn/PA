// Maria Moșneag 323CA

#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

#define NMAX 1000000
#define PMAX 1000000000

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    unsigned long long n, b, v[NMAX][2], i;

    /*
    * funcția calculează costul upgrade-urilor necesare astfel încât
    * numărul monedelor minate într-o oră să fie p
    */
    unsigned long long get_cost(unsigned long long p) {
        unsigned long long s = 0;
        for (i = 0; i < n; i++) {
            if (p > v[i][0]) {
                s += (p - v[i][0]) * v[i][1];
            }
        }
        return s;
    }

    /*
    * funcția caută între valorile start și end numărul maxim de
    * monede ce pot fi minate pe oră după aplicarea unor upgrade-uri
    * care să se încadreze în bugetul b, iar dacă această valoare nu există,
    * rezultatul întors este 0
    */
    unsigned long long find_best_p(unsigned long long start,
                                    unsigned long long end) {
        if (start <= end) {
            unsigned long long mid = (start + end) / 2;
            unsigned long long ans = get_cost(mid);
            if (ans > b) {
                return find_best_p(start, mid - 1);
            } else if (ans == b) {
                return mid;
            } else {
                unsigned long long p2 = find_best_p(mid + 1, end);
                if (p2) {
                    return p2;
                } else {
                    return mid;
                }
            }
        }
        return 0;
    }

    /*
    * funcția citește input-ul și stochează perechile
    * (Pi, Ui) în matricea v: Pi = v[i][0], Ui = v[i][1]
    */
    void read_input() {
        ifstream fin("crypto.in");
        fin >> n >> b;
        for (i = 0; i < n; ++i) {
            fin >> v[i][0] >> v[i][1];
        }
        fin.close();
    }

    unsigned long long get_result() {
        return find_best_p(1, PMAX);
    }

    void print_output(unsigned long long result) {
        ofstream fout("crypto.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* task = new (std::nothrow) Task{};
    if (!task) {
        std::cerr << "new failed\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
