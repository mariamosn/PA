#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
#define NMAX 200005

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

    // adj[i] = lista de adiacenta a lui i
    // (j, w) - exista muchie de la i la j de cost w
    vector<pair<int, int>> adj[NMAX];

    void read_input() {
        // ifstream fin("in");
        cin >> n >> m;
        for (int i = 1, x, y, w; i <= m; i++) {
            cin >> x >> y >> w;
            adj[x].push_back({y, w});
            adj[y].push_back({x, w});
        }
        // fin.close();
    }

    int get_result() {
        //
        // TODO: Calculati costul minim al unui arbore de acoperire
        // folosind algoritmul lui Prim.
        //
        return prim();
    }

    // cautam un APM pornind dintr-un nod oarecare (ex. 1)
    int prim(int source = 1) {
        // d[i] = distanta nodului i fata de APM-ul curent (cel ma apropiat nod din APM)
        // d[i] in aceasta problema va fi mereu egal cu costul unei muchii
        // Initializam vectorul de distante cu distante infinite.
        std::vector<int> d(n + 1, INF);
        // Initializam vectorul de parinti cu 0.
        std::vector<int> p(n + 1, 0);
        std::vector<int> used(n + 1, 0);

        // In loc de un priority_queue<> folosim set<>, cu elemente tupluri de
        // tipul (distanta pana la nod, nod). Setul tine elementele ordonate, deci
        // mereum in pq.begin() vom avea tuplul care ii corespunde nodului cu
        // distanta minima.
        std::set<std::pair<int, int>> pq;

        // Inseram nodul de plecare in coada si ii actualizam distanta.
        d[source] = 0;
        p[source] = 0;
        pq.insert({d[source], source});

        // Costul APM-ului (MST) gasit.
        int cost_mst = 0;

        // adaugam fix n noduri la arbore
        for (int i = 1; i <= n; ++i) {
            int x;

            do {
                // Scoatem top-ul.
                auto top = pq.begin();
                x = top->second;
                pq.erase(top);
            } while (used[x]);

            // adaug muchia x - p[x]
            cost_mst += d[x];
            used[x] = 1;

            // Ii parcurgem toti vecinii.
            for (const auto& yc : adj[x]) {
                int y = yc.first;
                int c = yc.second;

                // Se imbunatateste distanta?
                if (!used[y] && c < d[y]) {
                    // Scoatem vechea pereche din set.
                    pq.erase({d[y], y});
                    // Actualizam distanta si inseram din nou in set.
                    d[y] = c;
                    p[y] = x;
                    pq.insert({d[y], y});
                }
            }
        }

        return cost_mst;
    }

    void print_output(int result) {
        // ofstream fout("out");
        cout << result << "\n";
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
