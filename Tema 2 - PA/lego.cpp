// Maria Moșneag 323CA

#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

#define NMAX 10
#define KMAX 50
#define TMAX 20

class Task {
 public:
    void solve() {
        read_input();
        get_result();
        print_output();
    }

 private:
    int n, k, t;
    bool searching = true;
    vector<int> best_pieces;
    int best_cnt;
    bool found = false;

    void read_input() {
        ifstream fin("lego.in");
        fin >> k >> n >> t;
        fin.close();
    }

    int get_cnt(vector<int> sol) {
        vector<int> sums(t * k + 1, 0);
        int max_sum = 1, x;
        for (auto i : sol) {
            sums[i] = 1;

            for (int j = 1; j <= max_sum; j++) {
                if (sums[j]) {
                    x = 1;
                    while (sums[j] + x <= t) {
                        if (sums[j + i * x] == 0 ||
                            sums[j + i * x] > sums[j] + x) {
                            sums[j + i * x] = sums[j] + x;
                        }
                        x++;
                    }
                    if (j + i * (x - 1) > max_sum) {
                        max_sum = j + i * (x - 1);
                    }
                }
            }
        }

        // determinarea lungimii maxime de dimensiuni consecutive
        int max_cnt = 0;
        int crt_cnt = 0;
        for (int i = 1; i <= max_sum; i++) {
            if (!sums[i]) {
                if (max_cnt < crt_cnt) {
                    max_cnt = crt_cnt;
                }
                crt_cnt = 0;
            } else {
                crt_cnt++;
            }
        }
        if (max_cnt < crt_cnt) {
            max_cnt = crt_cnt;
        }
        return max_cnt;
    }

    void back(int step, vector<int>& sol) {
        // am obținut un grup valid de piese
        if (step == n) {
            int cnt = get_cnt(sol);
            // verific dacă este cel mai bun de până acum
            if (!found || best_cnt < cnt) {
                found = true;
                best_cnt = cnt;
                best_pieces = sol;
            }
            return;
        }

        for (int i = sol[step - 1] + 1; i <= k; i++) {
            sol[step] = i;
            back(step + 1, sol);
        }
    }

    void get_result() {
        vector<int> solution(n);
        solution[0] = 1;
        back(1, solution);
    }

    void print_output() {
        ofstream fout("lego.out");
        fout << best_cnt << endl;
        for (auto i : best_pieces) {
            fout << i << ' ';
        }
        fout << endl;
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
