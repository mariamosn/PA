#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    struct Edge {
        int x;
        int y;

        Edge() { }
        Edge(int x, int y)
            : x(x)
            , y(y) { }

        bool operator==(const Edge& other) { return x == other.x && y == other.y; }
        bool operator!=(const Edge& other) { return !(*this == other); }
    };

    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];

    // parent[node] = parent of node in the DFS traversal
    vector<int> parent;

    // found[node] = the timestamp when node was found (when started to visit its subtree)
    // Note: The global timestamp is incremented everytime a node is found.
    vector<int> found;

    // the minimum accessible timestamp that node can see/access
    // low_link[node] =  min { found[x] | x is node OR x in ancestors(node) OR x in descendants(node) };
    vector<int> low_link;

    // edges stack: (node, neigh) is pushed into stack when traversing the edge
    stack<Edge> edges_stack;

    void read_input() {
        // ifstream fin("in");
        cin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            cin >> x >> y; // muchia (x, y)
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        // fin.close();
    }

    vector<vector<int>> get_result() {
        //
        // TODO: Găsiți componentele biconexe (BCC) ale grafului neorientat cu n noduri, stocat în adj.
        //
        // Rezultatul se va returna sub forma unui vector, fiecare element fiind un BCC (adică tot un vector).
        // * nodurile dintr-un BCC pot fi găsite în orice ordine
        // * BCC-urile din graf pot fi găsite în orice ordine
        //
        // Indicație: Folosiți algoritmul lui Tarjan pentru BCC.
        //

        return tarjan_bcc();
    }

    vector<vector<int>> tarjan_bcc() {
        // STEP 1: initialize results
        parent = vector<int>(n + 1, -1);
        found = vector<int>(n + 1, -1);
        low_link = vector<int>(n + 1, -1);

        // STEP 2: visit all nodes
        vector<vector<int>> all_bccs;
        int timestamp = 0; // global timestamp
        for (int node = 1; node <= n; ++node) {
            if (parent[node] == -1) { // node not visited
                parent[node] = node; // convention: the parent of the root is actually the root

                // STEP 3: start a new DFS traversal this subtree
                dfs(node, timestamp, all_bccs);
            }
        }

        return all_bccs;
    }

    void dfs(int node, int& timestamp, vector<vector<int>>& all_bccs) {
        // STEP 1: a new node is visited - increment the timestamp
        found[node] = ++timestamp; // the timestamp when node was found
        low_link[node] = found[node]; // node only knows its timestamp

        // STEP 2: visit each neighbour
        for (auto neigh : adj[node]) {
            // STEP 3: check if neigh is already visited
            if (parent[neigh] != -1) {
                // STEP 3.1: update low_link[node] with information gained through neigh
                // note: because it's an undirected graf, we should ignore the edge to the parent
                // (the found value of the parent is always less than found value of node)
                if (neigh != parent[node]) {
                    low_link[node] = min(low_link[node], found[neigh]);
                }
                continue;
            }

            // STEP 4: save parent
            parent[neigh] = node;
            edges_stack.push(Edge(node, neigh));

            // STEP 5: recursively visit the child subree
            dfs(neigh, timestamp, all_bccs);

            // STEP 6: update low_link[node] with information gained through neigh
            low_link[node] = min(low_link[node], low_link[neigh]);

            // STEP 7: if low_link[neigh] >= found[node], all edges above (node, neigh) from stack are from the same BCC
            if (low_link[neigh] >= found[node]) {
                all_bccs.push_back(get_bcc(Edge(node, neigh)));
            }
        }
    }

    // extract all edges from the stack above stop_edge
    vector<int> get_bcc(Edge stop_edge) {
        unordered_set<int> bcc;

        Edge e;
        do {
            e = edges_stack.top();
            edges_stack.pop();

            bcc.insert(e.x);
            bcc.insert(e.y);
        } while (e != stop_edge); // stop when extracted the stop_edge

        // convert set to vector
        return vector<int>{bcc.begin(), bcc.end()};
    }

    void print_output(const vector<vector<int>>& all_bccs) {
        // ofstream fout("out");
        cout << all_bccs.size() << '\n';
        for (auto& bcc : all_bccs) {
            for (auto node : bcc) {
                cout << node << " ";
            }
            cout << "\n";
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
