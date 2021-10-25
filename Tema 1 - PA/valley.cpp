// Maria Moșneag 323CA

#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

#define NMAX 1000000

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    unsigned long long int n, v[NMAX], i, dp[2][NMAX], aux[NMAX];

    void read_input() {
        ifstream fin("valley.in");
        fin >> n;
        for (i = 0; i < n; ++i) {
            fin >> v[i];
            aux[i] = v[i];
        }
        fin.close();
    }

    unsigned long long int get_result() {
        unsigned long long int min_tot;
        dp[0][0] = dp[0][n - 1] = dp[1][0] = dp[1][n - 1] = 0;

        /*
        * calculez valorile din dp[0][], astfel încât dp[0][i] să reprezinte
        * numărul de ore necesare pentru ca secvența formată din vârfurile de la
        * 0 la i să fie prefix
        */
        for (i = 1; i < n - 1; i++) {
            if (aux[i] <= aux[i - 1]) {
                dp[0][i] = dp[0][i - 1];
            } else {
                dp[0][i] = dp[0][i - 1] + aux[i] - aux[i - 1];
                aux[i] = aux[i - 1];
            }
        }
        /*
        * suplimentar, verific ca vârful de pe poziția n - 2 să fie mai mic
        * decât cel de pe poziția n - 1, astfel încât să existe și un sufix
        */
        if (aux[n - 2] > aux[n - 1]) {
            dp[0][n - 2] += aux[n - 2] - aux[n - 1];
            aux[n - 2] = aux[n - 1];
        }

        /*
        * analog, calculez și dp[1][], de această dată dp[1][i] reprezentând în-
        * să numărul de ore necesar pentru a obține un sufix de la i la n - 1;
        * suplimentar, în paralel cu calculul dp[1][], la acest pas calculez și
        * numărul total de ore și determin minimul
        */
        for (i = n - 2; i > 0; i--) {
            /*
            * calculul lui dp[1][]
            */
            if (v[i] <= v[i + 1]) {
                dp[1][i] = dp[1][i + 1];
            } else {
                dp[1][i] = dp[1][i + 1] + v[i] - v[i + 1];
                v[i] = v[i + 1];
            }
            /*
            * asigurarea existenței unui prefix
            */
            if (i == 1 && v[1] > v[0]) {
                dp[1][1] += v[1] - v[0];
                v[1] = v[0];
            }

            /*
            * determinarea numărului total de ore
            */
            dp[0][i] += dp[1][i];

            if (aux[i] == v[i] && dp[1][i] != dp[1][i + 1]) {
                dp[0][i] -= (dp[1][i] - dp[1][i + 1]);
            } else if (aux[i] > v[i]) {
                dp[0][i] += (aux[i] - v[i]);
            } else if (aux[i] < v[i]) {
                dp[0][i] += (v[i] - aux[i]);
            }

            /*
            * obținerea rezultatului final
            */
            if (i == n - 2 || min_tot > dp[0][i]) {
                min_tot = dp[0][i];
            }
        }

        return min_tot;
    }

    void print_output(unsigned long long int result) {
        ofstream fout("valley.out");
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
