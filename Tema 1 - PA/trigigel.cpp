// Maria Moșneag 323CA

#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

#define NMAX 1000000
#define MOD 1000000007
#define KMAX 4

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    long long n;

    void read_input() {
        ifstream fin("trigigel.in");
        fin >> n;
        fin.close();
    }

    /*
    * funcția înmulțește A cu B și pune rezultatul în C
    */
    void matrix_multiply(long long A[KMAX][KMAX],
                         long long B[KMAX][KMAX],
                         long long C[KMAX][KMAX]) {
        long long aux[KMAX][KMAX];
        for (int i = 0; i < KMAX; ++i) {
            for (int j = 0; j < KMAX; ++j) {
                long long s = 0;
                for (int k = 0; k < KMAX; ++k) {
                    s += ((A[i][k] % MOD) * (B[k][j] % MOD)) % MOD;
                }
                aux[i][j] = s % MOD;
            }
        }

        memcpy(C, aux, sizeof(aux));
    }

    /*
    * funcția calculează C^pow și pune rezultatul în R
    */
    void matrix_pow(long long C[KMAX][KMAX], long long pow,
                    long long R[KMAX][KMAX]) {
        long long res[KMAX][KMAX];
        for (int i = 0; i < KMAX; ++i) {
            for (int j = 0; j < KMAX; ++j) {
                if (i == j) {
                    res[i][j] = 1;
                } else {
                    res[i][j] = 0;
                }
            }
        }

        while (pow > 1) {
            if (pow % 2 == 0) {
                matrix_multiply(C, C, C);
                pow /= 2;
            } else {
                matrix_multiply(res, C, res);
                --pow;
            }
            cout << "kkkkkk\n";
        }

        matrix_multiply(C, res, R);
    }

    long long get_result() {
        long long i, j, res = 0;
        long long C[KMAX][KMAX] = {{0, 0, 0, -1},
                                    {1, 0, 0, 1},
                                    {0, 1, 0, -1},
                                    {0, 0, 1, 2}};
        long long S4[KMAX] = {1, 2, 3, 5};

        if (n <= 4) {
            for (i = n - 3; i < n; i++) {
                res += S4[i];
            }
            return res;
        }

        /*
        * calculează C^(n - 4)
        */
        matrix_pow(C, n - 4, C);

        /*
        * determinarea rezultatului prin calcularea sumei elementelor de pe po-
        * zițiile 1, 2 și 3 ale matricei 1 x 4 obținute ca rezultat al calculu-
        * lui S4 * C^(n - 4)
        */
        for (i = 1; i < 4; ++i) {
            for (j = 0; j < 4; ++j) {
                long long aux;
                if (C[j][i] > 0) {
                    aux = S4[j] * (C[j][i] % MOD);
                } else {
                    aux = S4[j] * C[j][i];
                }
                if (aux > 0) {
                    res = ((res % MOD) + (aux % MOD)) % MOD;
                } else {
                    aux = -aux;
                    res = ((res % MOD) - (aux % MOD) + MOD) % MOD;
                }
            }
        }

       return res;
    }

    void print_output(long long result) {
        ofstream fout("trigigel.out");
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
