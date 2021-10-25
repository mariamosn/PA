#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
#define NMAX 50005

// valoare mai mare decat orice distanta din graf
#define INF (1 << 30)

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // n = numar de noduri, m = numar de muchii
    int n, m;
    // adj[i] = lista de adiacenta a nodului i
    // perechea (j, w) semnifica muchie de la i la j de cost w
    vector<pair<int, int>> adj[NMAX];
    // nodul sursa
    int source;

    void read_input() {
        // ifstream fin("in");
        cin >> n >> m >> source;
        for (int i = 1, x, y, w; i <= m; i++) {
            cin >> x >> y >> w;
            adj[x].push_back({y, w});
        }
        // fin.close();
    }

    vector<int> get_result() {
        //
        // TODO: Gasiti distantele minime de la nodul source la celelalte noduri
        // folosind Bellman-Ford pe graful orientat cu n noduri, m arce stocat in adj.
        //     d[node] = costul minim / lungimea minima a unui drum de la source la nodul
        // node;
        //     d[source] = 0;
        //     d[node] = -1, daca nu se poate ajunge de la source la node.
        //
        // Atentie:
        // O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
        //     adj[x][i] == (y, w) - unde y este al i-lea vecin al lui x, iar (x, y) are cost w: (x, y, w)
        //
        // In cazul in care exista ciclu de cost negativ, returnati un vector gol:
        //     return {};
        //

        vector<int> d(n + 1, 0);

        if (!bellman(source, d))
            // cicu
            return {};

        return d;
    }

    bool bellman(int souce, vector<int>& d) {
        // Initializam vectorul de distante cu distante infinite.
        fill(d.begin(), d.end(), INF);

        // Setez sursa la distanta 0.
        d[source] = 0;

        // Construiesc un vector de muchii.
        vector<tuple<int, int, int>> edges;

        for (int x = 1; x <= n; ++x) {
            for (const auto& [y, w] : adj[x]) {
                edges.push_back({x, y, w});
            }
        }

        // Fac N - 1 relaxari.
        for (int i = 1; i <= n - 1; i++) {
            // Parcurg toate muchiile:
            for (const auto& [x, y, w] : edges) {
                // Incerc sa updatez distanta.
                if (d[y] > d[x] + w) {
                    d[y] = d[x] + w;
                }
            }
        }

        // Verific daca mai poate fi updatata distanta
        for (const auto& [x, y, w] : edges) {
            // Incerc sa updatez distanta.
            if (d[y] > d[x] + w) {
                // Am gasit un ciclu.
                return false;
            }
        }

        // Toate nodurile catre care distanta este inca INF nu pot fi atinse din
        // nodul source, deci le setam pe -1.
        for (int i = 1; i <= n; i++) {
            if (d[i] == INF) {
                d[i] = -1;
            }
        }

        return true;
    }

    void print_output(vector<int> result) {
        // ofstream fout("out");
        if (result.size() == 0) {
            cout << "Ciclu negativ!\n";
        } else {
            for (int i = 1; i <= n; i++) {
                cout << result[i] << ' ';
            }
            cout << '\n';
        }
        // fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
