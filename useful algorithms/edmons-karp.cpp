#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
#define NMAX 1005

// valoare mai mare decat max_flow
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
    vector<int> adj[NMAX];

    // cap[i][j] = capacitatea arcului i -> j
    int cap[NMAX][NMAX];

    // flow[i][j] = fluxul curent pe arcul i->j
    // ATENTIE! Mereu vom avea flow[i][j] = -flow[j][i]!
    int flow[NMAX][NMAX];

    // p[i] = parintele nodului i in parcurgerea BFS pornita din source
    int p[NMAX];

    void read_input() {
        // ifstream fin("in");
        cin >> n >> m;
        memset(cap, 0, sizeof cap);
        for (int i = 1, x, y, c; i <= m; i++) {
            // x -> y de capacitate c
            cin >> x >> y >> c;
            adj[x].push_back(y);
            adj[y].push_back(x);

            // Presupunem existenta mai multor arce x -> y cu capacitati c1, c2, ...
            // Comprimam intr-un singur arc x -> y cu capacitate
            // cap[x][y] = c1 + c2 + ...
            cap[x][y] += c;
        }
        // fin.close();
    }

    int get_result() {
        //
        // TODO: Calculati fluxul maxim pe graful orientat dat.
        // Sursa este nodul 1.
        // Destinatia este nodul n.
        //
        // In adj este stocat graful neorientat obtinut dupa ce se elimina orientarea
        // arcelor, iar in cap sunt stocate capacitatile arcelor.
        // De exemplu, un arc (x, y) de capacitate c va fi tinut astfel:
        // cap[x][y] = c, adj[x] contine y, adj[y] contine x.
        //
        return get_maxflow(1, n);
    }

    int get_maxflow(int source, int sink) {
        // Initial nu exista flux in retea.
        int max_flow = 0;
        memset(flow, 0, sizeof(flow));

        // Cat timp am un drum de ameliorare de la source la sink
        while (bfs(source, sink)) {
            // Drumul se poate deduce din vectorul de parinti p[]
            // Parcurg drumul: d = sink <- x <- ... <- source
            // (de la sink la source, urc din parinte in parinte)
            // min_flow = min(cap[ parent ][ node ] - flow[ parent ][ node ])
            // unde node <- parent este o muchie de pe drumul d
            int min_flow = INF;
            for (int node = sink; node != source; node = p[node]) {
                int available_flow = cap[ p[node] ][node] - flow[ p[node] ][node];
                min_flow = min(min_flow, available_flow);
            }

            // DACA se poate pompa flux pe drum
            if (min_flow >= 1) {
                // pompam fluxul
                max_flow += min_flow;

                // actualizez drumul
                for (int node = sink; node != source; node = p[node]) {
                    flow[ p[node] ][node] += min_flow; // adaug fluxul pe muchia de pe drum
                    flow[node][ p[node] ] -= min_flow; // scad  fluxul in sens invers
                }
            }
        }

        return max_flow;
    }

    // Se realizeaza o parcugere BFS de la source la sink.
    // Se incearca unui drum de ameliorare.
    // Se poate merge pe un arc i->j doar daca capacitatea reziduala este strict
    // pozitiva
    // a.k.a. cap[i][j] - flow[i][j] > 0, pentru arcul i->j
    //         (muchia i->j nu e saturata)
    bool bfs(int source, int sink) {
        queue<int> q;

        // initializare vector parinti din BFS
        for (int i = 1; i <= n; ++i) {
            p[i] = -1; // nimeni nu are parinte
        }

        // sursa este radacina in arborele BFS - singura cu parinte 0
        q.push(source);
        p[source] = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto& x : adj[node]) {
                // daca x NU are parinte si muchia node->x NU este saturata
                if (p[x] == -1 && flow[node][x] < cap[node][x]) {
                    p[x] = node;
                    q.push(x);
                }
            }
        }

        // returnez TRUE daca se poate ajunge se la source la sink
        return p[sink] != -1;
    }

    void print_output(int result) {
        // ofstream fout("out");
        cout << result << '\n';
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
