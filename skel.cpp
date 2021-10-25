#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;

    void read_input() {
    }

    int get_result() {
        
    }

    void print_output(int result) {
       
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
