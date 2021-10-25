// Maria Moșneag 323CA

#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

#define NMAX 2052

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, m, x, y;
    char bridges[NMAX][NMAX];

    void read_input() {
        ifstream fin("poduri.in");
        fin >> n >> m;
        fin >> x >> y;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; j++) {
                fin >> bridges[i][j];
            }
        }
        fin.close();
    }

    int get_result() {
        int **d = (int **) calloc(NMAX, sizeof(int *));
        for (int i = 0; i < NMAX; i++) {
            d[i] = (int *) calloc(NMAX, sizeof(int));
        }
        queue<pair<int, int>> q;

        // poziția inițială a lui Gigel
        q.push({x, y});
        d[x][y] = 1;

        while (!q.empty()) {
            int x_crt = q.front().first;
            int y_crt = q.front().second;
            q.pop();

            if (bridges[x_crt][y_crt] == 'V' || bridges[x_crt][y_crt] == 'D') {
                int x_next, y_next = y_crt;

                // Nord
                x_next = x_crt - 1;
                if (x_next == 0) {
                    return d[x_crt][y_crt];
                }
                if (d[x_next][y_next] == 0) {
                    d[x_next][y_next] = d[x_crt][y_crt] + 1;
                    q.push({x_next, y_next});
                }

                // Sud
                x_next = x_crt + 1;
                if (x_next == n + 1) {
                    return d[x_crt][y_crt];
                }
                if (d[x_next][y_next] == 0) {
                    d[x_next][y_next] = d[x_crt][y_crt] + 1;
                    q.push({x_next, y_next});
                }
            }
            if (bridges[x_crt][y_crt] == 'O' || bridges[x_crt][y_crt] == 'D') {
                int x_next = x_crt, y_next;

                // Vest
                y_next = y_crt - 1;
                if (y_next == 0) {
                    return d[x_crt][y_crt];
                }
                if (d[x_next][y_next] == 0) {
                    d[x_next][y_next] = d[x_crt][y_crt] + 1;
                    q.push({x_next, y_next});
                }

                // Est
                y_next = y_crt + 1;
                if (y_next == m + 1) {
                    return d[x_crt][y_crt];
                }
                if (d[x_next][y_next] == 0) {
                    d[x_next][y_next] = d[x_crt][y_crt] + 1;
                    q.push({x_next, y_next});
                }
            }
        }
        return -1;
    }

    void print_output(int result) {
        ofstream fout("poduri.out");
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
