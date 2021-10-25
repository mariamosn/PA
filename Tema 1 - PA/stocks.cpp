// Maria Moșneag 323CA

#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

#define NMAX 501

class Task {
 public:
    void solve() {
        print_output(get_result());
    }

 private:
    int n, b, l, dp[NMAX][NMAX] = {0}, prev[NMAX][NMAX] = {0};

    /*
    * funcția actualizează matricea folosită în cadrul tehnicii programării
    * dinamice în funcție de informațiile primite despre o nouă acțiune
    */
    void update_dp(int crt, int min, int max) {
        /*
        * matricea prev reține informația din dp dinaintea modificărilor
        * cauzate de noua acțiune introdusă
        */
        for (int i = 0; i <= l; i++) {
            for (int j = 0; j <= b; j++) {
                prev[i][j] = dp[i][j];
            }
        }

        /*
        * loss reprezintă pierderea potențială introdusă de acțiunea curentă,
        * iar profit, în mod analog, profitul
        */
        int loss = crt - min;
        int profit = max - crt;

        /*
        * actualizarea informației din dp, ținând cont și de acțiunea curentă;
        * dp[i][j] = profitul maxim ce poate fi obținut cu o pierdere potențială
        *            maximă i și un cost maxim j
        */
        for (int i = loss; i <= l; i++) {
            for (int j = crt; j <= b; j++) {
                int potential_new = prev[i - loss][j - crt] + profit;
                if (dp[i][j] < potential_new) {
                    dp[i][j] = potential_new;
                }
            }
        }
    }

    /*
    * funcția realizează atât citirea input-ului,
    * cât și determinarea rezultatului problemei
    */
    int get_result() {
        int crt, min, max;
        ifstream fin("stocks.in");
        fin >> n >> b >> l;
        for (int i = 0; i < n; ++i) {
            fin >> crt >> min >> max;
            update_dp(crt, min, max);
        }
        fin.close();
        return dp[l][b];
    }

    void print_output(int result) {
        ofstream fout("stocks.out");
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
