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
    // adj[x] = lista de adiacenta a nodului y
    // perechea (y, w) semnifica muchie de la x la y de cost w
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
        // folosind Dijkstra pe graful orientat cu n noduri, m arce stocat in adj.
        //     d[node] = costul minim / lungimea minima a unui drum de la source la nodul
        // node;
        //     d[source] = 0;
        //     d[node] = -1, daca nu se poate ajunge de la source la node.
        //
        // Atentie:
        // O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
        //     adj[x][i] == (y, w) - unde y este al i-lea vecin al lui x, iar (x, y) are cost w: (x, y, w)
        //

        vector<int> d(n + 1, 0);

        dijkstra(source, d);

        return d;
    }

    void dijkstra(int source, vector<int>& d) {
        // Initializam vectorul de distante cu distante infinite.
        fill(d.begin(), d.end(), INF); // https://en.cppreference.com/w/cpp/algorithm/fill

        // In loc de un priority_queue<> folosim set<>, cu elemente tupluri de
        // tipul (distanta pana la nod, nod). Setul tine elementele ordonate, deci
        // mereum in pq.begin() vom avea tuplul care ii corespunde nodului cu
        // distanta minima.
        set<pair<int, int>> pq;

        // Inseram nodul de plecare in coada si ii actualizam distanta.
        d[source] = 0;
        pq.insert({d[source], source});

        while (!pq.empty()) {
            // Scoatem top-ul.
            auto top = pq.begin();
            auto x = top->second;
            pq.erase(top);

            // Ii parcurgem toti vecinii.
            for (const auto& [y, w] : adj[x]) {
                // Se imbunatateste distanta?
                if (d[y] > d[x] + w) {
                    // Scoatem vechea pereche din set.
                    pq.erase({d[y], y});
                    // Actualizam distanta si inseram din nou in set.
                    d[y] = d[x] + w;
                    pq.insert({d[y], y});
                }
            }
        }

        // Toate nodurile catre care distanta este inca INF nu pot fi atinse din
        // nodul source, deci le setam pe -1.
        for (int i = 1; i <= n; i++) {
            if (d[i] == INF) {
                d[i] = -1;
            }
        }
    }

    void print_output(vector<int> result) {
        // ofstream fout("out");
        for (int i = 1; i <= n; i++) {
            cout << result[i] << " ";
        }
        cout << "\n";
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
