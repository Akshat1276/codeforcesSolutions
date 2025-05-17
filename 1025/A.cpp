#include <bits/stdc++.h>
using namespace std;

struct TwoSAT {
    int n;
    vector<vector<int>> adj, adj_t;
    vector<bool> used;
    vector<int> order, comp;
    vector<bool> assignment;
    TwoSAT(int _n) : n(_n), adj(2 * _n), adj_t(2 * _n), assignment(_n) {}
    void dfs1(int v) {
        used[v] = true;
        for (int u : adj[v]) {
            if (!used[u]) {
                dfs1(u);
            }
        }
        order.push_back(v);
    }
    void dfs2(int v, int cl) {
        comp[v] = cl;
        for (int u : adj_t[v]) {
            if (comp[u] == -1) {
                dfs2(u, cl);
            }
        }
    }
    bool solve_2SAT() {
        used.assign(2 * n, false);
        for (int i = 0; i < 2 * n; ++i) {
            if (!used[i]) {
                dfs1(i);
            }
        }
        comp.assign(2 * n, -1);
        for (int i = 0, j = 0; i < 2 * n; ++i) {
            int v = order[2 * n - 1 - i];
            if (comp[v] == -1) {
                dfs2(v, j++);
            }
        }
        assignment.assign(n, false);
        for (int i = 0; i < n; ++i) {
            if (comp[2 * i] == comp[2 * i + 1]) {
                return false;
            }
            assignment[i] = comp[2 * i] > comp[2 * i + 1];
        }
        return true;
    }
    void add_clause(int a, int b) {
        adj[a^1].push_back(b);
        adj_t[b].push_back(a^1);
        adj[b^1].push_back(a);
        adj_t[a].push_back(b^1);
    }
};
void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        vector<char> duels(n-1, 'U');
        bool possible = true;
        for (int i = 0; i < n; ++i) {
            if (a[i] == 0) {
                int player = i + 1;
                if (player == 1) {
                    if (duels[0] == 'L') {
                        possible = false;
                    } else {
                        duels[0] = 'R';
                    }
                } else if (player == n) {
                    int j = n-2;
                    if (j < 0 || j >= duels.size()) {
                        possible = false;
                    } else {
                        if (duels[j] == 'R') {
                            possible = false;
                        } else {
                            duels[j] = 'L';
                        }
                    }
                } else {
                    int j_left = player - 2;
                    int j_right = player - 1;

                    if (j_left < 0 || j_left >= duels.size()) {
                        possible = false;
                    } else {
                        if (duels[j_left] != 'U' && duels[j_left] != 'L') {
                            possible = false;
                        } else {
                            duels[j_left] = 'L';
                        }
                    }

                    if (j_right >= duels.size()) {
                        possible = false;
                    } else {
                        if (duels[j_right] != 'U' && duels[j_right] != 'R') {
                            possible = false;
                        } else {
                            duels[j_right] = 'R';
                        }
                    }
                }
                if (!possible) break;
            }
        }
        if (!possible) {
            cout << "YES\n";
            continue;
        }

        vector<int> wins(n, 0);
        for (int j = 0; j < n-1; ++j) {
            if (duels[j] == 'L') {
                wins[j]++;
            } else if (duels[j] == 'R') {
                wins[j+1]++;
            }
        }
        TwoSAT solver(n-1);
        for (int j = 0; j < n-1; ++j) {
            if (duels[j] == 'L') {
                solver.add_clause(2*j, 2*j);
            } else if (duels[j] == 'R') {
                solver.add_clause(2*j + 1, 2*j + 1);
            }
        }
        bool has_liar = false;
        for (int i = 0; i < n; ++i) {
            if (a[i] == 1) {
                if (wins[i] >= 1) continue;
                int player = i + 1;
                vector<int> conditions;

                if (player == 1) {
                    int j = 0;
                    if (duels[j] == 'U') {
                        conditions.push_back(2*j);
                    }
                } else if (player == n) {
                    int j = n-2;
                    if (j >= 0 && j < duels.size() && duels[j] == 'U') {
                        conditions.push_back(2*j + 1);
                    }
                } else {
                    int j_left = player - 2;
                    int j_right = player - 1;

                    if (j_left >= 0 && j_left < duels.size() && duels[j_left] == 'U') {
                        conditions.push_back(2*j_left + 1);
                    }
                    if (j_right < duels.size() && duels[j_right] == 'U') {
                        conditions.push_back(2*j_right);
                    }
                }
                if (conditions.empty()) {
                    has_liar = true;
                    break;
                } else {
                    if (conditions.size() == 1) {
                        int a = conditions[0];
                        solver.add_clause(a, a);
                    } else {
                        int a = conditions[0];
                        int b = conditions[1];
                        solver.add_clause(a, b);
                    }
                }
            }
        }
        if (has_liar) {
            cout << "YES\n";
            continue;
        }
        bool solvable = solver.solve_2SAT();
        cout << (solvable ? "NO" : "YES") << "\n";
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
