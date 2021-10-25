#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
#define NMAX 200005

// Structura de date descrisa aici https://infoarena.ro/problema/disjoint.
class DisjointSet {
private:
    vector<int> parent, size;

public:
    // Se initializeaza n paduri
    DisjointSet(int n)
        : parent(n + 1)
        , size(n + 1) {
        for (int i = 1; i <= n; ++i) {
            // fiecare padure contine un nod initial
            parent[i] = i;
            size[i] = 1;
        }
    }

    // returneaza radacina arborelui din care face parte node
    int find_root(int node) {
        if (node == parent[node]) {
            return node;
        }
        return parent[node] = find_root(parent[node]);
    }

    // reuneste arborii lui root1 si root2 intr-un singur arbore
    void merge_forests(int root1, int root2) {
        if (size[root1] <= size[root2]) {
            size[root2] += size[root1];
            parent[root1] = root2;
        } else {
            size[root1] += size[root2];
            parent[root2] = root1;
        }
    }
};

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // n = numar de noduri, m = numar de muchii
    int n, m;

    // (x, y, w) - muchie de la x la y de cost w
    typedef tuple<int, int, int> edge;

    // edges = toate muchiile din graf
    vector<edge> edges;

    void read_input() {
        // ifstream fin("in");
        cin >> n >> m;
        for (int i = 1, x, y, w; i <= m; i++) {
            cin >> x >> y >> w;
            edges.push_back({x, y, w});
        }
        // fin.close();
    }

    int get_result() {
        //
        // TODO: Calculati costul minim al unui arbore de acoperire
        // folosind algoritmul lui Kruskal.
        //
        // Pentru a construi un tuple:
        // int a, b, c;
        // tuple<int, int, int> t = make_tuple(a, b, c);
        //
        // Pentru a accesa elementele dintr-un tuple, exista 2 variante:
        // tuple<int, int, int> t;
        // int a, b, c;
        // tie(a, b, c) = t;
        //
        // tuple<int, int, int> t;
        // int a = get<0>(t);
        // int b = get<1>(t);
        // int c = get<2>(t);
        //
        // Vi se da implementata structura de Paduri de multimi disjuncte.
        // Utilizare:
        // DisjointSet dj(n);
        // dj.find(x);
        // dj.reunion(x, y);
        //

        return kruskal(edges);
    }

    int kruskal(vector<edge>& edges) {
        // Sortam muchiile crescator dupa cost.
        std::sort(edges.begin(), edges.end(),
            [](const edge& e1, const edge& e2) { return std::get<2>(e1) < std::get<2>(e2); });

        // Initializam padurile.
        DisjointSet dj(n);

        // Costul APM-ului (MST) gasit.
        int cost_mst = 0;

        // Folosim muchiile in ordine crescatoare a costului.
        int used_edges = 0;
        for (const auto& edge : edges) {
            int x, y, c;
            std::tie(x, y, c) = edge;

            // aflam radacinile celor 2 arbori in care sunt x si y
            int rx = dj.find_root(x);
            int ry = dj.find_root(y);

            // daca sunt arbori diferiti
            if (rx != ry) {
                // reunim arborii
                dj.merge_forests(rx, ry);
                cost_mst += c;
                ++used_edges;

                if (used_edges == n - 1) {
                    break;
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
