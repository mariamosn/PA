// Maria Moșneag 323CA

#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

#define NMAX 10001

class Task {
 public:
    void solve() {
        read_input();
        get_result();
    }

 private:
    int n, m;
    vector<int> adj[NMAX];

    vector<int> parent;
    vector<int> found;
    vector<int> low_link;

    vector<int> is_cv;

    void read_input() {
        int x, y;
        ifstream fin("retea.in");
        fin >> n >> m;
        for (int i = 1; i <= m; i++) {
            fin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        fin.close();
    }

    // funcție preluată din rezolvarea laboratorului 8
    vector<int> tarjan_cv() {
        parent = vector<int>(n + 1, -1);
        found = vector<int>(n + 1, -1);
        low_link = vector<int>(n + 1, -1);
        is_cv = vector<int>(n + 1, 0);

        unordered_set<int> all_cvs;
        int timestamp = 0;
        for (int node = 1; node <= n; ++node) {
            if (parent[node] == -1) {
                parent[node] = node;
                dfs(node, timestamp, all_cvs);
            }
        }
        return {all_cvs.begin(), all_cvs.end()};
    }

    // funcție preluată din rezolvarea laboratorului 8
    void dfs(int node, int& timestamp, unordered_set<int>& all_cvs) {
        found[node] = ++timestamp;
        low_link[node] = found[node];

        int children = 0;
        for (auto neigh : adj[node]) {
            if (parent[neigh] != -1) {
                if (neigh != parent[node]) {
                    low_link[node] = min(low_link[node], found[neigh]);
                }
                continue;
            }

            parent[neigh] = node;
            ++children;

            dfs(neigh, timestamp, all_cvs);

            low_link[node] = min(low_link[node], low_link[neigh]);

            if (parent[node] != node && low_link[neigh] >= found[node]) {
                all_cvs.insert(node);
                is_cv[node] = 1;
            }
        }

        if (parent[node] == node && children > 1) {
            all_cvs.insert(node);
            is_cv[node] = 1;
        }
    }

    void get_result() {
        ofstream fout("retea.out");
        vector<int> cvs = tarjan_cv();

        for (int i = 1; i <= n; i++) {
            // i e nodul care dispare acum

            // determinarea numărului de apeluri dispărute pentru cazul
            // unui nod de articulație
            if (is_cv[i]) {
                vector<int> visited(n + 1, 0);
                queue<int> q;
                visited[i] = 1;
                int sum = n - 1;
                int cnt;

                for (int j = 1; j <= n; j++) {
                    if (!visited[j]) {
                        cnt = 0;
                        q.push(j);
                        visited[j] = 1;

                        while (!q.empty()) {
                            int node = q.front();
                            q.pop();
                            cnt++;

                            for (int neigh : adj[node]) {
                                if (!visited[neigh]) {
                                    visited[neigh] = 1;
                                    q.push(neigh);
                                }
                            }
                        }

                        sum += cnt * (n - cnt);
                    }
                }

                fout << sum << endl;

            // determinarea numărului de apeluri pierdute pentru cazul
            // nodurilor normale
            } else {
                fout << 2 * (n - 1) << endl;
            }
        }
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
