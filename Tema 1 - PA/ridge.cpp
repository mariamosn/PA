// Maria Moșneag 323CA

#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

#define MAX_COST 1000000000000000

class Task {
 public:
    void solve() {
        print_output(get_result());
    }

 private:
    unsigned long long dp[3][2], h_pred;

    /*
    * funcția realizează update-ul matricei dp pe baza informațiilor despre un
    * munte;
    * dp[i][0] = costul pentru a avea o creastă de la primul munte până la cel
    *            precedent, considerând că din cel anterior tăiem i
    * dp[i][1] = analog cu dp[i][0], doar că pentru muntele curent
    */
    void update_dp(unsigned long long h_crt, unsigned long long c_crt) {
        unsigned long long i, j;

        /*
        * calcularea valorilor din dp[*][1] pe baza celor din dp[*][0]
        */
        for (i = 0; i < 3; ++i) {
            dp[i][1] = MAX_COST;
            for (j = 0; j < 3; j++) {
                if (h_crt - i != h_pred - j && dp[i][1] > dp[j][0]
                    && h_crt >= i) {
                    dp[i][1] = dp[j][0];
                }
            }
            dp[i][1] += c_crt * i;
        }

        /*
        * pregătirea lui dp pentru pasul următor, prin mutarea informației
        * obținute în dp[*][1] în dp[*][0]
        */
        for (i = 0; i < 3; ++i) {
            dp[i][0] = dp[i][1];
        }
        h_pred = h_crt;
    }

    /*
    * funcția citește input-ul și determină soluția problemei
    */
    unsigned long long get_result() {
        unsigned long long h_crt, c_crt, cost, n, i;
        ifstream fin("ridge.in");
        fin >> n;
        fin >> h_crt >> c_crt;

        if (n == 1) {
            return 0;
        }

        /*
        * inițializarea matricei dp pe baza informației despre primul munte
        */
        for (i = 0; i < 3; ++i) {
            if (h_crt >= i) {
                dp[i][0] = i * c_crt;
            } else {
                dp[i][0] = MAX_COST;
            }
        }
        h_pred = h_crt;

        /*
        * citirea informației despre ceilalți munți și actualizarea matricei dp
        */
        for (i = 2; i <= n; ++i) {
            fin >> h_crt >> c_crt;
            update_dp(h_crt, c_crt);
        }
        fin.close();

        /*
        * determinarea răspunsului pe baza dp
        */
        cost = dp[0][0];
        for (i = 1; i < 3; ++i) {
            if (dp[i][0] < cost) {
                cost = dp[i][1];
            }
        }

        return cost;
    }

    void print_output(unsigned long long result) {
        ofstream fout("ridge.out");
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

