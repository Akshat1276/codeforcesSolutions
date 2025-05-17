#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int64 h(int64 x) {
    if (x <= 1) return 0;
    x -= 1;
    int64 lg = 63 - __builtin_clzll(x);
    return lg + 1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int64 n, m, a, b;
        cin >> n >> m >> a >> b;
        if (n == 1 && m == 1) {
            cout << 0 << "\n";
            continue;
        }
        int64 n1 = min(a, n - a + 1);
        int64 m1 = min(b, m - b + 1);
        int64 cost_rows_first = 1 + (h(n1) + h(m));
        int64 cost_cols_first = 1 + (h(n) + h(m1));
        int64 ans = min(cost_rows_first, cost_cols_first);

        cout << ans << "\n";
    }

    return 0;
}
