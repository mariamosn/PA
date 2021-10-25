// Maria Moșneag 323CA

#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

#define NMAX 500000

vector<string> people;
unordered_map<int, vector<string>> id_and_mails;

class Task {
 public:
    void solve() {
        read_input();
        get_result();
        print_output();
    }

 private:
    int n;
    unordered_map<string, vector<int>> mail_to_ids;
    vector<int> final_people;

    static bool sort_aux_names(const int id1, const int id2) {
        if (id_and_mails[id1].size() == id_and_mails[id2].size()) {
            return people[id1] < people[id2];
        }
        return id_and_mails[id1].size() < id_and_mails[id2].size();
    }

    void read_input() {
        char name[21];
        char mail[51];
        int i, j, k, crt;
        ifstream fin("adrese.in");
        fin >> n;
        for (i = 0; i < n; ++i) {
            fin >> name;
            people.push_back(name);
            crt = people.size() - 1;

            fin >> k;
            for (j = 0; j < k; j++) {
                fin >> mail;
                if (mail_to_ids.find(string(mail)) == mail_to_ids.end()) {
                    vector<int> new_list;
                    new_list.push_back(crt);
                    mail_to_ids.insert(make_pair(string(mail), new_list));
                } else {
                    mail_to_ids[string(mail)].push_back(crt);
                }
            }
        }
        fin.close();
    }

    void get_result() {
        vector<int> adj[n + 1];
        // construirea grafului de id-uri
        for (auto kv : mail_to_ids) {
            for (int i = 0; i < (int) kv.second.size() - 1; i++) {
                adj[kv.second[i]].push_back(kv.second[i + 1]);
                adj[kv.second[i + 1]].push_back(kv.second[i]);
            }
        }

        vector<int> visited(n + 1, 0);
        queue<int> q;
        string name;
        int name_id;
        vector<int> rep(n + 1, 0);

        // determinarea componentelor conexe
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                vector<int> comp;
                comp.push_back(i);
                q.push(i);
                visited[i] = 1;
                name = people[i];
                name_id = i;

                while (!q.empty()) {
                    int crt = q.front();
                    q.pop();

                    for (int j = 0; j < (int) adj[crt].size(); j++) {
                        int neigh = adj[crt][j];
                        if (!visited[neigh]) {
                            visited[neigh] = 1;
                            comp.push_back(neigh);
                            q.push(neigh);
                            if (name > people[neigh]) {
                                name = people[neigh];
                                name_id = neigh;
                            }
                        }
                    }
                }

                for (auto i : comp) {
                    rep[i] = name_id;
                }
                id_and_mails[name_id] = vector<string>();
                final_people.push_back(name_id);
            }
        }

        // mapez lista de mailuri la id-ul unei persoane
        for (auto kv : mail_to_ids) {
            int rep_id = rep[kv.second[0]];
            id_and_mails[rep_id].push_back(kv.first);
        }

        // sortez lista de nume
        sort(final_people.begin(), final_people.end(), sort_aux_names);
    }

    void print_output() {
        ofstream fout("adrese.out");

        fout << final_people.size() << endl;
        for (auto i : final_people) {
            fout << people[i] << ' ' << id_and_mails[i].size() << endl;

            sort(id_and_mails[i].begin(), id_and_mails[i].end());
            for (auto j : id_and_mails[i]) {
                fout << j << endl;
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
